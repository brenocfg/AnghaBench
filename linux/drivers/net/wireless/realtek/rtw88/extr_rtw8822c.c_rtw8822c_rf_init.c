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
 int /*<<< orphan*/  rtw8822c_rf_dac_cal (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw8822c_rf_x2_check (struct rtw_dev*) ; 

__attribute__((used)) static void rtw8822c_rf_init(struct rtw_dev *rtwdev)
{
	rtw8822c_rf_dac_cal(rtwdev);
	rtw8822c_rf_x2_check(rtwdev);
}