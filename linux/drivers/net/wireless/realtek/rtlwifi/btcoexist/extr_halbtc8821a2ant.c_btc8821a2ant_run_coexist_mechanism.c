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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct rtl_priv {int dummy; } ;
struct btc_bt_link_info {scalar_t__ bt_link_exist; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_set ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;scalar_t__ manual_control; struct btc_bt_link_info bt_link_info; struct rtl_priv* adapter; } ;
struct TYPE_4__ {int cur_algorithm; int auto_tdma_adjust; int pre_algorithm; } ;
struct TYPE_3__ {scalar_t__ c2h_bt_inquiry_page; scalar_t__ under_ips; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_WIFI_LINK ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_ROAM ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_SCAN ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_5G ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_LINK_STATUS ; 
 int /*<<< orphan*/  BTC_SET_BL_MIRACAST_PLUS_BT ; 
#define  BT_8821A_2ANT_COEX_ALGO_A2DP 137 
#define  BT_8821A_2ANT_COEX_ALGO_A2DP_PANHS 136 
#define  BT_8821A_2ANT_COEX_ALGO_HID 135 
#define  BT_8821A_2ANT_COEX_ALGO_HID_A2DP 134 
#define  BT_8821A_2ANT_COEX_ALGO_HID_A2DP_PANEDR 133 
#define  BT_8821A_2ANT_COEX_ALGO_PANEDR 132 
#define  BT_8821A_2ANT_COEX_ALGO_PANEDR_A2DP 131 
#define  BT_8821A_2ANT_COEX_ALGO_PANEDR_HID 130 
#define  BT_8821A_2ANT_COEX_ALGO_PANHS 129 
#define  BT_8821A_2ANT_COEX_ALGO_SCO 128 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int WIFI_P2P_GO_CONNECTED ; 
 int /*<<< orphan*/  btc8821a2ant_act_hid_a2dp_pan_edr (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a2ant_action_a2dp (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a2ant_action_a2dp_pan_hs (struct btc_coexist*) ; 
 scalar_t__ btc8821a2ant_action_algorithm (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a2ant_action_bt_inquiry (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a2ant_action_hid (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a2ant_action_hid_a2dp (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a2ant_action_pan_edr (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a2ant_action_pan_edr_a2dp (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a2ant_action_pan_edr_hid (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a2ant_action_pan_hs (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a2ant_action_sco (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a2ant_action_wifi_link_process (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a2ant_action_wifi_multi_port (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a2ant_coex_all_off (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a2ant_coex_under_5g (struct btc_coexist*) ; 
 scalar_t__ btc8821a2ant_is_common_action (struct btc_coexist*) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void btc8821a2ant_run_coexist_mechanism(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool wifi_under_5g = false;
	u8 algorithm = 0;
	u32 num_of_wifi_link = 0;
	u32 wifi_link_status = 0;
	bool miracast_plus_bt = false;
	bool scan = false, link = false, roam = false;

	if (btcoexist->manual_control) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Manual control!!!\n");
		return;
	}

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wifi_under_5g);

	if (wifi_under_5g) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], RunCoexistMechanism(), run 5G coex setting!!<===\n");
		btc8821a2ant_coex_under_5g(btcoexist);
		return;
	}

	if (coex_sta->under_ips) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], wifi is under IPS !!!\n");
		return;
	}

	algorithm = btc8821a2ant_action_algorithm(btcoexist);
	if (coex_sta->c2h_bt_inquiry_page &&
	    (BT_8821A_2ANT_COEX_ALGO_PANHS != algorithm)) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], BT is under inquiry/page scan !!\n");
		btc8821a2ant_action_bt_inquiry(btcoexist);
		return;
	}

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);

	if (scan || link || roam) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], WiFi is under Link Process !!\n");
		btc8821a2ant_action_wifi_link_process(btcoexist);
		return;
	}

	/* for P2P */
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_LINK_STATUS,
			   &wifi_link_status);
	num_of_wifi_link = wifi_link_status >> 16;

	if ((num_of_wifi_link >= 2) ||
	    (wifi_link_status & WIFI_P2P_GO_CONNECTED)) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "############# [BTCoex],  Multi-Port num_of_wifi_link = %d, wifi_link_status = 0x%x\n",
			 num_of_wifi_link, wifi_link_status);

		if (bt_link_info->bt_link_exist)
			miracast_plus_bt = true;
		else
			miracast_plus_bt = false;

		btcoexist->btc_set(btcoexist, BTC_SET_BL_MIRACAST_PLUS_BT,
				   &miracast_plus_bt);
		btc8821a2ant_action_wifi_multi_port(btcoexist);

		return;
	}

	miracast_plus_bt = false;
	btcoexist->btc_set(btcoexist, BTC_SET_BL_MIRACAST_PLUS_BT,
			   &miracast_plus_bt);

	coex_dm->cur_algorithm = algorithm;
	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], Algorithm = %d\n", coex_dm->cur_algorithm);

	if (btc8821a2ant_is_common_action(btcoexist)) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], Action 2-Ant common\n");
		coex_dm->auto_tdma_adjust = true;
	} else {
		if (coex_dm->cur_algorithm != coex_dm->pre_algorithm) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], pre_algorithm = %d, cur_algorithm = %d\n",
				    coex_dm->pre_algorithm,
				    coex_dm->cur_algorithm);
			coex_dm->auto_tdma_adjust = false;
		}
		switch (coex_dm->cur_algorithm) {
		case BT_8821A_2ANT_COEX_ALGO_SCO:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action 2-Ant, algorithm = SCO\n");
			btc8821a2ant_action_sco(btcoexist);
			break;
		case BT_8821A_2ANT_COEX_ALGO_HID:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action 2-Ant, algorithm = HID\n");
			btc8821a2ant_action_hid(btcoexist);
			break;
		case BT_8821A_2ANT_COEX_ALGO_A2DP:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action 2-Ant, algorithm = A2DP\n");
			btc8821a2ant_action_a2dp(btcoexist);
			break;
		case BT_8821A_2ANT_COEX_ALGO_A2DP_PANHS:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action 2-Ant, algorithm = A2DP+PAN(HS)\n");
			btc8821a2ant_action_a2dp_pan_hs(btcoexist);
			break;
		case BT_8821A_2ANT_COEX_ALGO_PANEDR:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action 2-Ant, algorithm = PAN(EDR)\n");
			btc8821a2ant_action_pan_edr(btcoexist);
			break;
		case BT_8821A_2ANT_COEX_ALGO_PANHS:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action 2-Ant, algorithm = HS mode\n");
			btc8821a2ant_action_pan_hs(btcoexist);
			break;
		case BT_8821A_2ANT_COEX_ALGO_PANEDR_A2DP:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action 2-Ant, algorithm = PAN+A2DP\n");
			btc8821a2ant_action_pan_edr_a2dp(btcoexist);
			break;
		case BT_8821A_2ANT_COEX_ALGO_PANEDR_HID:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action 2-Ant, algorithm = PAN(EDR)+HID\n");
			btc8821a2ant_action_pan_edr_hid(btcoexist);
			break;
		case BT_8821A_2ANT_COEX_ALGO_HID_A2DP_PANEDR:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action 2-Ant, algorithm = HID+A2DP+PAN\n");
			btc8821a2ant_act_hid_a2dp_pan_edr(btcoexist);
			break;
		case BT_8821A_2ANT_COEX_ALGO_HID_A2DP:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action 2-Ant, algorithm = HID+A2DP\n");
			btc8821a2ant_action_hid_a2dp(btcoexist);
			break;
		default:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action 2-Ant, algorithm = coexist All Off!!\n");
			btc8821a2ant_coex_all_off(btcoexist);
			break;
		}
		coex_dm->pre_algorithm = coex_dm->cur_algorithm;
	}
}