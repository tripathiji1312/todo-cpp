#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

void heading(string charac) {
    cout << "######################### " << charac << " #########################" << endl;
}

bool check_user(string username) {
    ifstream fil("users.log");
    string unames;
    while (getline(fil, unames)) {
        if (unames == username) {
            fil.close();
            return true;
        }
    }
    fil.close();
    return false;
}

void new_user(string username) {
    ofstream fil("users.log", ios::app); // Open file in append mode
    fil << username << endl;
    fil.close();
}

string get_time() {
    time_t timestamp;
    char output[50];
    struct tm *datetime;
    time(&timestamp);
    datetime = localtime(&timestamp);
    strftime(output, sizeof(output), "%d_%m", datetime);
    return string(output);
}

string filname_create(string time, string username) {
    return username + "_" + time + ".txt";
}

void add_task(string timeeee, string username) {
    heading("ADDING");
    while (true) {
        cout << "Type your task: ";
        string tas;
        cin.ignore();
        getline(cin, tas);
        string filname = filname_create(timeeee, username);
        ofstream file(filname, ios::app); // Open file in append mode
        file << "--> " << tas << endl;
        file.close();
        cout << "Do you want to add another task? (y=yes, n=no): ";
        string cho;
        cin >> cho;
        if (cho == "y") {
            continue;
        } else if (cho == "n") {
            break;
        }
    }
}

void check_list(string username) {
    heading("FINDING");
    while (true) {
        cout << "Do you want today's or some other day's tasks? (today = 1, other = 0): ";
        int checkingtime;
        cin >> checkingtime;
        if (checkingtime == 1) {
            string timee = get_time();
            string filename = filname_create(timee, username);
            ifstream file(filename);
            if (!file) {
                cout << "No tasks found for today." << endl;
            } else {
                string task;
                heading("READING");
                while (getline(file, task)) {
                    cout << task << endl;
                }
            }
            file.close();
        } else if (checkingtime == 0) {
            string date, month;
            cout << "Enter the date (dd): ";
            cin >> date;
            cout << "Enter the month (mm): ";
            cin >> month;
            string timee = date + "_" + month;
            string filename = filname_create(timee, username);
            ifstream file(filename);
            if (!file) {
                cout << "No tasks found for this date." << endl;
            } else {
                string task;
                heading("READING");
                while (getline(file, task)) {
                    cout << task << endl;
                }
            }
            file.close();
            cout << "Select one: " << endl;
            cout << "0 = Add new task today" << endl;
            cout << "1 = Add new task other day" << endl;
            cout << "2 = Check todo for other day" << endl;
            cout << "-> ";
            int choicee;
            cin >> choicee;
            if (choicee == 0) {
                string tim = get_time();
                add_task(tim, username);
            } else if (choicee == 1) {
                cout << "Enter the date (dd): ";
                cin >> date;
                cout << "Enter the month (mm): ";
                cin >> month;
                string timee_other = date + "_" + month;
                add_task(timee_other, username);
            } else if (choicee == 2) {
                cout << "Enter the date (dd): ";
                cin >> date;
                cout << "Enter the month (mm): ";
                cin >> month;
                string timee_other = date + "_" + month;
                string filenam = filname_create(timee_other, username);
                ifstream fi(filenam);
                if (!fi) {
                    cout << "No tasks found for this date." << endl;
                } else {
                    string tak;
                    while (getline(fi, tak)) {
                        cout << tak << endl;
                    }
                }
                fi.close();
            } else {
                break;
            }
        } else {
            cout << "Select a correct choice!!" << endl;
            continue;
        }
    }
}

int main() {
    string user_type;
    heading("WELCOME, TODO LIST");
    while (true) {
        cout << "Are you an existing or new user? (ex/n): ";
        cin >> user_type;
        cout << "Enter your username: ";
        string n_username;
        cin >> n_username;
        if (user_type == "n") {
            bool user_check = check_user(n_username);
            if (user_check) {
                cout << "You are already a user!!" << endl;
            } else {
                new_user(n_username);
                check_list(n_username);
            }
        } else if (user_type == "ex") {
            bool user_check = check_user(n_username);
            if (user_check) {
                check_list(n_username);
            } else {
                cout << "Account with this username doesn't exist!! \nCreating new account." << endl;
                new_user(n_username);
                check_list(n_username);
            }
        } else {
            cout << "Select a correct option!! :(" << endl;
            continue;
        }
    }
    return 0;
}
