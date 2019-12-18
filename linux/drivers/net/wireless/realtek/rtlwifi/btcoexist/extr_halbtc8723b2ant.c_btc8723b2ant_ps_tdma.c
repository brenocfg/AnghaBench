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
struct btc_bt_link_info {scalar_t__ a2dp_exist; scalar_t__ slave_role; } ;
struct btc_coexist {struct btc_bt_link_info bt_link_info; struct rtl_priv* adapter; } ;
typedef  int s8 ;
struct TYPE_4__ {int switch_thres_offset; int cur_ps_tdma_on; int cur_ps_tdma; int is_switch_to_1dot5_ant; int pre_ps_tdma_on; int pre_ps_tdma; } ;
struct TYPE_3__ {int scan_ap_num; int a2dp_bit_pool; } ;

/* Variables and functions */
 scalar_t__ BTC_RSSI_HIGH (int) ; 
 int BT_8723B_2ANT_BT_RSSI_COEXSWITCH_THRES ; 
 int BT_8723B_2ANT_WIFI_RSSI_COEXSWITCH_THRES ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int btc8723b2ant_bt_rssi_state (struct btc_coexist*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8723b2ant_set_fw_ps_tdma (struct btc_coexist*,int,int,int,int,int) ; 
 int btc8723b2ant_wifi_rssi_state (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 

__attribute__((used)) static void btc8723b2ant_ps_tdma(struct btc_coexist *btcoexist, bool force_exec,
				 bool turn_on, u8 type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	u8 wifi_rssi_state, bt_rssi_state;
	s8 wifi_duration_adjust = 0x0;
	u8 tdma_byte4_modify = 0x0;
	u8 tmp = BT_8723B_2ANT_WIFI_RSSI_COEXSWITCH_THRES -
			coex_dm->switch_thres_offset;

	wifi_rssi_state = btc8723b2ant_wifi_rssi_state(btcoexist, 0, 2, tmp, 0);
	tmp = BT_8723B_2ANT_BT_RSSI_COEXSWITCH_THRES -
			coex_dm->switch_thres_offset;
	bt_rssi_state = btc8723b2ant_bt_rssi_state(btcoexist, 2, tmp, 0);

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], %s turn %s PS TDMA, type=%d\n",
		 (force_exec ? "force to" : ""),
		 (turn_on ? "ON" : "OFF"), type);
	coex_dm->cur_ps_tdma_on = turn_on;
	coex_dm->cur_ps_tdma = type;

	if (!(BTC_RSSI_HIGH(wifi_rssi_state) &&
	      BTC_RSSI_HIGH(bt_rssi_state)) && turn_on) {
		 /* for WiFi RSSI low or BT RSSI low */
		type = type + 100;
		coex_dm->is_switch_to_1dot5_ant = true;
	} else {
		coex_dm->is_switch_to_1dot5_ant = false;
	}

	if (!force_exec) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], bPrePsTdmaOn = %d, bCurPsTdmaOn = %d!!\n",
			 coex_dm->pre_ps_tdma_on, coex_dm->cur_ps_tdma_on);
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], prePsTdma = %d, curPsTdma = %d!!\n",
			 coex_dm->pre_ps_tdma, coex_dm->cur_ps_tdma);

		if ((coex_dm->pre_ps_tdma_on == coex_dm->cur_ps_tdma_on) &&
		    (coex_dm->pre_ps_tdma == coex_dm->cur_ps_tdma))
			return;
	}

	if (coex_sta->scan_ap_num <= 5) {
		if (coex_sta->a2dp_bit_pool >= 45)
			wifi_duration_adjust = -15;
		else if (coex_sta->a2dp_bit_pool >= 35)
			wifi_duration_adjust = -10;
		else
			wifi_duration_adjust = 5;
	} else if (coex_sta->scan_ap_num <= 20) {
		if (coex_sta->a2dp_bit_pool >= 45)
			wifi_duration_adjust = -15;
		else if (coex_sta->a2dp_bit_pool >= 35)
			wifi_duration_adjust = -10;
		else
			wifi_duration_adjust = 0;
	} else if (coex_sta->scan_ap_num <= 40) {
		if (coex_sta->a2dp_bit_pool >= 45)
			wifi_duration_adjust = -15;
		else if (coex_sta->a2dp_bit_pool >= 35)
			wifi_duration_adjust = -10;
		else
			wifi_duration_adjust = -5;
	} else {
		if (coex_sta->a2dp_bit_pool >= 45)
			wifi_duration_adjust = -15;
		else if (coex_sta->a2dp_bit_pool >= 35)
			wifi_duration_adjust = -10;
		else
			wifi_duration_adjust = -10;
	}

	if ((bt_link_info->slave_role) && (bt_link_info->a2dp_exist))
		/* 0x778 = 0x1 at wifi slot (no blocking BT Low-Pri pkts) */
		tdma_byte4_modify = 0x1;

	if (turn_on) {
		switch (type) {
		case 1:
		default:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xe3, 0x3c,
				0x03, 0xf1, 0x90 | tdma_byte4_modify);
			break;
		case 2:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xe3, 0x2d,
				0x03, 0xf1, 0x90 | tdma_byte4_modify);
			break;
		case 3:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0xf1,
						    0x90 | tdma_byte4_modify);
			break;
		case 4:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x10,
						    0x03, 0xf1,
						    0x90 | tdma_byte4_modify);
			break;
		case 5:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xe3, 0x3c,
				0x3, 0x70, 0x90 | tdma_byte4_modify);
			break;
		case 6:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xe3, 0x2d,
				0x3, 0x70, 0x90 | tdma_byte4_modify);
			break;
		case 7:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0x70,
						    0x90 | tdma_byte4_modify);
			break;
		case 8:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xa3, 0x10,
						    0x3, 0x70,
						    0x90 | tdma_byte4_modify);
			break;
		case 9:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xe3, 0x3c + wifi_duration_adjust,
				0x03, 0xf1, 0x90 | tdma_byte4_modify);
			break;
		case 10:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xe3, 0x2d,
				0x03, 0xf1, 0x90 | tdma_byte4_modify);
			break;
		case 11:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0xf1,
						    0x90 | tdma_byte4_modify);
			break;
		case 12:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x10,
						    0x3, 0xf1,
						    0x90 | tdma_byte4_modify);
			break;
		case 13:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xe3, 0x3c,
				0x3, 0x70, 0x90 | tdma_byte4_modify);
			break;
		case 14:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xe3, 0x2d,
				0x3, 0x70, 0x90 | tdma_byte4_modify);
			break;
		case 15:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0x70,
						    0x90 | tdma_byte4_modify);
			break;
		case 16:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x10,
						    0x3, 0x70,
						    0x90 | tdma_byte4_modify);
			break;
		case 17:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xa3, 0x2f,
						    0x2f, 0x60, 0x90);
			break;
		case 18:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x5, 0x5,
						    0xe1, 0x90);
			break;
		case 19:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x25,
						    0x25, 0xe1, 0x90);
			break;
		case 20:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x25,
						    0x25, 0x60, 0x90);
			break;
		case 21:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x15,
						    0x03, 0x70, 0x90);
			break;

		case 23:
		case 123:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x35,
						    0x03, 0x71, 0x10);
			break;
		case 71:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xe3, 0x3c + wifi_duration_adjust,
				0x03, 0xf1, 0x90);
			break;
		case 101:
		case 105:
		case 113:
		case 171:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xd3, 0x3a + wifi_duration_adjust,
				0x03, 0x70, 0x50 | tdma_byte4_modify);
			break;
		case 102:
		case 106:
		case 110:
		case 114:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xd3, 0x2d + wifi_duration_adjust,
				0x03, 0x70, 0x50 | tdma_byte4_modify);
			break;
		case 103:
		case 107:
		case 111:
		case 115:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x1c,
						    0x03, 0x70,
						    0x50 | tdma_byte4_modify);
			break;
		case 104:
		case 108:
		case 112:
		case 116:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x10,
						    0x03, 0x70,
						    0x50 | tdma_byte4_modify);
			break;
		case 109:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x3c,
						    0x03, 0xf1,
						    0x90 | tdma_byte4_modify);
			break;
		case 121:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x15,
						    0x03, 0x70,
						    0x90 | tdma_byte4_modify);
			break;
		case 22:
		case 122:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x35,
						    0x03, 0x71, 0x11);
			break;
		}
	} else {
		/* disable PS tdma */
		switch (type) {
		case 0:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0, 0x0,
						    0x40, 0x0);
			break;
		case 1:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0, 0x0,
						    0x48, 0x0);
			break;
		default:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0, 0x0,
						    0x40, 0x0);
			break;
		}
	}

	/* update pre state */
	coex_dm->pre_ps_tdma_on = coex_dm->cur_ps_tdma_on;
	coex_dm->pre_ps_tdma = coex_dm->cur_ps_tdma;
}