#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RF_PATH_A ; 
 int /*<<< orphan*/  RF_PATH_B ; 
 int /*<<< orphan*/  rtw8822c_dpk_cal_coef1 (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw8822c_dpk_calibrate (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw8822c_dpk_on (struct rtw_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw8822c_dpk_path_select(struct rtw_dev *rtwdev)
{
	rtw8822c_dpk_calibrate(rtwdev, RF_PATH_A);
	rtw8822c_dpk_calibrate(rtwdev, RF_PATH_B);
	rtw8822c_dpk_on(rtwdev, RF_PATH_A);
	rtw8822c_dpk_on(rtwdev, RF_PATH_B);
	rtw8822c_dpk_cal_coef1(rtwdev);
}