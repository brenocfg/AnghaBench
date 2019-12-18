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
struct rtw_coex_rfe {scalar_t__ ant_switch_with_bt; } ;
struct rtw_coex_dm {scalar_t__ bt_status; int /*<<< orphan*/ * wl_rssi_state; } ;
struct rtw_coex_stat {int bt_ble_scan_type; int /*<<< orphan*/  wl_gl_busy; } ;
struct rtw_coex {struct rtw_coex_rfe rfe; struct rtw_coex_dm dm; struct rtw_coex_stat stat; } ;
struct rtw_dev {struct rtw_chip_info* chip; struct rtw_efuse efuse; struct rtw_coex coex; } ;
struct rtw_chip_info {int /*<<< orphan*/ * wl_rf_para_rx; } ;

/* Variables and functions */
 scalar_t__ COEX_BTSTATUS_NCON_IDLE ; 
 scalar_t__ COEX_RSSI_HIGH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COEX_SET_ANT_2G ; 
 int /*<<< orphan*/  COEX_SET_ANT_2G_FREERUN ; 
 int /*<<< orphan*/  rtw_coex_set_ant_path (struct rtw_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_set_rf_para (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_table (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw_coex_tdma (struct rtw_dev*,int,int) ; 

__attribute__((used)) static void rtw_coex_action_bt_idle(struct rtw_dev *rtwdev)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;
	struct rtw_coex_dm *coex_dm = &coex->dm;
	struct rtw_efuse *efuse = &rtwdev->efuse;
	struct rtw_chip_info *chip = rtwdev->chip;
	struct rtw_coex_rfe *coex_rfe = &coex->rfe;
	u8 table_case = 0xff, tdma_case = 0xff;

	if (coex_rfe->ant_switch_with_bt &&
	    coex_dm->bt_status == COEX_BTSTATUS_NCON_IDLE) {
		if (efuse->share_ant &&
		    COEX_RSSI_HIGH(coex_dm->wl_rssi_state[1])) {
			table_case = 0;
			tdma_case = 0;
		} else if (!efuse->share_ant) {
			table_case = 100;
			tdma_case = 100;
		}
	}

	if (table_case != 0xff && tdma_case != 0xff) {
		rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G_FREERUN);
		rtw_coex_table(rtwdev, table_case);
		rtw_coex_tdma(rtwdev, false, tdma_case);
		return;
	}

	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);

	if (efuse->share_ant) {
		/* Shared-Ant */
		if (!coex_stat->wl_gl_busy) {
			table_case = 10;
			tdma_case = 3;
		} else if (coex_dm->bt_status == COEX_BTSTATUS_NCON_IDLE) {
			table_case = 6;
			tdma_case = 7;
		} else {
			table_case = 12;
			tdma_case = 7;
		}
	} else {
		/* Non-Shared-Ant */
		if (!coex_stat->wl_gl_busy) {
			table_case = 112;
			tdma_case = 104;
		} else if ((coex_stat->bt_ble_scan_type & 0x2) &&
			    coex_dm->bt_status == COEX_BTSTATUS_NCON_IDLE) {
			table_case = 114;
			tdma_case = 103;
		} else {
			table_case = 112;
			tdma_case = 103;
		}
	}

	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);
	rtw_coex_table(rtwdev, table_case);
	rtw_coex_tdma(rtwdev, false, tdma_case);
}