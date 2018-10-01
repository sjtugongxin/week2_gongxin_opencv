#include <iostream>
#include <chrono>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
int main ( int argc, char** argv )
{
    // 读取argv[1]指定的图像
    cv::Mat image;
    cout<<argv[0]<<"是目录."<<endl;
    
    image = cv::imread(argv[1]);
     //判断图像文件是否正确读取
    if ( image.data == nullptr ) //数据不存在,可能是文件不存在
    {
        cerr<<"文件"<<argv[1]<<"不存在."<<endl;
	//cout<<"文件"<<"不存在."<<endl;
        return 0;
    }
    
    // 文件顺利读取, 首先输出一些基本信息
    cout<<"I Love OPENCV"<<endl;
    cout<<"图像宽为"<<image.cols<<",高为"<<image.rows<<",通道数为"<<image.channels()<<endl;
    cv::imshow ( "Rune1.jpg", image );      // 用cv::imshow显示图像
    cv::waitKey ( 0 );                  // 暂停程序,等待一个按键输入
    // 判断image的类型
    if ( image.type() != CV_8UC1 && image.type() != CV_8UC3 )
    {
        // 图像类型不符合要求
        cout<<"请输入一张彩色图或灰度图."<<endl;
        return 0;
    }
    
    //获取图像的copy
    // 使用clone函数来拷贝数据
    cv::Mat image_clone = image.clone();
    image_clone ( cv::Rect ( 0,0,100,100 ) ).setTo ( 255 );
    cv::imshow ( "image", image_clone );
    cv::imwrite("Rune1_copy.jpg(添加白色色块)", image_clone);
    cv::waitKey ( 0 );
    
    //Change your copied image into a binary typed picture
    cv::Mat image_binary = image.clone();
    cv::cvtColor(image,image_binary,CV_BGR2GRAY);
    //三通道的图转化为1通道的灰度图threshold(image_f,image_f,145,255,THRESH_BINARY);//通过阈值操作把灰度图变成二值图namedWindow("original image");  imshow("original image",image_f); 
    cv::threshold(image_binary,image_binary,145,255,CV_THRESH_BINARY);
    cv::imshow ( "image_binary", image_binary);
    cv::imwrite("Rune1_binary.jpg", image_binary);
    cv::waitKey ( 0 );
    
    //Edge Detection
    // a. Find the contours in the image, with the usage of the binary image
    vector<vector<cv::Point>>contours;
    vector<cv::Vec4i>hierarchy;
    cv::Mat grayImage;
    grayImage = image_binary > 100;
    //cv::imshow("grayImage:image_binary > 100", grayImage);
    
    cv::waitKey(0);
    cv::findContours(grayImage, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

    //绘制轮廓图
    cv::Mat dstImage = cv::Mat::zeros(grayImage.size(), CV_8UC3);
    for (int i = 0; i < hierarchy.size(); i++)
    {
        cv::Scalar color = cv::Scalar(rand() % 255, rand() % 255, rand() % 255);
	//cv::Scalar color = cv::Scalar(0, 0, 255);
        cv::drawContours(dstImage, contours, i, color, CV_FILLED, 8, hierarchy);
    }
    //
    cv::imshow("轮廓图", dstImage);
    cv::imwrite("轮廓图.jpg", dstImage);
    cv::waitKey(0);
    
    vector<vector<cv::Point>>contours2;
    vector<cv::Vec4i>hierarchy2;
    cv::Mat grayImage2;
    grayImage2 = image_binary > 100;
    cv::findContours(grayImage2, contours2, hierarchy2, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

    //绘制红色轮廓图
    cv::Mat dstImage2 = cv::Mat::zeros(grayImage2.size(), CV_8UC3);
    cout<<"hierarchy2.size:"<<hierarchy2.size()<<endl;
    int size = hierarchy2.size();
    for (int i = 0; i < size; i++)
    {
        //cv::Scalar color2 = cv::Scalar(rand() % 255, rand() % 255, rand() % 255);
	cv::Scalar color2 = cv::Scalar(0, 0, 255);
        //cv::drawContours(dstImage2, contours2, i, color2, CV_FILLED, 1, hierarchy2);
	cv::drawContours(dstImage2, contours2, i, color2, 1, 1, hierarchy2);
    }
    cv::imshow("绘制红色轮廓图", dstImage2);
    cv::imwrite("红色轮廓图.jpg", dstImage2);
    cv::waitKey(0);
    
    vector<vector<cv::Point>>contours3;
    vector<cv::Vec4i>hierarchy3;
    cv::Mat grayImage3;
    grayImage3 = image_binary > 100;
    cv::findContours(grayImage3, contours3, hierarchy3, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

    //绘制红色数字轮廓图
    cv::Mat dstImage3 = cv::Mat::zeros(grayImage3.size(), CV_8UC3);
    cout<<"hierarchy3.size:"<<hierarchy3.size()<<endl;
    int size3 = hierarchy3.size();
    for (int i = size3-150; i < size3-70; i++)
    {
        //cv::Scalar color2 = cv::Scalar(rand() % 255, rand() % 255, rand() % 255);
	cv::Scalar color3 = cv::Scalar(0, 0, 255);
        cv::drawContours(dstImage3, contours3, i, color3, 1, 8, hierarchy3);
    }
//     cv::Scalar color3 = cv::Scalar(0, 0, 255);
//     cv::drawContours(dstImage3, contours3, size3-74, color3, 1, 1, hierarchy3);
//     cv::Scalar color5 = cv::Scalar(0, 255, 0);
//     cv::drawContours(dstImage3, contours3, size3-72, color5, 1, 1, hierarchy3);
//     cv::Scalar color6 = cv::Scalar(255, 0, 255);
//     cv::drawContours(dstImage3, contours3, size3-71, color6, 1, 1, hierarchy3);
//     cv::Scalar color7 = cv::Scalar(0, 255, 255);
//     cv::drawContours(dstImage3, contours3, size3-70, color7, 1, 1, hierarchy3);
//     dstImage3 ( cv::Rect ( 0,0,220,356 )).setTo ( 255 );
//     dstImage3 ( cv::Rect ( 420,0,640-40,356-13 )).setTo ( 255 );
//     dstImage3 ( cv::Rect ( 0,0,640,120 ) ).setTo ( 255 );
//     dstImage3 ( cv::Rect ( 0,240,640,356 ) ).setTo ( 255 );
    cv::Mat roi_img;
    roi_img = dstImage3(cv::Range(60,210),cv::Range(220,420));
    cv::imshow("绘制数字红色轮廓图", roi_img);
    cv::imwrite("数字红色轮廓图.jpg", roi_img);
    cv::waitKey(0);
    
    
       

// c. Select the nine contours which are the target with the number in them

   
    cv::destroyAllWindows();
    return 0;
}
