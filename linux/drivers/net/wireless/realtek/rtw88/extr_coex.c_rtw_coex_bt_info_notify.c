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
struct rtw_coex_stat {int bt_iqk_state; int* cnt_bt; int bt_disabled; int bt_disabled_pre; int bt_reenable; int** bt_info_c2h; int bt_info_lb2; int bt_info_lb3; int bt_info_hb0; int bt_info_hb1; int bt_info_hb2; int bt_info_hb3; int bt_whck_test; int bt_inq_page; int bt_acl_busy; int bt_fix_2M; int bt_inq; int bt_page; int bt_rssi; int bt_ble_exist; int bt_setup_link; int bt_ble_voice; int bt_ble_scan_en; int bt_multi_link; int bt_opp_exist; int bt_a2dp_active; int bt_slave; int bt_hid_slot; int bt_hid_pair_num; int bt_418_hid_exist; int bt_a2dp_bitpool; int bt_a2dp_sink; scalar_t__ wl_connected; scalar_t__ wl_gl_busy; scalar_t__ wl_hi_pri_task2; scalar_t__ wl_hi_pri_task1; scalar_t__ wl_linkscan_proc; } ;
struct rtw_coex {int /*<<< orphan*/  bt_relink_work; int /*<<< orphan*/  bt_reenable_work; struct rtw_coex_stat stat; } ;
struct rtw_dev {int /*<<< orphan*/  hw; struct rtw_chip_info* chip; struct rtw_coex coex; } ;
struct rtw_chip_info {scalar_t__ bt_rssi_type; } ;

/* Variables and functions */
 int BIT (int) ; 
 int COEX_BTINFO_LENGTH_MAX ; 
 int COEX_BTINFO_SRC_BT_ACT ; 
 int COEX_BTINFO_SRC_BT_IQK ; 
 int COEX_BTINFO_SRC_BT_RSP ; 
 int COEX_BTINFO_SRC_BT_SCBD ; 
 int COEX_BTINFO_SRC_MAX ; 
 int COEX_BTINFO_SRC_WL_FW ; 
 scalar_t__ COEX_BTRSSI_RATIO ; 
 size_t COEX_CNT_BT_AFHUPDATE ; 
 size_t COEX_CNT_BT_IGNWLANACT ; 
 size_t COEX_CNT_BT_INQ ; 
 size_t COEX_CNT_BT_IQK ; 
 size_t COEX_CNT_BT_IQKFAIL ; 
 size_t COEX_CNT_BT_PAGE ; 
 size_t COEX_CNT_BT_POPEVENT ; 
 size_t COEX_CNT_BT_REINIT ; 
 size_t COEX_CNT_BT_RETRY ; 
 size_t COEX_CNT_BT_ROLESWITCH ; 
 size_t COEX_CNT_BT_SETUPLINK ; 
 int COEX_MEDIA_CONNECT ; 
 int COEX_MEDIA_DISCONNECT ; 
 int /*<<< orphan*/  COEX_RSN_BTINFO ; 
 int /*<<< orphan*/  COEX_SCBD_SCAN ; 
 int HZ ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rtw_coex_ignore_wlan_act (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw_coex_monitor_bt_enable (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_run_coex (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_coex_update_bt_link_info (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_coex_update_wl_ch_info (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw_coex_write_scbd (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 

void rtw_coex_bt_info_notify(struct rtw_dev *rtwdev, u8 *buf, u8 length)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;
	struct rtw_chip_info *chip = rtwdev->chip;
	unsigned long bt_relink_time;
	u8 i, rsp_source = 0, type;

	rsp_source = buf[0] & 0xf;
	if (rsp_source >= COEX_BTINFO_SRC_MAX)
		rsp_source = COEX_BTINFO_SRC_WL_FW;

	if (rsp_source == COEX_BTINFO_SRC_BT_IQK) {
		coex_stat->bt_iqk_state = buf[1];
		if (coex_stat->bt_iqk_state == 1)
			coex_stat->cnt_bt[COEX_CNT_BT_IQK]++;
		else if (coex_stat->bt_iqk_state == 2)
			coex_stat->cnt_bt[COEX_CNT_BT_IQKFAIL]++;

		return;
	}

	if (rsp_source == COEX_BTINFO_SRC_BT_SCBD) {
		rtw_coex_monitor_bt_enable(rtwdev);
		if (coex_stat->bt_disabled != coex_stat->bt_disabled_pre) {
			coex_stat->bt_disabled_pre = coex_stat->bt_disabled;
			rtw_coex_run_coex(rtwdev, COEX_RSN_BTINFO);
		}
		return;
	}

	if (rsp_source == COEX_BTINFO_SRC_BT_RSP ||
	    rsp_source == COEX_BTINFO_SRC_BT_ACT) {
		if (coex_stat->bt_disabled) {
			coex_stat->bt_disabled = false;
			coex_stat->bt_reenable = true;
			ieee80211_queue_delayed_work(rtwdev->hw,
						     &coex->bt_reenable_work,
						     15 * HZ);
		}
	}

	for (i = 0; i < length; i++) {
		if (i < COEX_BTINFO_LENGTH_MAX)
			coex_stat->bt_info_c2h[rsp_source][i] = buf[i];
		else
			break;
	}

	if (rsp_source == COEX_BTINFO_SRC_WL_FW) {
		rtw_coex_update_bt_link_info(rtwdev);
		rtw_coex_run_coex(rtwdev, COEX_RSN_BTINFO);
		return;
	}

	/* get the same info from bt, skip it */
	if (coex_stat->bt_info_c2h[rsp_source][1] == coex_stat->bt_info_lb2 &&
	    coex_stat->bt_info_c2h[rsp_source][2] == coex_stat->bt_info_lb3 &&
	    coex_stat->bt_info_c2h[rsp_source][3] == coex_stat->bt_info_hb0 &&
	    coex_stat->bt_info_c2h[rsp_source][4] == coex_stat->bt_info_hb1 &&
	    coex_stat->bt_info_c2h[rsp_source][5] == coex_stat->bt_info_hb2 &&
	    coex_stat->bt_info_c2h[rsp_source][6] == coex_stat->bt_info_hb3)
		return;

	coex_stat->bt_info_lb2 = coex_stat->bt_info_c2h[rsp_source][1];
	coex_stat->bt_info_lb3 = coex_stat->bt_info_c2h[rsp_source][2];
	coex_stat->bt_info_hb0 = coex_stat->bt_info_c2h[rsp_source][3];
	coex_stat->bt_info_hb1 = coex_stat->bt_info_c2h[rsp_source][4];
	coex_stat->bt_info_hb2 = coex_stat->bt_info_c2h[rsp_source][5];
	coex_stat->bt_info_hb3 = coex_stat->bt_info_c2h[rsp_source][6];

	/* 0xff means BT is under WHCK test */
	coex_stat->bt_whck_test = (coex_stat->bt_info_lb2 == 0xff);
	coex_stat->bt_inq_page = ((coex_stat->bt_info_lb2 & BIT(2)) == BIT(2));
	coex_stat->bt_acl_busy = ((coex_stat->bt_info_lb2 & BIT(3)) == BIT(3));
	coex_stat->cnt_bt[COEX_CNT_BT_RETRY] = coex_stat->bt_info_lb3 & 0xf;
	if (coex_stat->cnt_bt[COEX_CNT_BT_RETRY] >= 1)
		coex_stat->cnt_bt[COEX_CNT_BT_POPEVENT]++;

	coex_stat->bt_fix_2M = ((coex_stat->bt_info_lb3 & BIT(4)) == BIT(4));
	coex_stat->bt_inq = ((coex_stat->bt_info_lb3 & BIT(5)) == BIT(5));
	if (coex_stat->bt_inq)
		coex_stat->cnt_bt[COEX_CNT_BT_INQ]++;

	coex_stat->bt_page = ((coex_stat->bt_info_lb3 & BIT(7)) == BIT(7));
	if (coex_stat->bt_page) {
		coex_stat->cnt_bt[COEX_CNT_BT_PAGE]++;
		if (coex_stat->wl_linkscan_proc ||
		    coex_stat->wl_hi_pri_task1 ||
		    coex_stat->wl_hi_pri_task2 || coex_stat->wl_gl_busy)
			rtw_coex_write_scbd(rtwdev, COEX_SCBD_SCAN, true);
		else
			rtw_coex_write_scbd(rtwdev, COEX_SCBD_SCAN, false);
	} else {
		rtw_coex_write_scbd(rtwdev, COEX_SCBD_SCAN, false);
	}

	/* unit: % (value-100 to translate to unit: dBm in coex info) */
	if (chip->bt_rssi_type == COEX_BTRSSI_RATIO) {
		coex_stat->bt_rssi = coex_stat->bt_info_hb0 * 2 + 10;
	} else { /* original unit: dbm -> unit: % ->  value-100 in coex info */
		if (coex_stat->bt_info_hb0 <= 127)
			coex_stat->bt_rssi = 100;
		else if (256 - coex_stat->bt_info_hb0 <= 100)
			coex_stat->bt_rssi = 100 - (256 - coex_stat->bt_info_hb0);
		else
			coex_stat->bt_rssi = 0;
	}

	coex_stat->bt_ble_exist = ((coex_stat->bt_info_hb1 & BIT(0)) == BIT(0));
	if (coex_stat->bt_info_hb1 & BIT(1))
		coex_stat->cnt_bt[COEX_CNT_BT_REINIT]++;

	if (coex_stat->bt_info_hb1 & BIT(2)) {
		coex_stat->cnt_bt[COEX_CNT_BT_SETUPLINK]++;
		coex_stat->bt_setup_link = true;
		if (coex_stat->bt_reenable)
			bt_relink_time = 6 * HZ;
		else
			bt_relink_time = 2 * HZ;

		ieee80211_queue_delayed_work(rtwdev->hw,
					     &coex->bt_relink_work,
					     bt_relink_time);
	}

	if (coex_stat->bt_info_hb1 & BIT(3))
		coex_stat->cnt_bt[COEX_CNT_BT_IGNWLANACT]++;

	coex_stat->bt_ble_voice = ((coex_stat->bt_info_hb1 & BIT(4)) == BIT(4));
	coex_stat->bt_ble_scan_en = ((coex_stat->bt_info_hb1 & BIT(5)) == BIT(5));
	if (coex_stat->bt_info_hb1 & BIT(6))
		coex_stat->cnt_bt[COEX_CNT_BT_ROLESWITCH]++;

	coex_stat->bt_multi_link = ((coex_stat->bt_info_hb1 & BIT(7)) == BIT(7));
	/* resend wifi info to bt, it is reset and lost the info */
	if ((coex_stat->bt_info_hb1 & BIT(1))) {
		if (coex_stat->wl_connected)
			type = COEX_MEDIA_CONNECT;
		else
			type = COEX_MEDIA_DISCONNECT;
		rtw_coex_update_wl_ch_info(rtwdev, type);
	}

	/* if ignore_wlan_act && not set_up_link */
	if ((coex_stat->bt_info_hb1 & BIT(3)) &&
	    (!(coex_stat->bt_info_hb1 & BIT(2))))
		rtw_coex_ignore_wlan_act(rtwdev, false);

	coex_stat->bt_opp_exist = ((coex_stat->bt_info_hb2 & BIT(0)) == BIT(0));
	if (coex_stat->bt_info_hb2 & BIT(1))
		coex_stat->cnt_bt[COEX_CNT_BT_AFHUPDATE]++;

	coex_stat->bt_a2dp_active = (coex_stat->bt_info_hb2 & BIT(2)) == BIT(2);
	coex_stat->bt_slave = ((coex_stat->bt_info_hb2 & BIT(3)) == BIT(3));
	coex_stat->bt_hid_slot = (coex_stat->bt_info_hb2 & 0x30) >> 4;
	coex_stat->bt_hid_pair_num = (coex_stat->bt_info_hb2 & 0xc0) >> 6;
	if (coex_stat->bt_hid_pair_num > 0 && coex_stat->bt_hid_slot >= 2)
		coex_stat->bt_418_hid_exist = true;
	else if (coex_stat->bt_hid_pair_num == 0)
		coex_stat->bt_418_hid_exist = false;

	if ((coex_stat->bt_info_lb2 & 0x49) == 0x49)
		coex_stat->bt_a2dp_bitpool = (coex_stat->bt_info_hb3 & 0x7f);
	else
		coex_stat->bt_a2dp_bitpool = 0;

	coex_stat->bt_a2dp_sink = ((coex_stat->bt_info_hb3 & BIT(7)) == BIT(7));

	rtw_coex_update_bt_link_info(rtwdev);
	rtw_coex_run_coex(rtwdev, COEX_RSN_BTINFO);
}