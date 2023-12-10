#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

// Class to represent an item in the supermarket
class Item {
public:
    string name;
    double price;
    int quantity;

    Item(string n, double p, int q) : name(n), price(p), quantity(q) {}

    // Function to calculate the total cost of the item
    double getTotalCost() const {
        return price * quantity;
    }
};

// Function to display the available items as a menu
void displayMenu(const vector<Item>& availableItems) {
    cout << "Available Items:\n";
    cout << "-----------------\n";
    for (const Item& item : availableItems) {
        cout << item.name << " (Price: " << item.price << ")\n";
    }
    cout << "-----------------\n";
}

// Function to add items to the cart
void addToCart(vector<Item>& items, const vector<Item>& availableItems) {
    displayMenu(availableItems);

    string itemName;
    cout << "Enter the name of the item to add to the cart: ";
    getline(cin, itemName);

    // Find the selected item in the available items
    auto it = find_if(availableItems.begin(), availableItems.end(),
                      [&itemName](const Item& item) { return item.name == itemName; });

    // If the item is found, prompt for quantity and add it to the cart
    if (it != availableItems.end()) {
        int quantity;
        cout << "Enter the quantity: ";
        cin >> quantity;

        // Clear the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Add the item to the cart
        items.push_back(Item(it->name, it->price, quantity));
        cout << it->name << " added to the cart.\n";
    } else {
        cout << "Item not found in the menu.\n";
    }
}

// Function to add a new item to the available items list
void addNewItem(vector<Item>& availableItems) {
    string itemName;
    double itemPrice;

    cout << "Enter the name of the new item: ";
    getline(cin, itemName);

    cout << "Enter the price of the new item: ";
    cin >> itemPrice;

    // Clear the input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Add the new item to the available items list
    availableItems.push_back(Item(itemName, itemPrice, 0));
    cout << itemName << " added to the available items.\n";
}

// Function to display the bill and calculate the total amount
void generateBill(const vector<Item>& items) {
    cout << "----------------------------------------\n";
    cout << setw(20) << "Item" << setw(10) << "Price" << setw(10) << "Quantity" << setw(15) << "Total Cost" << endl;
    cout << "----------------------------------------\n";

    double totalAmount = 0.0;

    for (const Item& item : items) {
        cout << setw(20) << item.name << setw(10) << item.price << setw(10) << item.quantity << setw(15) << item.getTotalCost() << endl;
        totalAmount += item.getTotalCost();
    }

    cout << "----------------------------------------\n";
    cout << setw(40) << "Total Amount: " << totalAmount << endl;
    cout << "----------------------------------------\n";
}

int main() {
    // Sample available items in the supermarket
    vector<Item> availableItems = {
        {"Apple", 25, 0},
        {"Banana", 10, 0},
        {"Bread", 20, 0}
    };

    vector<Item> items;  // Vector to store items in the cart
    int choice;

    do {
        cout << "Supermarket Billing System\n";
        cout << "1. Add product to the cart\n";
        cout << "2. Generate bill\n";
        cout << "3. Add new item to the menu\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Clear the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                addToCart(items, availableItems);
                break;

            case 2:
                generateBill(items);
                break;

            case 3:
                addNewItem(availableItems);
                break;

            case 4:
                cout << "Exiting the program.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

