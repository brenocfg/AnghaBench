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
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;struct rtl_priv* adapter; } ;
struct TYPE_2__ {scalar_t__ bt_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 scalar_t__ BT_8821A_1ANT_BT_STATUS_CONNECTED_IDLE ; 
 scalar_t__ BT_8821A_1ANT_BT_STATUS_NON_CONNECTED_IDLE ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  btc8821a1ant_sw_mechanism (struct btc_coexist*,int) ; 
 TYPE_1__* coex_dm ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool btc8821a1ant_is_common_action(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool common = false, wifi_connected = false, wifi_busy = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wifi_connected);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wifi_busy);

	if (!wifi_connected &&
	    BT_8821A_1ANT_BT_STATUS_NON_CONNECTED_IDLE ==
	    coex_dm->bt_status) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Wifi non connected-idle + BT non connected-idle!!\n");
		btc8821a1ant_sw_mechanism(btcoexist, false);

		common = true;
	} else if (wifi_connected &&
		   (BT_8821A_1ANT_BT_STATUS_NON_CONNECTED_IDLE ==
		    coex_dm->bt_status)) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Wifi connected + BT non connected-idle!!\n");
		btc8821a1ant_sw_mechanism(btcoexist, false);

		common = true;
	} else if (!wifi_connected &&
		   (BT_8821A_1ANT_BT_STATUS_CONNECTED_IDLE ==
		    coex_dm->bt_status)) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Wifi non connected-idle + BT connected-idle!!\n");
		btc8821a1ant_sw_mechanism(btcoexist, false);

		common = true;
	} else if (wifi_connected &&
		   (BT_8821A_1ANT_BT_STATUS_CONNECTED_IDLE ==
		    coex_dm->bt_status)) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Wifi connected + BT connected-idle!!\n");
		btc8821a1ant_sw_mechanism(btcoexist, false);

		common = true;
	} else if (!wifi_connected &&
		   (BT_8821A_1ANT_BT_STATUS_CONNECTED_IDLE !=
		    coex_dm->bt_status)) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Wifi non connected-idle + BT Busy!!\n");
		btc8821a1ant_sw_mechanism(btcoexist, false);

		common = true;
	} else {
		if (wifi_busy) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Wifi Connected-Busy + BT Busy!!\n");
		} else {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Wifi Connected-Idle + BT Busy!!\n");
		}

		common = false;
	}

	return common;
}