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
struct rtw_coex_dm {int cur_wl_rx_low_gain_en; } ;
struct rtw_coex {struct rtw_coex_dm dm; } ;
struct rtw_dev {struct rtw_coex coex; } ;

/* Variables and functions */
 int /*<<< orphan*/  RF_PATH_A ; 
 int /*<<< orphan*/  RF_PATH_B ; 
 int /*<<< orphan*/  rtw_write_rf (struct rtw_dev*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void rtw8822c_coex_cfg_wl_rx_gain(struct rtw_dev *rtwdev, bool low_gain)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_dm *coex_dm = &coex->dm;

	if (low_gain == coex_dm->cur_wl_rx_low_gain_en)
		return;

	coex_dm->cur_wl_rx_low_gain_en = low_gain;

	if (coex_dm->cur_wl_rx_low_gain_en) {
		/* set Rx filter corner RCK offset */
		rtw_write_rf(rtwdev, RF_PATH_A, 0xde, 0xfffff, 0x22);
		rtw_write_rf(rtwdev, RF_PATH_A, 0x1d, 0xfffff, 0x36);
		rtw_write_rf(rtwdev, RF_PATH_B, 0xde, 0xfffff, 0x22);
		rtw_write_rf(rtwdev, RF_PATH_B, 0x1d, 0xfffff, 0x36);
	} else {
		/* set Rx filter corner RCK offset */
		rtw_write_rf(rtwdev, RF_PATH_A, 0xde, 0xfffff, 0x20);
		rtw_write_rf(rtwdev, RF_PATH_A, 0x1d, 0xfffff, 0x0);
		rtw_write_rf(rtwdev, RF_PATH_B, 0x1d, 0xfffff, 0x0);
	}
}