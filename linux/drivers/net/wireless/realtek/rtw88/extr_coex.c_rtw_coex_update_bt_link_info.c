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
typedef  size_t u8 ;
struct TYPE_2__ {size_t min_rssi; } ;
struct rtw_coex_dm {size_t* bt_rssi_state; size_t* wl_rssi_state; int /*<<< orphan*/  bt_status; } ;
struct rtw_coex_stat {size_t bt_rssi; int* cnt_bt; size_t bt_ble_scan_type; int bt_init_scan; int bt_info_lb2; int bt_link_exist; int bt_pan_exist; int bt_a2dp_exist; int bt_hid_exist; int bt_hfp_exist; scalar_t__ bt_profile_num; scalar_t__ bt_ble_scan_en; } ;
struct rtw_coex {struct rtw_coex_dm dm; struct rtw_coex_stat stat; } ;
struct rtw_dev {TYPE_1__ dm_info; struct rtw_chip_info* chip; struct rtw_coex coex; } ;
struct rtw_chip_info {size_t* bt_rssi_step; size_t* wl_rssi_step; } ;

/* Variables and functions */
 int /*<<< orphan*/  COEX_BTSTATUS_ACL_BUSY ; 
 int /*<<< orphan*/  COEX_BTSTATUS_ACL_SCO_BUSY ; 
 int /*<<< orphan*/  COEX_BTSTATUS_CON_IDLE ; 
 int /*<<< orphan*/  COEX_BTSTATUS_INQ_PAGE ; 
 int /*<<< orphan*/  COEX_BTSTATUS_MAX ; 
 int /*<<< orphan*/  COEX_BTSTATUS_NCON_IDLE ; 
 int /*<<< orphan*/  COEX_BTSTATUS_SCO_BUSY ; 
 size_t COEX_CNT_BT_INFOUPDATE ; 
 int COEX_INFO_A2DP ; 
 int COEX_INFO_ACL_BUSY ; 
 int COEX_INFO_CONNECTION ; 
 int COEX_INFO_FTP ; 
 int COEX_INFO_HID ; 
 int COEX_INFO_INQ_PAGE ; 
 int COEX_INFO_SCO_BUSY ; 
 int COEX_INFO_SCO_ESCO ; 
 size_t COEX_RSSI_STEP ; 
 int /*<<< orphan*/  RTW_DBG_COEX ; 
 scalar_t__ rtw_coex_get_bt_scan_type (struct rtw_dev*,size_t*) ; 
 size_t rtw_coex_next_rssi_state (struct rtw_dev*,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  rtw_dbg (struct rtw_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw_coex_update_bt_link_info(struct rtw_dev *rtwdev)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;
	struct rtw_coex_dm *coex_dm = &coex->dm;
	struct rtw_chip_info *chip = rtwdev->chip;
	u8 i;
	u8 rssi_state;
	u8 rssi_step;
	u8 rssi;

	/* update wl/bt rssi by btinfo */
	for (i = 0; i < COEX_RSSI_STEP; i++) {
		rssi_state = coex_dm->bt_rssi_state[i];
		rssi_step = chip->bt_rssi_step[i];
		rssi = coex_stat->bt_rssi;
		rssi_state = rtw_coex_next_rssi_state(rtwdev, rssi_state,
						      rssi, rssi_step);
		coex_dm->bt_rssi_state[i] = rssi_state;
	}

	for (i = 0; i < COEX_RSSI_STEP; i++) {
		rssi_state = coex_dm->wl_rssi_state[i];
		rssi_step = chip->wl_rssi_step[i];
		rssi = rtwdev->dm_info.min_rssi;
		rssi_state = rtw_coex_next_rssi_state(rtwdev, rssi_state,
						      rssi, rssi_step);
		coex_dm->wl_rssi_state[i] = rssi_state;
	}

	if (coex_stat->bt_ble_scan_en &&
	    coex_stat->cnt_bt[COEX_CNT_BT_INFOUPDATE] % 3 == 0) {
		u8 scan_type;

		if (rtw_coex_get_bt_scan_type(rtwdev, &scan_type)) {
			coex_stat->bt_ble_scan_type = scan_type;
			if ((coex_stat->bt_ble_scan_type & 0x1) == 0x1)
				coex_stat->bt_init_scan = true;
			else
				coex_stat->bt_init_scan = false;
		}
	}

	coex_stat->bt_profile_num = 0;

	/* set link exist status */
	if (!(coex_stat->bt_info_lb2 & COEX_INFO_CONNECTION)) {
		coex_stat->bt_link_exist = false;
		coex_stat->bt_pan_exist = false;
		coex_stat->bt_a2dp_exist = false;
		coex_stat->bt_hid_exist = false;
		coex_stat->bt_hfp_exist = false;
	} else {
		/* connection exists */
		coex_stat->bt_link_exist = true;
		if (coex_stat->bt_info_lb2 & COEX_INFO_FTP) {
			coex_stat->bt_pan_exist = true;
			coex_stat->bt_profile_num++;
		} else {
			coex_stat->bt_pan_exist = false;
		}

		if (coex_stat->bt_info_lb2 & COEX_INFO_A2DP) {
			coex_stat->bt_a2dp_exist = true;
			coex_stat->bt_profile_num++;
		} else {
			coex_stat->bt_a2dp_exist = false;
		}

		if (coex_stat->bt_info_lb2 & COEX_INFO_HID) {
			coex_stat->bt_hid_exist = true;
			coex_stat->bt_profile_num++;
		} else {
			coex_stat->bt_hid_exist = false;
		}

		if (coex_stat->bt_info_lb2 & COEX_INFO_SCO_ESCO) {
			coex_stat->bt_hfp_exist = true;
			coex_stat->bt_profile_num++;
		} else {
			coex_stat->bt_hfp_exist = false;
		}
	}

	if (coex_stat->bt_info_lb2 & COEX_INFO_INQ_PAGE) {
		coex_dm->bt_status = COEX_BTSTATUS_INQ_PAGE;
	} else if (!(coex_stat->bt_info_lb2 & COEX_INFO_CONNECTION)) {
		coex_dm->bt_status = COEX_BTSTATUS_NCON_IDLE;
	} else if (coex_stat->bt_info_lb2 == COEX_INFO_CONNECTION) {
		coex_dm->bt_status = COEX_BTSTATUS_CON_IDLE;
	} else if ((coex_stat->bt_info_lb2 & COEX_INFO_SCO_ESCO) ||
		   (coex_stat->bt_info_lb2 & COEX_INFO_SCO_BUSY)) {
		if (coex_stat->bt_info_lb2 & COEX_INFO_ACL_BUSY)
			coex_dm->bt_status = COEX_BTSTATUS_ACL_SCO_BUSY;
		else
			coex_dm->bt_status = COEX_BTSTATUS_SCO_BUSY;
	} else if (coex_stat->bt_info_lb2 & COEX_INFO_ACL_BUSY) {
		coex_dm->bt_status = COEX_BTSTATUS_ACL_BUSY;
	} else {
		coex_dm->bt_status = COEX_BTSTATUS_MAX;
	}

	coex_stat->cnt_bt[COEX_CNT_BT_INFOUPDATE]++;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "coex: bt status(%d)\n", coex_dm->bt_status);
}