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
 int rtw_chip_board_info_setup (struct rtw_dev*) ; 
 int rtw_chip_efuse_info_setup (struct rtw_dev*) ; 
 int rtw_chip_parameter_setup (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 

int rtw_chip_info_setup(struct rtw_dev *rtwdev)
{
	int ret;

	ret = rtw_chip_parameter_setup(rtwdev);
	if (ret) {
		rtw_err(rtwdev, "failed to setup chip parameters\n");
		goto err_out;
	}

	ret = rtw_chip_efuse_info_setup(rtwdev);
	if (ret) {
		rtw_err(rtwdev, "failed to setup chip efuse info\n");
		goto err_out;
	}

	ret = rtw_chip_board_info_setup(rtwdev);
	if (ret) {
		rtw_err(rtwdev, "failed to setup chip board info\n");
		goto err_out;
	}

	return 0;

err_out:
	return ret;
}