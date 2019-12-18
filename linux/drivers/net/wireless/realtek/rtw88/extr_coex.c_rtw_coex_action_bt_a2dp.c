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
typedef  int u32 ;
struct rtw_efuse {scalar_t__ share_ant; } ;
struct rtw_coex_dm {int /*<<< orphan*/ * wl_rssi_state; } ;
struct rtw_coex_stat {scalar_t__ wl_noisy_level; scalar_t__ wl_gl_busy; } ;
struct rtw_coex {struct rtw_coex_dm dm; struct rtw_coex_stat stat; } ;
struct rtw_dev {struct rtw_chip_info* chip; struct rtw_efuse efuse; struct rtw_coex coex; } ;
struct rtw_chip_info {int /*<<< orphan*/ * wl_rf_para_rx; } ;

/* Variables and functions */
 scalar_t__ COEX_RSSI_HIGH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COEX_SET_ANT_2G ; 
 int TDMA_4SLOT ; 
 int /*<<< orphan*/  rtw_coex_set_ant_path (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_set_rf_para (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_table (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw_coex_tdma (struct rtw_dev*,int,int) ; 

__attribute__((used)) static void rtw_coex_action_bt_a2dp(struct rtw_dev *rtwdev)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;
	struct rtw_coex_dm *coex_dm = &coex->dm;
	struct rtw_efuse *efuse = &rtwdev->efuse;
	struct rtw_chip_info *chip = rtwdev->chip;
	u8 table_case, tdma_case;
	u32 slot_type = 0;

	if (efuse->share_ant) {
		/* Shared-Ant */
		if (coex_stat->wl_gl_busy && coex_stat->wl_noisy_level == 0)
			table_case = 10;
		else
			table_case = 9;

		slot_type = TDMA_4SLOT;

		if (coex_stat->wl_gl_busy)
			tdma_case = 13;
		else
			tdma_case = 14;
	} else {
		/* Non-Shared-Ant */
		table_case = 112;

		if (COEX_RSSI_HIGH(coex_dm->wl_rssi_state[1]))
			tdma_case = 112;
		else
			tdma_case = 113;
	}

	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);
	rtw_coex_table(rtwdev, table_case);
	rtw_coex_tdma(rtwdev, false, tdma_case | slot_type);
}