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
typedef  int u8 ;
struct rtw_efuse {scalar_t__ share_ant; } ;
struct rtw_coex_stat {scalar_t__ wl_gl_busy; } ;
struct rtw_coex {struct rtw_coex_stat stat; } ;
struct rtw_dev {struct rtw_chip_info* chip; struct rtw_efuse efuse; struct rtw_coex coex; } ;
struct rtw_chip_info {int /*<<< orphan*/ * wl_rf_para_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  COEX_SET_ANT_2G ; 
 int /*<<< orphan*/  rtw_coex_set_ant_path (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_set_rf_para (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_table (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw_coex_tdma (struct rtw_dev*,int,int) ; 

__attribute__((used)) static void rtw_coex_action_bt_a2dpsink(struct rtw_dev *rtwdev)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;
	struct rtw_efuse *efuse = &rtwdev->efuse;
	struct rtw_chip_info *chip = rtwdev->chip;
	u8 table_case, tdma_case;
	bool ap_enable = false;

	if (efuse->share_ant) { /* Shared-Ant */
		if (ap_enable) {
			table_case = 2;
			tdma_case = 0;
		} else if (coex_stat->wl_gl_busy) {
			table_case = 28;
			tdma_case = 20;
		} else {
			table_case = 28;
			tdma_case = 26;
		}
	} else { /* Non-Shared-Ant */
		if (ap_enable) {
			table_case = 100;
			tdma_case = 100;
		} else {
			table_case = 119;
			tdma_case = 120;
		}
	}

	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);
	rtw_coex_table(rtwdev, table_case);
	rtw_coex_tdma(rtwdev, false, tdma_case);
}