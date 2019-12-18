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
typedef  int u16 ;
struct rtw_coex_dm {scalar_t__ cur_bt_lna_lvl; } ;
struct rtw_coex_stat {int bt_disabled; int bt_reenable; int bt_mailbox_reply; scalar_t__ bt_ble_scan_type; } ;
struct rtw_coex {int /*<<< orphan*/  bt_reenable_work; struct rtw_coex_dm dm; struct rtw_coex_stat stat; } ;
struct rtw_dev {int /*<<< orphan*/  hw; struct rtw_coex coex; struct rtw_chip_info* chip; } ;
struct rtw_chip_info {scalar_t__ scbd_support; } ;

/* Variables and functions */
 int COEX_SCBD_ONOFF ; 
 int HZ ; 
 int /*<<< orphan*/  RTW_DBG_COEX ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int rtw_coex_read_scbd (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_dbg (struct rtw_dev*,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void rtw_coex_monitor_bt_enable(struct rtw_dev *rtwdev)
{
	struct rtw_chip_info *chip = rtwdev->chip;
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;
	struct rtw_coex_dm *coex_dm = &coex->dm;
	bool bt_disabled = false;
	u16 score_board;

	if (chip->scbd_support) {
		score_board = rtw_coex_read_scbd(rtwdev);
		bt_disabled = !(score_board & COEX_SCBD_ONOFF);
	}

	if (coex_stat->bt_disabled != bt_disabled) {
		rtw_dbg(rtwdev, RTW_DBG_COEX, "coex: BT state changed (%d) -> (%d)\n",
			coex_stat->bt_disabled, bt_disabled);

		coex_stat->bt_disabled = bt_disabled;
		coex_stat->bt_ble_scan_type = 0;
		coex_dm->cur_bt_lna_lvl = 0;
	}

	if (!coex_stat->bt_disabled) {
		coex_stat->bt_reenable = true;
		ieee80211_queue_delayed_work(rtwdev->hw,
					     &coex->bt_reenable_work, 15 * HZ);
	} else {
		coex_stat->bt_mailbox_reply = false;
		coex_stat->bt_reenable = false;
	}
}