#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_set ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  auto_report_2ant; int /*<<< orphan*/  stop_coex_dm; int /*<<< orphan*/  manual_control; int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct rtl_priv* adapter; } ;
struct TYPE_4__ {scalar_t__ bt_status; int limited_dig; } ;
struct TYPE_3__ {int c2h_bt_info_req_sent; int** bt_info_c2h; int bt_retry_cnt; int bt_rssi; int bt_info_ext; int c2h_bt_inquiry_page; int bt_link_exist; int pan_exist; int a2dp_exist; int hid_exist; int sco_exist; int /*<<< orphan*/ * bt_info_c2h_cnt; } ;

/* Variables and functions */
 int BIT1 ; 
 int BIT3 ; 
 int BIT4 ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  BTC_MEDIA_CONNECT ; 
 int /*<<< orphan*/  BTC_MEDIA_DISCONNECT ; 
 int /*<<< orphan*/  BTC_SET_BL_BT_LIMITED_DIG ; 
 int /*<<< orphan*/  BTC_SET_BL_BT_TRAFFIC_BUSY ; 
 scalar_t__ BT_8192E_2ANT_BT_STATUS_ACL_BUSY ; 
 scalar_t__ BT_8192E_2ANT_BT_STATUS_ACL_SCO_BUSY ; 
 scalar_t__ BT_8192E_2ANT_BT_STATUS_CONNECTED_IDLE ; 
 scalar_t__ BT_8192E_2ANT_BT_STATUS_MAX ; 
 scalar_t__ BT_8192E_2ANT_BT_STATUS_NON_CONNECTED_IDLE ; 
 scalar_t__ BT_8192E_2ANT_BT_STATUS_SCO_BUSY ; 
 int BT_INFO_8192E_2ANT_B_A2DP ; 
 int BT_INFO_8192E_2ANT_B_ACL_BUSY ; 
 int BT_INFO_8192E_2ANT_B_CONNECTION ; 
 int BT_INFO_8192E_2ANT_B_FTP ; 
 int BT_INFO_8192E_2ANT_B_HID ; 
 int BT_INFO_8192E_2ANT_B_INQ_PAGE ; 
 int BT_INFO_8192E_2ANT_B_SCO_BUSY ; 
 int BT_INFO_8192E_2ANT_B_SCO_ESCO ; 
 int BT_INFO_SRC_8192E_2ANT_MAX ; 
 int BT_INFO_SRC_8192E_2ANT_WIFI_FW ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  btc8192e2ant_bt_auto_report (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8192e2ant_ignore_wlan_act (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8192e2ant_run_coexist_mechanism (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8192e2ant_update_bt_link_info (struct btc_coexist*) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  ex_btc8192e2ant_media_status_notify (struct btc_coexist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

void ex_btc8192e2ant_bt_info_notify(struct btc_coexist *btcoexist,
				    u8 *tmp_buf, u8 length)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u8 bt_info = 0;
	u8 i, rsp_source = 0;
	bool bt_busy = false, limited_dig = false;
	bool wifi_connected = false;

	coex_sta->c2h_bt_info_req_sent = false;

	rsp_source = tmp_buf[0] & 0xf;
	if (rsp_source >= BT_INFO_SRC_8192E_2ANT_MAX)
		rsp_source = BT_INFO_SRC_8192E_2ANT_WIFI_FW;
	coex_sta->bt_info_c2h_cnt[rsp_source]++;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], Bt info[%d], length=%d, hex data = [",
		 rsp_source, length);
	for (i = 0; i < length; i++) {
		coex_sta->bt_info_c2h[rsp_source][i] = tmp_buf[i];
		if (i == 1)
			bt_info = tmp_buf[i];
		if (i == length-1)
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "0x%02x]\n", tmp_buf[i]);
		else
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "0x%02x, ", tmp_buf[i]);
	}

	if (BT_INFO_SRC_8192E_2ANT_WIFI_FW != rsp_source) {
		/* [3:0] */
		coex_sta->bt_retry_cnt =
			coex_sta->bt_info_c2h[rsp_source][2] & 0xf;

		coex_sta->bt_rssi =
			coex_sta->bt_info_c2h[rsp_source][3] * 2 + 10;

		coex_sta->bt_info_ext =
			coex_sta->bt_info_c2h[rsp_source][4];

		/* Here we need to resend some wifi info to BT
		 * because bt is reset and loss of the info.
		 */
		if ((coex_sta->bt_info_ext & BIT1)) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "bit1, send wifi BW&Chnl to BT!!\n");
			btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
					   &wifi_connected);
			if (wifi_connected)
				ex_btc8192e2ant_media_status_notify(
							btcoexist,
							BTC_MEDIA_CONNECT);
			else
				ex_btc8192e2ant_media_status_notify(
							btcoexist,
							BTC_MEDIA_DISCONNECT);
		}

		if ((coex_sta->bt_info_ext & BIT3)) {
			if (!btcoexist->manual_control &&
			    !btcoexist->stop_coex_dm) {
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					 "bit3, BT NOT ignore Wlan active!\n");
				btc8192e2ant_ignore_wlan_act(btcoexist,
							     FORCE_EXEC,
							     false);
			}
		} else {
			/* BT already NOT ignore Wlan active,
			 * do nothing here.
			 */
		}

		if (!btcoexist->auto_report_2ant) {
			if (!(coex_sta->bt_info_ext & BIT4))
				btc8192e2ant_bt_auto_report(btcoexist,
							    FORCE_EXEC,
							    true);
		}
	}

	/* check BIT2 first ==> check if bt is under inquiry or page scan */
	if (bt_info & BT_INFO_8192E_2ANT_B_INQ_PAGE)
		coex_sta->c2h_bt_inquiry_page = true;
	else
		coex_sta->c2h_bt_inquiry_page = false;

	/* set link exist status */
	if (!(bt_info&BT_INFO_8192E_2ANT_B_CONNECTION)) {
		coex_sta->bt_link_exist = false;
		coex_sta->pan_exist = false;
		coex_sta->a2dp_exist = false;
		coex_sta->hid_exist = false;
		coex_sta->sco_exist = false;
	} else {/* connection exists */
		coex_sta->bt_link_exist = true;
		if (bt_info & BT_INFO_8192E_2ANT_B_FTP)
			coex_sta->pan_exist = true;
		else
			coex_sta->pan_exist = false;
		if (bt_info & BT_INFO_8192E_2ANT_B_A2DP)
			coex_sta->a2dp_exist = true;
		else
			coex_sta->a2dp_exist = false;
		if (bt_info & BT_INFO_8192E_2ANT_B_HID)
			coex_sta->hid_exist = true;
		else
			coex_sta->hid_exist = false;
		if (bt_info & BT_INFO_8192E_2ANT_B_SCO_ESCO)
			coex_sta->sco_exist = true;
		else
			coex_sta->sco_exist = false;
	}

	btc8192e2ant_update_bt_link_info(btcoexist);

	if (!(bt_info & BT_INFO_8192E_2ANT_B_CONNECTION)) {
		coex_dm->bt_status = BT_8192E_2ANT_BT_STATUS_NON_CONNECTED_IDLE;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BT Non-Connected idle!!!\n");
	} else if (bt_info == BT_INFO_8192E_2ANT_B_CONNECTION) {
		coex_dm->bt_status = BT_8192E_2ANT_BT_STATUS_CONNECTED_IDLE;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], bt_infoNotify(), BT Connected-idle!!!\n");
	} else if ((bt_info & BT_INFO_8192E_2ANT_B_SCO_ESCO) ||
		   (bt_info & BT_INFO_8192E_2ANT_B_SCO_BUSY)) {
		coex_dm->bt_status = BT_8192E_2ANT_BT_STATUS_SCO_BUSY;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], bt_infoNotify(), BT SCO busy!!!\n");
	} else if (bt_info & BT_INFO_8192E_2ANT_B_ACL_BUSY) {
		coex_dm->bt_status = BT_8192E_2ANT_BT_STATUS_ACL_BUSY;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], bt_infoNotify(), BT ACL busy!!!\n");
	} else {
		coex_dm->bt_status = BT_8192E_2ANT_BT_STATUS_MAX;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex]bt_infoNotify(), BT Non-Defined state!!!\n");
	}

	if ((BT_8192E_2ANT_BT_STATUS_ACL_BUSY == coex_dm->bt_status) ||
	    (BT_8192E_2ANT_BT_STATUS_SCO_BUSY == coex_dm->bt_status) ||
	    (BT_8192E_2ANT_BT_STATUS_ACL_SCO_BUSY == coex_dm->bt_status)) {
		bt_busy = true;
		limited_dig = true;
	} else {
		bt_busy = false;
		limited_dig = false;
	}

	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_TRAFFIC_BUSY, &bt_busy);

	coex_dm->limited_dig = limited_dig;
	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_LIMITED_DIG, &limited_dig);

	btc8192e2ant_run_coexist_mechanism(btcoexist);
}