#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct rtw_efuse {scalar_t__ share_ant; } ;
struct TYPE_2__ {scalar_t__ current_band_width; } ;
struct rtw_coex_stat {scalar_t__ wl_gl_busy; scalar_t__ bt_ble_exist; scalar_t__ bt_a2dp_active; scalar_t__ bt_418_hid_exist; } ;
struct rtw_coex {struct rtw_coex_stat stat; } ;
struct rtw_dev {TYPE_1__ hal; struct rtw_chip_info* chip; struct rtw_efuse efuse; struct rtw_coex coex; } ;
struct rtw_chip_info {int /*<<< orphan*/ * wl_rf_para_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  COEX_SET_ANT_2G ; 
 int /*<<< orphan*/  rtw_coex_set_ant_path (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_set_rf_para (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_table (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw_coex_tdma (struct rtw_dev*,int,int) ; 

__attribute__((used)) static void rtw_coex_action_bt_hid(struct rtw_dev *rtwdev)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;
	struct rtw_efuse *efuse = &rtwdev->efuse;
	struct rtw_chip_info *chip = rtwdev->chip;
	u8 table_case, tdma_case;
	u32 wl_bw;

	wl_bw = rtwdev->hal.current_band_width;

	if (efuse->share_ant) {
		/* Shared-Ant */
		if (coex_stat->bt_ble_exist) {
			/* RCU */
			if (!coex_stat->wl_gl_busy)
				table_case = 14;
			else
				table_case = 15;

			if (coex_stat->bt_a2dp_active || wl_bw == 0)
				tdma_case = 18;
			else if (coex_stat->wl_gl_busy)
				tdma_case = 8;
			else
				tdma_case = 4;
		} else {
			if (coex_stat->bt_a2dp_active || wl_bw == 0) {
				table_case = 8;
				tdma_case = 4;
			} else {
				/* for 4/18 HID */
				if (coex_stat->bt_418_hid_exist &&
				    coex_stat->wl_gl_busy)
					table_case = 12;
				else
					table_case = 10;
				tdma_case = 4;
			}
		}
	} else {
		/* Non-Shared-Ant */
		if (coex_stat->bt_a2dp_active) {
			table_case = 113;
			tdma_case = 118;
		} else if (coex_stat->bt_ble_exist) {
			/* BLE */
			table_case = 113;

			if (coex_stat->wl_gl_busy)
				tdma_case = 106;
			else
				tdma_case = 104;
		} else {
			table_case = 113;
			tdma_case = 104;
		}
	}

	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);
	rtw_coex_table(rtwdev, table_case);
	rtw_coex_tdma(rtwdev, false, tdma_case);
}