#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Объявление класса Student
class Student {
private:
    string name;
    int age;
    int course;

public:
    // Методы класса Student
    void Keyboard() {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter course: ";
        cin >> course;
    }

    void display() const {
        cout << "Name: " << name << ", Age: " << age << ", Course: " << course;
    }

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    int getCourse() const {
        return course;
    }
};

// Объявление класса StudentDatabase
class StudentDatabase {
private:
    vector<Student> students;

public:
    // Конструкторы и деструктор
    StudentDatabase() {}

    StudentDatabase(const vector<Student>& s) : students(s) {}

    StudentDatabase(const StudentDatabase& other) : students(other.students) {}

    StudentDatabase(StudentDatabase&& other) noexcept : students(std::move(other.students)) {}

    ~StudentDatabase() {}

    // Метод добавления студента в базу данных с вводом данных с клавиатуры
    void addStudent() {
        Student student;
        student.Keyboard();
        students.push_back(student);
    }

    // Метод загрузки базы данных из бинарного файла
    void loadFromBinary(const string& filename) {
        ifstream file(filename, ios::binary);
        if (file.is_open()) {
            students.clear();
            Student student;
            while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
                students.push_back(student);
            }
            file.close();
        }
        else {
            cerr << "Error: Unable to open file for loading\n";
        }
    }

    // Метод сохранения базы данных в бинарный файл
    void saveToBinary(const string& filename) {
        ofstream file(filename, ios::binary);
        if (file.is_open()) {
            for (const auto& student : students) {
                file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
            }
            file.close();
        }
        else {
            cerr << "Error: Unable to open file for saving\n";
        }
    }

    // Метод вывода базы данных на экран
    void display() {
        for (const auto& student : students) {
            student.display();
            cout << endl;
        }
    }

    // Метод поиска студентов в базе данных по имени
    void searchByName(const string& name) {
        bool found = false;
        for (const auto& student : students) {
            if (student.getName() == name) {
                student.display();
                cout << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No students found with the name: " << name << endl;
        }
    }


    // Выполнение задания из 4.2 (поиск самого младшего студента заданного курса)
    void findYoungestStudentInCourse(int course) {
        auto it = std::min_element(students.begin(), students.end(), [course](const Student& s1, const Student& s2) {
            return (s1.getCourse() == course && s2.getCourse() == course && s1.getAge() < s2.getAge());
            });

        if (it != students.end() && it->getCourse() == course) {
            cout << "The youngest student in course " << course << " is: ";
            it->display();
            cout << endl;
        }
        else {
            cout << "No students found in course " << course << endl;
        }
    }
};
int main() {
    StudentDatabase db;

    int numStudents;
    cout << "Enter the number of students to add: ";
    cin >> numStudents;

    for (int i = 0; i < numStudents; ++i) {
        cout << "Adding student " << i + 1 << ":\n";
        db.addStudent();
    }

    // Сохранение базы данных в бинарный файл
    db.saveToBinary("students.bin");

    // Загрузка базы данных из бинарного файла
    db.loadFromBinary("students.bin");

    // Вывод базы данных на экран
    db.display();

    // Поиск студентов по имени
    string searchName;
    cout << "Enter student's name to search: ";
    cin >> searchName;
    db.searchByName(searchName);

    // Выполнение задания из 4.2 (поиск самого младшего студента заданного курса)
    db.findYoungestStudentInCourse(3);

    return 0;
}



//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//class Student {
//private:
//    string name;
//    int age;
//    int course;
//
//public:
//    // Методы класса Student
//    void Keyboard() {
//        cout << "Enter name: ";
//        cin >> name;
//        cout << "Enter age: ";
//        cin >> age;
//        cout << "Enter course: ";
//        cin >> course;
//    }
//
//    void display() const {
//        cout << "Name: " << name << ", Age: " << age << ", Course: " << course << endl;
//    }
//
//    string getName() const {
//        return name;
//    }
//
//    int getAge() const {
//        return age;
//    }
//
//    int getCourse() const {
//        return course;
//    }
//};
//
//class StudentDatabase {
//private:
//    vector<Student> students;
//
//public:
//    // Конструкторы и деструктор
//    StudentDatabase() {}
//    ~StudentDatabase() {}
//
//    // Метод добавления студента в базу данных с вводом данных с клавиатуры
//    void addStudent() {
//        Student student;
//        student.Keyboard();
//        students.push_back(student);
//    }
//
//    // Метод загрузки базы данных из бинарного файла
//    void loadFromBinary(const string& filename) {
//        ifstream file(filename, ios::binary);
//        if (file.is_open()) {
//            students.clear();
//            Student student;
//            while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
//                students.push_back(student);
//            }
//            file.close();
//        } else {
//            cerr << "Error: Unable to open file for loading\n";
//        }
//    }
//
//    // Метод сохранения базы данных в бинарный файл
//    void saveToBinary(const string& filename) {
//        ofstream file(filename, ios::binary);
//        if (file.is_open()) {
//            for (const auto& student : students) {
//                file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
//            }
//            file.close();
//        } else {
//            cerr << "Error: Unable to open file for saving\n";
//        }
//    }
//
//    // Метод вывода базы данных на экран
//    void display() {
//        for (const auto& student : students) {
//            student.display();
//        }
//    }
//
//    // Метод поиска студентов в базе данных по имени
//    void searchByName(const string& name) {
//        bool found = false;
//        for (const auto& student : students) {
//            if (student.getName() == name) {
//                student.display();
//                found = true;
//            }
//        }
//        if (!found) {
//            cout << "No students found with the name: " << name << endl;
//        }
//    }
//
//    // Поиск самого младшего студента на заданном курсе
//    void findYoungestStudentInCourse(int course) {
//        vector<int> courses;
//        for (const auto& student : students) {
//            int studentCourse = student.getCourse();
//            if (find(courses.begin(), courses.end(), studentCourse) == courses.end()) {
//                courses.push_back(studentCourse);
//            }
//        }
//
//        for (int currentCourse : courses) {
//            int minAge = INT_MAX;
//            const Student* youngestStudent = nullptr;
//            for (const auto& student : students) {
//                if (student.getCourse() == currentCourse && student.getAge() < minAge) {
//                    minAge = student.getAge();
//                    youngestStudent = &student;
//                }
//            }
//            if (youngestStudent != nullptr) {
//                cout << "The youngest student in course " << currentCourse << " is: ";
//                youngestStudent->display();
//            } else {
//                cout << "No students found in course " << currentCourse << endl;
//            }
//        }
//    }
//};
//
//int main() {
//    StudentDatabase db;
//
//    int numStudents;
//    cout << "Enter the number of students to add: ";
//    cin >> numStudents;
//
//    for (int i = 0; i < numStudents; ++i) {
//        cout << "Adding student " << i + 1 << ":\n";
//        db.addStudent();
//    }
//
//    // Сохранение базы данных в бинарный файл
//    db.saveToBinary("students.bin");
//
//    // Загрузка базы данных из бинарного файла
//    db.loadFromBinary("students.bin");
//
//    // Вывод базы данных на экран
//    db.display();
//
//    // Поиск студентов по имени
//    string searchName;
//    cout << "Enter student's name to search: ";
//    cin >> searchName;
//    db.searchByName(searchName);
//
//    // Выполнение задания (поиск самого младшего студента на каждом курсе)
//    db.findYoungestStudentInCourse(3);
//
//    return 0;
//}
