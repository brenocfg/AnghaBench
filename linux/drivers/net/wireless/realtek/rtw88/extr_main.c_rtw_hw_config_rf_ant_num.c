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
typedef  scalar_t__ u8 ;
struct rtw_hal {scalar_t__ rf_path_num; void* antenna_rx; void* antenna_tx; int /*<<< orphan*/  rf_type; } ;
struct rtw_dev {struct rtw_hal hal; } ;

/* Variables and functions */
 void* BB_PATH_A ; 
 scalar_t__ EFUSE_HW_CAP_IGNORE ; 
 int /*<<< orphan*/  RF_1T1R ; 
 int /*<<< orphan*/  WARN (int,char*) ; 

__attribute__((used)) static void rtw_hw_config_rf_ant_num(struct rtw_dev *rtwdev, u8 hw_ant_num)
{
	struct rtw_hal *hal = &rtwdev->hal;

	if (hw_ant_num == EFUSE_HW_CAP_IGNORE ||
	    hw_ant_num >= hal->rf_path_num)
		return;

	switch (hw_ant_num) {
	case 1:
		hal->rf_type = RF_1T1R;
		hal->rf_path_num = 1;
		hal->antenna_tx = BB_PATH_A;
		hal->antenna_rx = BB_PATH_A;
		break;
	default:
		WARN(1, "invalid hw configuration from efuse\n");
		break;
	}
}