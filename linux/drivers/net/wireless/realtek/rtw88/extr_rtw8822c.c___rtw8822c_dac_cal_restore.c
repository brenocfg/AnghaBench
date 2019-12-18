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
 int /*<<< orphan*/  rtw8822c_dac_cal_restore_path (struct rtw_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __rtw8822c_dac_cal_restore(struct rtw_dev *rtwdev)
{
	if (!rtw8822c_dac_cal_restore_path(rtwdev, RF_PATH_A))
		return false;

	if (!rtw8822c_dac_cal_restore_path(rtwdev, RF_PATH_B))
		return false;

	return true;
}