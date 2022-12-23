// assign2_app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include<vector>
#include "sqlite/sqlite3.h"
using namespace std;



static int print_values(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {

        cout << azColName[i] << " " << argv[i] << " ";
    }
    cout << endl;
    return 0;
}

int main()
{
    sqlite3* Database;

    // CREATE OPERATION
    // Opening A New Database Connection Database - first arg(filename (UTF-8)) - second arg (OUT: SQLite db handle)
    sqlite3_open("Database.db", &Database);
    char* err;
    int rc = sqlite3_exec(Database, "CREATE TABLE IF NOT EXISTS employee(EmployeeID INT, FirstName TEXT, LastName TEXT, City TEXT);", NULL, NULL, &err);

    if (rc != SQLITE_OK) {
        cout << "Error is: " << err << endl;
    }
    vector<int>ids{ 1, 2, 3,4, 5, 6, 7, 8, 9, 10 };
    vector<string>fname{"James", "Mary", "Robert", "Patricia", "John", "Jennifer", "Michael", "Linda", "David", "Elizabeth"};
    vector<string>lname{ "Barlowe", "Caddel", "Hart", "Katz", "Laurier", "Madden", "Elrod", "Whitlock", "West", "Langley" };
    vector<string>city{ "Tokyo", "Delhi", "Shanghai", "Mexico_City", "São_Paulo", "Mumbai", "Kinki", "Cairo", "Rome", "New_york" };


    // UPDATE OPERATION
    
    string query = "INSERT INTO employee VALUES(1, 'James', 'Barlowe', 'Tokyo');"
        "INSERT INTO employee VALUES(2, 'Mary', 'Caddel', 'Delhi');"
        "INSERT INTO employee VALUES(3, 'Robert', 'Hart', 'Shanghai');"
        "INSERT INTO employee VALUES(4, 'Patricia', 'Katz', 'Mexico_City');"
        "INSERT INTO employee VALUES(5, 'John', 'Laurier', 'São_Paulo');"
        "INSERT INTO employee VALUES(6, 'Jennifer', 'Madden', 'Mumbai');"
        "INSERT INTO employee VALUES(7, 'Michael', 'Elrod', 'Kinki');"
        "INSERT INTO employee VALUES(8, 'Linda', 'Whitlock', 'Cairo');"
        "INSERT INTO employee VALUES(9, 'David', 'West', 'Rome');"
        "INSERT INTO employee VALUES(10, 'Elizabeth', 'Langley', 'New_york');";

    rc = sqlite3_exec(Database, query.c_str(), NULL, NULL, &err);
    if (rc != SQLITE_OK) {
        cout << "Error is: " << err << endl;
    }
    
    

    // READ OPERATION
    // Compiling An SQL Statement, -1 in argument represents doesn't care, table is stored in stmt after this


    
    rc = sqlite3_exec(Database, "SELECT * FROM employee;", print_values, NULL, &err);

    if (rc != SQLITE_OK) {
        cout << "Error is: " << err << endl;
    }

    
    
    // DELETE OPERATION
    
    rc = sqlite3_exec(Database, "DELETE from employee where EmployeeID=2;", NULL, NULL, &err);

    if (rc != SQLITE_OK) {
        cout << "Delete error is: " << err << endl;
    }
    else {
        cout << "Data successfully deleted" << endl;

    }
    // Showing data after delete operation is performed
    rc = sqlite3_exec(Database, "SELECT * FROM employee;", print_values, NULL, &err);

    // closing the database connection
    sqlite3_close(Database);
    return 0;
}