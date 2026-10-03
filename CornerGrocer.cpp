#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>

using namespace std;

// GroceryTracker stores and manages grocery purchase data.
class GroceryTracker {
private:
    map<string, int> itemFrequency;

public:
    void LoadData(string fileName);
    int GetItemFrequency(string item);
    void PrintAllFrequencies();
    void PrintHistogram();
    void CreateBackupFile(string fileName);
};

// Reads grocery items from the input file and counts each occurrence.
void GroceryTracker::LoadData(string fileName) {
    ifstream inputFile(fileName);
    string item;

    if (inputFile.is_open()) {
        while (inputFile >> item) {
            itemFrequency[item]++;
        }

        inputFile.close();
    }
    else {
        cout << "Error: Unable to open " << fileName << endl;
    }
}

// Returns the frequency for a specific grocery item.
int GroceryTracker::GetItemFrequency(string item) {
    if (itemFrequency.count(item) > 0) {
        return itemFrequency[item];
    }

    return 0;
}

// Displays every grocery item and its numeric frequency.
void GroceryTracker::PrintAllFrequencies() {
    cout << endl;
    cout << "Item Frequency List" << endl;
    cout << "-------------------" << endl;

    for (const auto& pair : itemFrequency) {
        cout << pair.first << " " << pair.second << endl;
    }
}

// Displays grocery frequencies using asterisks.
void GroceryTracker::PrintHistogram() {
    cout << endl;
    cout << "Corner Grocer Purchase Histogram" << endl;
    cout << "--------------------------------" << endl;

    for (const auto& pair : itemFrequency) {
        cout << pair.first << " ";

        for (int i = 0; i < pair.second; ++i) {
            cout << "*";
        }

        cout << endl;
    }
}

// Creates the required frequency.dat backup file.
void GroceryTracker::CreateBackupFile(string fileName) {
    ofstream outputFile(fileName);

    if (outputFile.is_open()) {
        for (const auto& pair : itemFrequency) {
            outputFile << pair.first << " " << pair.second << endl;
        }

        outputFile.close();
    }
    else {
        cout << "Error: Unable to create backup file." << endl;
    }
}

int main() {
    GroceryTracker tracker;

    // Load the grocery purchase records.
    tracker.LoadData("CS210_Project_Three_Input_File.txt");

    // Automatically create the required backup file.
    tracker.CreateBackupFile("frequency.dat");

    int menuChoice = 0;
    string itemName;

    // Continue displaying the menu until the user chooses option 4.
    while (menuChoice != 4) {
        cout << endl;
        cout << "====================================" << endl;
        cout << " Corner Grocer Item Tracking Program" << endl;
        cout << "====================================" << endl;
        cout << "1. Look up an item frequency" << endl;
        cout << "2. Display all item frequencies" << endl;
        cout << "3. Display item histogram" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        // Validate that the user entered a number.
        if (!(cin >> menuChoice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number from 1 through 4." << endl;
            continue;
        }

        // Menu Option 1: Search for one grocery item.
        if (menuChoice == 1) {
            cout << "Enter the item you wish to look up: ";
            cin >> itemName;

            cout << itemName << " appears "
                 << tracker.GetItemFrequency(itemName)
                 << " time(s)." << endl;
        }

        // Menu Option 2: Display all item frequencies.
        else if (menuChoice == 2) {
            tracker.PrintAllFrequencies();
        }

        // Menu Option 3: Display histogram.
        else if (menuChoice == 3) {
            tracker.PrintHistogram();
        }

        // Menu Option 4: Exit the program.
        else if (menuChoice == 4) {
            cout << endl;
            cout << "Thank you for using the Corner Grocer Item Tracking Program." << endl;
        }

        // Handle menu numbers outside the range 1 through 4.
        else {
            cout << "Invalid selection. Please enter a number from 1 through 4." << endl;
        }
    }

    return 0;
}