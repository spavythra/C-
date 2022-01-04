//--------------------------------------------------
//  COMP.CS.110 Ohjelmointi 2: Rakenteet -pohjakoodi
//  Copyright © 2021
//--------------------------------------------------

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

// the chosen data structure is vector of structs inside a map
// to keep it simple term, "data structure" is used all over the places


//structure definition with course name,location and enrollment details
struct theme_info_vect
{
    string course_name;
    string location;
    string enrollments;
};


//data structure type definition for better readability
typedef vector<theme_info_vect> vect ;
typedef map<string ,vect> str_vect_map ;

//iterator type definition for better readability
map<string, vect>::iterator it_out;
vector<theme_info_vect>::iterator it_in;




// function definitions



// Splits the given string str into parts separated by the given delimiter
// and returns the parts in a vector.
// If the delimiter appears inside quatation, ignores delimiter,
// i.e. does not split quoted text.
std::vector<std::string> split_ignoring_quoted_delim(const std::string& str,
                                                     char delimiter)
{
    std::vector<std::string> result = {""};
    bool inside_quotation = false;
    for(char current_char : str)
    {
        if(current_char == '"')
        {
            inside_quotation = not inside_quotation;
        }
        else if(current_char == delimiter and not inside_quotation)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if(result.back() == "")
    {
        result.erase(--result.end());
    }
    return result;
}

// compares the two location strings (of the struct) for sort function
bool compare_courses_by_location(theme_info_vect& inst1, theme_info_vect& inst2)
{
    return inst1.location < inst2.location;
    return (inst1.location < inst2.location);
}


// compares the two location strings (of the struct) for sort function
// if location is same then two course_name strings are compared,
// both location and course_name are members of the struct
bool compare_courses_by_loc_name(theme_info_vect& inst1, theme_info_vect& inst2)
{

    if (inst1.location < inst2.location)
        return true;
    else if (inst1.location == inst2.location)
        if (inst1.course_name < inst2.course_name)
            return true;
        else
            return false;
    else
        return false;
}


// copying the data structure members to the local temporary vector
// prints all the available theme name, course_name
// (from the data structure) with locations and course_name sorted
void available(str_vect_map &m)
{

    // local temporary vector
    vector<theme_info_vect> course_vector;
    theme_info_vect struct_;

    // Looping and accessing the datastructure to the given location
    for(it_out = m.begin(); it_out !=m.end(); it_out++)
    {
        course_vector.clear();      // clearing when moving to next theme

        for(it_in=(*it_out).second.begin(); it_in !=(*it_out).second.end(); it_in++)
        {
            struct_.course_name = (*it_in).course_name;
            struct_.location = (*it_in).location;
            struct_.enrollments = (*it_in).enrollments;

            if ((*it_in).enrollments != "full")
            {
                 course_vector.push_back(struct_);
            }
        }
        std::sort(course_vector.begin(), course_vector.end(), compare_courses_by_loc_name);

        // printing the temporary vector
        for(auto name:course_vector)
        {
            cout<<(*it_out).first<<" : "<<name.location<<" : "<<name.course_name<<endl;
        }
    }
}


// sorting the course name and printing them with its enrollment details,
// (from the data structure) for the given location and course name
void courses(str_vect_map &m, string location_name, string course_name)
{

    // local temporary map
    map<string,string> courses_map;

    // Looping and accessing the datastructure to the given location
    for(it_out = m.begin(); it_out !=m.end(); it_out++)
    {
        if ((*it_out).first == course_name)
        {
            for(it_in=(*it_out).second.begin(); it_in !=(*it_out).second.end(); it_in++)
            {
                if ((*it_in).location == location_name)
                {
                    courses_map[(*it_in).course_name] = (*it_in).enrollments;
                }
            }
        }
    }
    // printing the temporary map
    for (auto name: courses_map)
    {
        if (name.second == "full")
        {
            cout<< name.first<< " --- "<< name.second<<endl;
        }
        else
        {
           cout<< name.first << " --- "<< name.second <<" enrollments"<<endl;
        }
    }
}



// sorting the location name and printing them with all its course details
// (from the data structure), for the given theme
void courses_in_theme(str_vect_map &m, string theme_name)
{

    vector<theme_info_vect> course_vector;
    theme_info_vect struct_;

    // Looping and accessing the datastructure to the given location
    for(it_out = m.begin(); it_out !=m.end(); it_out++)
    {
        if ((*it_out).first == theme_name)
        {
            course_vector.clear();      // clearing the vector when moving to next theme

            for(it_in=(*it_out).second.begin(); it_in !=(*it_out).second.end(); it_in++)
            {
                struct_.course_name = (*it_in).course_name;
                struct_.location = (*it_in).location;
                struct_.enrollments = (*it_in).enrollments;

                course_vector.push_back(struct_);
            }
        }
    }
    std::sort(course_vector.begin(), course_vector.end(), compare_courses_by_location);

    // printing the temporary vector
    for(auto name:course_vector)
    {
        cout<<name.location<<" : "<<name.course_name<<endl;
    }

}



// sorting the course name and printing them,
// for the given location (from the data structure)
void courses_in_location(str_vect_map &m, string location_name)
{

    //temporary set for auto sort
    set <string> result;

    // Looping and accessing the datastructure to the given location
    for(it_out = m.begin(); it_out !=m.end(); it_out++)
    {
            for(it_in=(*it_out).second.begin(); it_in !=(*it_out).second.end(); it_in++)
            {
                if((*it_in).location == location_name)
                {
                    result.insert((*it_in).course_name);
                }
            }
    }
    // printing the temporary set
    for (auto name : result)
    {
        cout<<name<<endl;
    } 
}


//printing the total enrollments for all the courses and
// theme name with maximum enrollments (from the data structure)
void favorite_theme(str_vect_map &m)
{

    map<string, int> temp_map;

    // Looping and accessing the datastructure to the given location
    for(it_out = m.begin(); it_out !=m.end(); it_out++)
    {
        for(it_in=(*it_out).second.begin(); it_in !=(*it_out).second.end(); it_in++)
        {
            int temp_value = 0;     // clearing value when moving to next course

            if (temp_map.find((*it_out).first)==temp_map.end())
            {
                if((*it_in).enrollments=="full")
                {
                    temp_value = 50;
                    temp_map[(*it_out).first] =temp_value;
                }
                else
                {
                    temp_map[(*it_out).first] =stoi((*it_in).enrollments);
                }
            }
            else
            {
                if((*it_in).enrollments=="full")
                {
                    temp_value = 50;
                    temp_value = temp_value + temp_map[(*it_out).first];
                    temp_map[(*it_out).first] =temp_value;
                }
                else
                {
                    temp_value = stoi((*it_in).enrollments) + temp_map[(*it_out).first];
                    temp_map[(*it_out).first] =temp_value;
                }
            }
        }
    }
    pair<string,int>maxValue = make_pair("a",0);
    map<string, int>::iterator currentEntry;

    for(currentEntry = temp_map.begin(); currentEntry != temp_map.end(); ++currentEntry)
    {
        if (currentEntry->second > maxValue.second)
        {
            maxValue = make_pair(currentEntry->first, currentEntry->second);
        }
    }
    if (maxValue.second != 0)
    {
        cout << maxValue.second<<" enrollments in themes"<<endl;
        for (auto count : temp_map)
        {
            if (count.second == maxValue.second)
            {
                cout<<"--- "<<count.first<<endl;
            }
        }
    }
    else
    {
        cout<<"No enrollments"<<endl;
    }
}


//removing the given course name from all the locations (from the data structure)
void cancel(str_vect_map &m, string course)
{

    // Looping and accessing the datastructure to the given location
    for(it_out = m.begin(); it_out != m.end(); it_out++)
    {
        (*it_out).second.erase(std::remove_if(((*it_out).second.begin()), ((*it_out).second.end()),
          [course] (theme_info_vect& temp_vect) {return temp_vect.course_name == course;}),(*it_out).second.end());
    }
    cout<<course<<" cancelled in all locations"<<endl;

}


// main function

int main(int , char* [])
{
    str_vect_map outer_map; // creating the data structure

    // variables for the input reading
    std::vector<std::string> in_vector;
    string theme;
    string command;
    string filename = "";
    string line;
    theme_info_vect course_info;

    // separate storage of struct members
    set<string> location_set;
    set<string> theme_set;
    set<string> course_set;

    cout << "Input file: ";
    getline(cin, filename);

    ifstream file_object(filename);

    // error opening file
    if (not file_object)
    {
        cout << "Error: the input file cannot be opened" << endl;
        return EXIT_FAILURE;
    }
    else
    {
        // reading input commands and do-functions and/or error messages when needed
        while (getline(file_object, line))
        {
            bool flag = false;
            in_vector = split_ignoring_quoted_delim(line,';');

            if (in_vector.size() < 4 || in_vector.at(0)=="" || in_vector.at(1)=="" ||
                    in_vector.at(2)=="" || in_vector.at(3)=="")
            {
                cout<<"Error: empty field"<<endl;
                return EXIT_FAILURE;
            }
            else
            {
                theme = in_vector.at(0);
                course_info.course_name = in_vector.at(1);
                course_info.location = in_vector.at(2);
                course_info.enrollments = in_vector.at(3);
                // course_info structure

                outer_map.insert(make_pair(theme,vect()));
                theme_set.insert(theme);

                // Looping and accessing the datastructure to the given location
                for(it_out = outer_map.begin(); it_out !=outer_map.end(); it_out++)
                {
                    for(it_in=(*it_out).second.begin(); it_in !=(*it_out).second.end(); it_in++)
                    {
                        if((*it_in).course_name == course_info.course_name
                                && (*it_in).location == course_info.location)
                        {
                            (*it_in).enrollments = course_info.enrollments;
                            // overwriting duplicate courses from same location

                            flag = true;      // flag variable for overwriting
                        }
                    }
                }
                if (!flag)
                {
                    outer_map[theme].push_back(course_info);
                    //vector of struct stored for given key value if flage is not set
                }

                course_set.insert(course_info.course_name);
                location_set.insert(course_info.location);
            }
        }
        file_object.close();
        bool invalid_input = false;
        while (invalid_input == false)
        {
            cout<<"> ";
            getline(cin,command);
            in_vector = split_ignoring_quoted_delim(command,' ');

            if (command == "themes")
            {
                for (auto name : theme_set)
                {
                    cout<<name<<endl;
                }
            }
            else if (in_vector.at(0)== "courses")
            {
                if (in_vector.size()== 3)
                {
                    if (theme_set.find(in_vector.at(2))== theme_set.end())
                    {
                        cout<<"Error: unknown theme"<<endl;
                    }
                    else if (location_set.find(in_vector.at(1)) == location_set.end())
                    {
                        cout<<"Error: unknown location"<<endl;
                    }
                    else
                    {
                        courses(outer_map,in_vector.at(1),in_vector.at(2));
                    }

                }
                else
                {
                    cout<<"Error: error in command "<<in_vector.at(0)<<endl;
                }
            }
            else if (command == "available")
            {
                available(outer_map);
            }
            else if (in_vector.size()== 2)
            {
                if (in_vector.at(0)== "courses_in_theme")
                {
                    if (theme_set.find(in_vector.at(1))== theme_set.end())
                    {
                        cout<<"Error: unknown theme"<<endl;
                    }
                    else
                    {
                        courses_in_theme(outer_map,in_vector.at(1));
                    }
                }
                else if (in_vector.at(0)== "courses_in_location")
                {
                    if (location_set.find(in_vector.at(1))== location_set.end())
                    {
                        cout<<"Error: unknown location"<<endl;
                    }
                    else
                    {
                        courses_in_location(outer_map,in_vector.at(1));
                    }

                }
                else if (in_vector.at(0)=="cancel")
                {
                    if (course_set.find(in_vector.at(1))== course_set.end())
                    {
                        cout<<"Error: unknown course"<<endl;
                    }
                    else
                    {
                        cancel(outer_map,in_vector.at(1));
                    }
                }
                else
                {
                    cout<<"Error: Unknown command: "<<in_vector.at(0)<<endl;
                }
            }
            else if (command == "favorite_theme")
            {
                favorite_theme(outer_map);
            }
            else
            {
                if (command == "quit")
                {
                    return EXIT_SUCCESS;
                }
                else
                {
                    cout<<"Error: Unknown command: "<<command<<endl;
                }
            }
        }

    }
return EXIT_SUCCESS;
}

