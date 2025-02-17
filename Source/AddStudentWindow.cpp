#include "AddStudentWindow.h"
#include <QFile>
#include <QDataStream>
#include <QMessageBox>

AddStudentWindow::AddStudentWindow(QWidget *parent)
    : QWidget(parent),
    headLabel1(new QLabel("A D D  S T U D E N T", this)),
    label1(new QLabel("NAME", this)),
    label2(new QLabel("ROLL NO", this)),
    label3(new QLabel("ADDRESS", this)),
    label4(new QLabel("UNIQUE PIN CODE", this)),
    imageLabel(new QLabel(this)),
    imageLabel1(new QLabel(this)),
    nameEdit(new QLineEdit(this)),
    rollNumberEdit(new QLineEdit(this)),
    addressEdit(new QLineEdit(this)),
    uniquePinCodeEdit(new QLineEdit(this)),
    saveButton(new QPushButton("Save", this)) {
   // this->setObjectName("mainWindow");
    this->setStyleSheet(winstyle);
    headLabel1->setGeometry(110,21,175,25);
    headLabel1->setStyleSheet("font-size: 18px; font-weight:600;color:#FFFFFF; background-color:transparent;");
    label1->setGeometry(85,60,183,11);
    label2->setGeometry(85,110,183,11);
    label3->setGeometry(85,160,183,11);
    label4->setGeometry(85,210,183,11);
    label1->setStyleSheet(labelstyle);
    label2->setStyleSheet(labelstyle);
    label3->setStyleSheet(labelstyle);
    label4->setStyleSheet(labelstyle);
    saveButton->setGeometry(164,270,111,34);
    nameEdit->setGeometry(85,76,190,25);
    rollNumberEdit->setGeometry(85,126,190,25);
    addressEdit->setGeometry(85,176,190,25);
    uniquePinCodeEdit->setGeometry(85,226,190,25);
    nameEdit->setStyleSheet(inputstyle);
    rollNumberEdit->setStyleSheet(inputstyle);
    addressEdit->setStyleSheet(inputstyle);
    uniquePinCodeEdit->setStyleSheet(inputstyle);
    saveButton->setStyleSheet(loginbtn);
    QPixmap pixmap("C:/Users/HP/Documents/att/pic4.png");
    //int newWidthHeigt = 50; // Desired width
    imageLabel->setPixmap(pixmap);
    imageLabel->setGeometry(255, -60, 298, 344); // Position and size of label
    imageLabel->setStyleSheet("background-color:transparent;");
    QPixmap pixmap1("C:/Users/HP/Documents/att/pic2.png");  // Load the c logo
    int newWidthHeigt = 50;
    imageLabel1->setPixmap(pixmap1);  // Set the scaled pixmap on the label
    imageLabel1->setGeometry(30, 10,  newWidthHeigt,  newWidthHeigt); // Position and size the label
    connect(saveButton, &QPushButton::clicked, this, &AddStudentWindow::onSaveButtonClicked);

   // setLayout(layout);
    setFixedSize(400, 320);
    setWindowTitle("Add Student");
}

void AddStudentWindow::onSaveButtonClicked() {
    QString name = nameEdit->text().trimmed();
    QString rollNumber = rollNumberEdit->text().trimmed();
    QString address = addressEdit->text().trimmed();
    QString uniquePinCode = uniquePinCodeEdit->text().trimmed();

    if (name.isEmpty() || rollNumber.isEmpty() || address.isEmpty() || uniquePinCode.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields are required.");
        return;
    }

    if (isStudentExists(rollNumber, uniquePinCode)) {
        QMessageBox::warning(this, "Duplicate Entry", "Student with the same Roll Number or Unique Pin Code already exists.");
        return;
    }

    Student student;
    student.name = name;
    student.rollNumber = rollNumber;
    student.address = address;
    student.uniquePinCode = uniquePinCode;

    saveStudent(student);

    QMessageBox::information(this, "Success", "Student information saved successfully.");
    this->close();
}

bool AddStudentWindow::isStudentExists(const QString &rollNumber, const QString &uniquePinCode) {
    QFile file("students.dat");
    if (!file.open(QIODevice::ReadOnly)) {
        return false; // Assuming file does not exist means no duplicates
    }

    QDataStream in(&file);
    while (!in.atEnd()) {
        Student tempStudent;
        tempStudent.load(in);
        if (tempStudent.rollNumber == rollNumber || tempStudent.uniquePinCode == uniquePinCode) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void AddStudentWindow::saveStudent(const Student &student) {
    QFile file("students.dat");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QMessageBox::warning(this, "File Error", "Unable to open file for writing.");
        return;
    }

    QDataStream out(&file);
    student.save(out);
    file.close();
}
