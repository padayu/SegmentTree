#include <iostream>
#include <memory>
#include <vector>
#include <math.h>

template<typename tp>
class st_node {
public:
    std::unique_ptr<st_node> leftChild;
    std::unique_ptr<st_node> rightChild;
    long long left;       // including left
    long long right;      // including right
    tp value;

    st_node(long long left, long long right): left(left), right(right) {}
    st_node(long long left, long long right, tp value): left(left), right(right), value(value) {}

    tp combineFunc(tp first, tp second) {
        return first + second;
    }

    void combineChildren() {
        value = combineFunc(leftChild->value, rightChild->value);
    }

    void update(long long from, long long to, tp new_value) {
        if (left > to || right < from || left > right) {
            return;
        }
        else if (left >= from && right <= to) {
            value = new_value;
        }
        else {
            leftChild->update(from, to, new_value);
            rightChild->update(from, to, new_value);
            combineChildren();
        }
    }

    tp getSegment(long long from, long long to) {
        if (left > to || right < from || from > to) {
            return 0;
        }
        else if (left >= from && right <= to) {
            return value;
        }
        else {
            return combineFunc(leftChild->getSegment(from, to), rightChild->getSegment(from, to));
        }
    }
};


template<typename tp>
std::unique_ptr<st_node<tp>> buildST(std::vector<tp>& vec, long long left, long long right) {
    if (left == right) {
        return std::make_unique<st_node<tp>>(left, right, vec[left]);
    }
    else if (left > right) {
        return nullptr;
    }
    else {
        long long middle = (left + right) / 2;
        auto node = std::make_unique<st_node<tp>>(left, right);
        node->rightChild = buildST(vec, left, middle);
        node->leftChild = buildST(vec, middle + 1, right);
        node->combineChildren();
        return node;
    }
}