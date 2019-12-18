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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ;struct rtl_priv* adapter; } ;
struct TYPE_2__ {int auto_tdma_adjust; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_U4_WIFI_BW ; 
 scalar_t__ BTC_RSSI_STATE_HIGH ; 
 scalar_t__ BTC_RSSI_STATE_LOW ; 
 scalar_t__ BTC_RSSI_STATE_MEDIUM ; 
 scalar_t__ BTC_RSSI_STATE_STAY_HIGH ; 
 scalar_t__ BTC_RSSI_STATE_STAY_LOW ; 
 scalar_t__ BTC_RSSI_STATE_STAY_MEDIUM ; 
 scalar_t__ BTC_WIFI_BW_HT40 ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ btc8192e2ant_bt_rssi_state (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  btc8192e2ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8192e2ant_dec_bt_pwr (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8192e2ant_fw_dac_swing_lvl (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8192e2ant_limited_rx (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  btc8192e2ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  btc8192e2ant_sw_mechanism1 (struct btc_coexist*,int,int,int,int) ; 
 int /*<<< orphan*/  btc8192e2ant_sw_mechanism2 (struct btc_coexist*,int,int,int,int) ; 
 int /*<<< orphan*/  btc8192e2ant_switch_ss_type (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8192e2ant_tdma_duration_adjust (struct btc_coexist*,int,int,int) ; 
 scalar_t__ btc8192e2ant_wifi_rssi_state (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* coex_dm ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void btc8192e2ant_action_a2dp(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u8 wifi_rssi_state, bt_rssi_state = BTC_RSSI_STATE_HIGH;
	u32 wifi_bw;
	bool long_dist = false;

	wifi_rssi_state = btc8192e2ant_wifi_rssi_state(btcoexist, 0, 2, 15, 0);
	bt_rssi_state = btc8192e2ant_bt_rssi_state(btcoexist, 3, 34, 42);

	if ((bt_rssi_state == BTC_RSSI_STATE_LOW ||
	     bt_rssi_state == BTC_RSSI_STATE_STAY_LOW) &&
	    (wifi_rssi_state == BTC_RSSI_STATE_LOW ||
	     wifi_rssi_state == BTC_RSSI_STATE_STAY_LOW)) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], A2dp, wifi/bt rssi both LOW!!\n");
		long_dist = true;
	}
	if (long_dist) {
		btc8192e2ant_switch_ss_type(btcoexist, NORMAL_EXEC, 2);
		btc8192e2ant_limited_rx(btcoexist, NORMAL_EXEC, false, true,
					0x4);
	} else {
		btc8192e2ant_switch_ss_type(btcoexist, NORMAL_EXEC, 1);
		btc8192e2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false,
					0x8);
	}

	btc8192e2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	if (long_dist)
		btc8192e2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
	else
		btc8192e2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);

	if (long_dist) {
		btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 17);
		coex_dm->auto_tdma_adjust = false;
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
	} else {
		if ((bt_rssi_state == BTC_RSSI_STATE_LOW) ||
		    (bt_rssi_state == BTC_RSSI_STATE_STAY_LOW)) {
			btc8192e2ant_tdma_duration_adjust(btcoexist, false,
							  true, 1);
			btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
		} else if ((bt_rssi_state == BTC_RSSI_STATE_MEDIUM) ||
			   (bt_rssi_state == BTC_RSSI_STATE_STAY_MEDIUM)) {
			btc8192e2ant_tdma_duration_adjust(btcoexist, false,
							  false, 1);
			btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
		} else if ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
			   (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) {
			btc8192e2ant_tdma_duration_adjust(btcoexist, false,
							  false, 1);
			btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 4);
		}
	}

	/* sw mechanism */
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wifi_bw);
	if (BTC_WIFI_BW_HT40 == wifi_bw) {
		if ((wifi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wifi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) {
			btc8192e2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		} else {
			btc8192e2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		}
	} else {
		if ((wifi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wifi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) {
			btc8192e2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		} else {
			btc8192e2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		}
	}
}