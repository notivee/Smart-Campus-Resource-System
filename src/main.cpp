#include <iostream>
#include <string>
#include <limits>

using namespace std;
const int MAX_STUDENTS = 5; // mabalik nalang siguro to sa 50
const int RESOURCE_COUNT = 5;
const int MATRIX_ROWS = 4;
const int MATRIX_COLS = 4;

// Student record
struct Student {
    int id;
    string name;
    string section;
    string yearLevel;
    string status;
};

// Campus resource record
struct Resource {
    string id;
    string name;
    string type;
    int capacity;
};


// ============================================================
// STATIC ARRAYS
// ============================================================

// Static array required by the assessment
Student students[MAX_STUDENTS];

int studentCount = 0;


// Static campus resource array
Resource resources[RESOURCE_COUNT] = {
    {"R-01", "Computer Laboratory 1", "Laboratory", 40},
    {"R-02", "Conference Room", "Meeting Space", 20},
    {"R-03", "Library Study Hub", "Study Area", 60},
    {"R-04", "Robotics Lab", "Laboratory", 25},
    {"R-05", "Multimedia Room", "Laboratory", 30}
};


// 2D Resource Utilization Matrix
//
// Rows:
// D1 = IT
// D2 = Engineering
// D3 = Business
// D4 = Education
//
// Columns:
// Resource 1, Resource 2, Resource 3, Resource 4

int resourceMatrix[MATRIX_ROWS][MATRIX_COLS] = {
    {12, 3, 8, 5},
    {9,  2, 4, 10},
    {5,  6, 10, 2},
    {4,  8, 6, 3}
};


// Department names for matrix
string departments[MATRIX_ROWS] = {
    "IT",
    "Engineering",
    "Business",
    "Education"
};


// ============================================================
// FUNCTION PROTOTYPES
// ============================================================

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

void manageResources();
void displayResourceMatrix();
void analyzeResourceUtilization();

void generateReport();


// Helper functions
bool studentIdExists(int id);
int findStudentIndex(int id);
void clearInput();
int getValidInteger(string prompt);
string getNonEmptyString(string prompt);
void displayOneStudent(const Student& student);


// ============================================================
// MAIN
// ============================================================

int main() {

    int choice = 0;

    do {

        cout << "\n========================================\n";
        cout << "SMART CAMPUS RESOURCE MANAGEMENT SYSTEM\n";
        cout << "========================================\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Manage Campus Resources\n";
        cout << "7. Display Resource Matrix\n";
        cout << "8. Analyze Resource Utilization\n";
        cout << "9. Generate Report\n";
        cout << "10. Exit\n";
        cout << "Enter choice: ";

        // INPUT VALIDATION - DO NOT REMOVE
        if (!(cin >> choice)) {

            cout << "Invalid input! Please enter a number.\n";

            cin.clear();
            cin.ignore(10000, '\n');

            continue;
        }

        cin.ignore(10000, '\n');


        switch (choice) {

            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                manageResources();
                break;
            case 7:
                displayResourceMatrix();
                break;
            case 8:
                analyzeResourceUtilization();
                break;
            case 9:
                generateReport();
                break;
            case 10:
                cout << "\nExiting system. Have a nice day!\n";
                break;
            default:
                cout << "\nInvalid choice! Please select an option from 1 to 10.\n";
        }

    } while (choice != 10);


    return 0;
}


// ============================================================
// HELPER FUNCTION: CLEAR INPUT
// ============================================================

void clearInput() {

    cin.clear();
    cin.ignore(10000, '\n');
}


// ============================================================
// HELPER FUNCTION: VALID INTEGER
// ============================================================

int getValidInteger(string prompt) {

    int value;

    while (true) {

        cout << prompt;

        if (cin >> value) {

            cin.ignore(10000, '\n');

            return value;
        }

        cout << "Invalid input! Please enter a number.\n";

        clearInput();
    }
}


// ============================================================
// HELPER FUNCTION: NON-EMPTY STRING
// ============================================================

string getNonEmptyString(string prompt) {

    string value;

    while (true) {

        cout << prompt;
        getline(cin, value);

        if (!value.empty()) {
            return value;
        }

        cout << "Input cannot be empty. Please try again.\n";
    }
}


// ============================================================
// HELPER FUNCTION: CHECK DUPLICATE STUDENT ID
// ============================================================

bool studentIdExists(int id) {

    for (int i = 0; i < studentCount; i++) {

        if (students[i].id == id) {
            return true;
        }
    }

    return false;
}


// ============================================================
// HELPER FUNCTION: LINEAR SEARCH
// ============================================================

int findStudentIndex(int id) {

    // Linear search
    // Best case: O(1)
    // Worst case: O(n)

    for (int i = 0; i < studentCount; i++) {

        if (students[i].id == id) {
            return i;
        }
    }

    return -1;
}


// ============================================================
// HELPER FUNCTION: DISPLAY ONE STUDENT
// ============================================================

void displayOneStudent(const Student& student) {

    cout << "Student ID : " << student.id << endl;
    cout << "Name       : " << student.name << endl;
    cout << "Section    : " << student.section << endl;
    cout << "Year Level : " << student.yearLevel << endl;
    cout << "Status     : " << student.status << endl;
}


// ============================================================
// 1. ADD STUDENT
// ============================================================

void addStudent() {

    cout << "\n========================================\n";
    cout << "ADD STUDENT\n";
    cout << "========================================\n";


    // Maximum capacity / bounds checking
    if (studentCount >= MAX_STUDENTS) {

        cout << "Student record capacity is full!\n";
        cout << "Maximum capacity: " << MAX_STUDENTS << " students.\n";

        return;
    }


    int id = getValidInteger("Enter Student ID: ");


    // Duplicate record validation
    if (studentIdExists(id)) {

        cout << "Error: Student ID already exists.\n";

        return;
    }


    // ========================================================
    // DYNAMIC MEMORY
    // ========================================================
    //
    // Allocate one Student dynamically using new.
    // The pointer stores the memory address.
    //
    Student* newStudent = new Student;


    // Pointer access using ->
    newStudent->id = id;

    cout << "Enter Student Name: ";
    getline(cin, newStudent->name);

    while (newStudent->name.empty()) {

        cout << "Name cannot be empty.\n";
        cout << "Enter Student Name: ";

        getline(cin, newStudent->name);
    }


    cout << "Enter Section: ";
    getline(cin, newStudent->section);

    while (newStudent->section.empty()) {

        cout << "Section cannot be empty.\n";
        cout << "Enter Section: ";

        getline(cin, newStudent->section);
    }


    cout << "Enter Year Level: ";
    getline(cin, newStudent->yearLevel);

    while (newStudent->yearLevel.empty()) {

        cout << "Year level cannot be empty.\n";
        cout << "Enter Year Level: ";

        getline(cin, newStudent->yearLevel);
    }


    cout << "Enter Status (Active/Inactive): ";
    getline(cin, newStudent->status);

    while (newStudent->status.empty()) {

        cout << "Status cannot be empty.\n";
        cout << "Enter Status (Active/Inactive): ";

        getline(cin, newStudent->status);
    }


    // Copy dynamically allocated record
    // into our static array.
    students[studentCount] = *newStudent;


    // Deallocate dynamic memory.
    // Prevents memory leak.
    delete newStudent;

    newStudent = nullptr;


    studentCount++;


    cout << "\nStudent added successfully!\n";
}


// ============================================================
// 2. DISPLAY STUDENTS
// ============================================================

void displayStudents() {

    cout << "\n========================================\n";
    cout << "STUDENT RECORDS\n";
    cout << "========================================\n";


    // Empty record validation
    if (studentCount == 0) {

        cout << "No student records available.\n";

        return;
    }


    // Array traversal
    // Time complexity: O(n)

    for (int i = 0; i < studentCount; i++) {

        cout << "\n----------------------------------------\n";
        cout << "Record #" << i + 1 << endl;
        cout << "----------------------------------------\n";

        displayOneStudent(students[i]);
    }
}


// ============================================================
// 3. SEARCH STUDENT
// ============================================================

void searchStudent() {

    cout << "\n========================================\n";
    cout << "SEARCH STUDENT\n";
    cout << "========================================\n";


    if (studentCount == 0) {

        cout << "No student records available.\n";

        return;
    }


    int id = getValidInteger("Enter Student ID to search: ");


    // Linear search
    int index = findStudentIndex(id);


    if (index == -1) {

        cout << "\nStudent ID not found.\n";

        return;
    }


    cout << "\nStudent found!\n";
    cout << "----------------------------------------\n";

    displayOneStudent(students[index]);
}


// ============================================================
// 4. UPDATE STUDENT
// ============================================================

void updateStudent() {

    cout << "\n========================================\n";
    cout << "UPDATE STUDENT\n";
    cout << "========================================\n";


    if (studentCount == 0) {

        cout << "No student records available.\n";

        return;
    }


    int id = getValidInteger("Enter Student ID to update: ");


    int index = findStudentIndex(id);


    if (index == -1) {

        cout << "Student ID not found.\n";

        return;
    }


    cout << "\nCurrent student information:\n";
    cout << "----------------------------------------\n";

    displayOneStudent(students[index]);


    cout << "\nEnter new information.\n";


    cout << "New Name: ";
    getline(cin, students[index].name);

    while (students[index].name.empty()) {

        cout << "Name cannot be empty.\n";
        cout << "New Name: ";

        getline(cin, students[index].name);
    }


    cout << "New Section: ";
    getline(cin, students[index].section);

    while (students[index].section.empty()) {

        cout << "Section cannot be empty.\n";
        cout << "New Section: ";

        getline(cin, students[index].section);
    }


    cout << "New Year Level: ";
    getline(cin, students[index].yearLevel);

    while (students[index].yearLevel.empty()) {

        cout << "Year level cannot be empty.\n";
        cout << "New Year Level: ";

        getline(cin, students[index].yearLevel);
    }


    cout << "New Status: ";
    getline(cin, students[index].status);

    while (students[index].status.empty()) {

        cout << "Status cannot be empty.\n";
        cout << "New Status: ";

        getline(cin, students[index].status);
    }


    cout << "\nStudent updated successfully!\n";
}


// ============================================================
// 5. DELETE STUDENT
// ============================================================

void deleteStudent() {

    cout << "\n========================================\n";
    cout << "DELETE STUDENT\n";
    cout << "========================================\n";


    if (studentCount == 0) {

        cout << "No student records available.\n";

        return;
    }


    int id = getValidInteger("Enter Student ID to delete: ");


    int index = findStudentIndex(id);


    if (index == -1) {

        cout << "Student ID not found.\n";

        return;
    }


    // Shift elements to the left.
    //
    // Example:
    // [1001] [1002] [1003] [1004]
    // Delete 1002
    // [1001] [1003] [1004]

    for (int i = index; i < studentCount - 1; i++) {

        students[i] = students[i + 1];
    }


    studentCount--;


    cout << "Student deleted successfully!\n";
}


// ============================================================
// 6. MANAGE CAMPUS RESOURCES
// ============================================================

void manageResources() {

    cout << "\n========================================\n";
    cout << "MANAGE CAMPUS RESOURCES\n";
    cout << "========================================\n";


    for (int i = 0; i < RESOURCE_COUNT; i++) {

        cout << "\nResource #" << i + 1 << endl;
        cout << "ID       : " << resources[i].id << endl;
        cout << "Name     : " << resources[i].name << endl;
        cout << "Type     : " << resources[i].type << endl;
        cout << "Capacity : " << resources[i].capacity << endl;
    }


    cout << "\n----------------------------------------\n";

    string resourceID;

    cout << "Enter Resource ID to update capacity\n";
    cout << "(Enter 0 to cancel): ";

    getline(cin, resourceID);


    if (resourceID == "0") {

        cout << "Operation cancelled.\n";

        return;
    }


    int resourceIndex = -1;


    // Linear search through resource array
    for (int i = 0; i < RESOURCE_COUNT; i++) {

        if (resources[i].id == resourceID) {

            resourceIndex = i;
            break;
        }
    }


    if (resourceIndex == -1) {

        cout << "Resource ID not found.\n";

        return;
    }


    int newCapacity =
        getValidInteger("Enter new capacity: ");


    // Bounds checking
    if (newCapacity <= 0) {

        cout << "Capacity must be greater than zero.\n";

        return;
    }


    resources[resourceIndex].capacity = newCapacity;


    cout << "Resource capacity updated successfully!\n";
}


// ============================================================
// 7. DISPLAY RESOURCE MATRIX
// ============================================================

void displayResourceMatrix() {

    cout << "\n========================================\n";
    cout << "CAMPUS RESOURCE UTILIZATION MATRIX\n";
    cout << "========================================\n";


    cout << "\nDepartment\tR1\tR2\tR3\tR4\n";
    cout << "----------------------------------------\n";


    // 2D array traversal
    // Time complexity: O(n^2)

    for (int i = 0; i < MATRIX_ROWS; i++) {

        cout << departments[i] << "\t\t";

        for (int j = 0; j < MATRIX_COLS; j++) {

            cout << resourceMatrix[i][j] << "\t";
        }

        cout << endl;
    }
}


// ============================================================
// 8. ANALYZE RESOURCE UTILIZATION
// ============================================================

void analyzeResourceUtilization() {

    cout << "\n========================================\n";
    cout << "RESOURCE UTILIZATION ANALYSIS\n";
    cout << "========================================\n";


    // ========================================================
    // MATRIX OPERATION 1: ROW TOTALS
    // ========================================================

    cout << "\nROW TOTALS\n";
    cout << "----------------------------------------\n";


    for (int i = 0; i < MATRIX_ROWS; i++) {

        int rowTotal = 0;


        for (int j = 0; j < MATRIX_COLS; j++) {

            rowTotal += resourceMatrix[i][j];
        }


        cout << departments[i]
             << ": "
             << rowTotal
             << endl;
    }


    // ========================================================
    // MATRIX OPERATION 2: COLUMN TOTALS
    // ========================================================

    cout << "\nCOLUMN TOTALS\n";
    cout << "----------------------------------------\n";


    for (int j = 0; j < MATRIX_COLS; j++) {

        int columnTotal = 0;


        for (int i = 0; i < MATRIX_ROWS; i++) {

            columnTotal += resourceMatrix[i][j];
        }


        cout << "Resource " << j + 1
             << ": "
             << columnTotal
             << endl;
    }


    // ========================================================
    // GRAND TOTAL
    // ========================================================

    int grandTotal = 0;


    for (int i = 0; i < MATRIX_ROWS; i++) {

        for (int j = 0; j < MATRIX_COLS; j++) {

            grandTotal += resourceMatrix[i][j];
        }
    }


    cout << "\n----------------------------------------\n";
    cout << "Total Utilization: " << grandTotal << endl;
}


// ============================================================
// 9. GENERATE REPORT
// ============================================================

void generateReport() {

    cout << "\n========================================\n";
    cout << "SMART CAMPUS SYSTEM REPORT\n";
    cout << "========================================\n";


    // ========================================================
    // STUDENT SUMMARY
    // ========================================================

    cout << "\nSTUDENT SUMMARY\n";
    cout << "----------------------------------------\n";

    cout << "Maximum Capacity : "
         << MAX_STUDENTS
         << endl;

    cout << "Current Records  : "
         << studentCount
         << endl;

    cout << "Available Slots  : "
         << MAX_STUDENTS - studentCount
         << endl;


    int activeStudents = 0;
    int inactiveStudents = 0;


    for (int i = 0; i < studentCount; i++) {

        if (students[i].status == "Active" ||
            students[i].status == "active" ||
            students[i].status == "ACTIVE") {

            activeStudents++;
        }
        else {

            inactiveStudents++;
        }
    }


    cout << "Active Students  : "
         << activeStudents
         << endl;

    cout << "Inactive Students: "
         << inactiveStudents
         << endl;


    // ========================================================
    // RESOURCE SUMMARY
    // ========================================================

    cout << "\nRESOURCE SUMMARY\n";
    cout << "----------------------------------------\n";


    cout << "Total Resources: "
         << RESOURCE_COUNT
         << endl;


    for (int i = 0; i < RESOURCE_COUNT; i++) {

        cout << resources[i].id
             << " - "
             << resources[i].name
             << " | Capacity: "
             << resources[i].capacity
             << endl;
    }


    // ========================================================
    // MATRIX SUMMARY
    // ========================================================

    int grandTotal = 0;


    for (int i = 0; i < MATRIX_ROWS; i++) {

        for (int j = 0; j < MATRIX_COLS; j++) {

            grandTotal += resourceMatrix[i][j];
        }
    }
    cout << "\nMATRIX SUMMARY\n";
    cout << "----------------------------------------\n";
    cout << "Departments: "
         << MATRIX_ROWS
         << endl;
    cout << "Resource Categories: "
         << MATRIX_COLS
         << endl;

    cout << "Total Utilization: "
         << grandTotal
         << endl;


    cout << "\n========================================\n";
    cout << "END OF REPORT\n";
    cout << "========================================\n";
}
