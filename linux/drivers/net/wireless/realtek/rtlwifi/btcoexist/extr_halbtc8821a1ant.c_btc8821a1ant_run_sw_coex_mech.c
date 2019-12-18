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
typedef  int u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {struct rtl_priv* adapter; } ;
struct TYPE_2__ {int cur_algorithm; int pre_algorithm; } ;

/* Variables and functions */
#define  BT_8821A_1ANT_COEX_ALGO_A2DP 137 
#define  BT_8821A_1ANT_COEX_ALGO_A2DP_PANHS 136 
#define  BT_8821A_1ANT_COEX_ALGO_HID 135 
#define  BT_8821A_1ANT_COEX_ALGO_HID_A2DP 134 
#define  BT_8821A_1ANT_COEX_ALGO_HID_A2DP_PANEDR 133 
#define  BT_8821A_1ANT_COEX_ALGO_PANEDR 132 
#define  BT_8821A_1ANT_COEX_ALGO_PANEDR_A2DP 131 
#define  BT_8821A_1ANT_COEX_ALGO_PANEDR_HID 130 
#define  BT_8821A_1ANT_COEX_ALGO_PANHS 129 
#define  BT_8821A_1ANT_COEX_ALGO_SCO 128 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  btc8821a1ant_action_a2dp (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a1ant_action_a2dp_pan_hs (struct btc_coexist*) ; 
 int btc8821a1ant_action_algorithm (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a1ant_action_hid (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a1ant_action_hid_a2dp (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a1ant_action_hid_a2dp_pan_edr (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a1ant_action_pan_edr (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a1ant_action_pan_edr_a2dp (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a1ant_action_pan_edr_hid (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a1ant_action_pan_hs (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a1ant_action_sco (struct btc_coexist*) ; 
 int /*<<< orphan*/  btc8821a1ant_is_common_action (struct btc_coexist*) ; 
 TYPE_1__* coex_dm ; 

__attribute__((used)) static void btc8821a1ant_run_sw_coex_mech(struct btc_coexist *btcoexist)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u8 algorithm = 0;

	algorithm = btc8821a1ant_action_algorithm(btcoexist);
	coex_dm->cur_algorithm = algorithm;

	if (!btc8821a1ant_is_common_action(btcoexist)) {
		switch (coex_dm->cur_algorithm) {
		case BT_8821A_1ANT_COEX_ALGO_SCO:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action algorithm = SCO\n");
			btc8821a1ant_action_sco(btcoexist);
			break;
		case BT_8821A_1ANT_COEX_ALGO_HID:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action algorithm = HID\n");
			btc8821a1ant_action_hid(btcoexist);
			break;
		case BT_8821A_1ANT_COEX_ALGO_A2DP:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action algorithm = A2DP\n");
			btc8821a1ant_action_a2dp(btcoexist);
			break;
		case BT_8821A_1ANT_COEX_ALGO_A2DP_PANHS:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action algorithm = A2DP+PAN(HS)\n");
			btc8821a1ant_action_a2dp_pan_hs(btcoexist);
			break;
		case BT_8821A_1ANT_COEX_ALGO_PANEDR:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action algorithm = PAN(EDR)\n");
			btc8821a1ant_action_pan_edr(btcoexist);
			break;
		case BT_8821A_1ANT_COEX_ALGO_PANHS:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action algorithm = HS mode\n");
			btc8821a1ant_action_pan_hs(btcoexist);
			break;
		case BT_8821A_1ANT_COEX_ALGO_PANEDR_A2DP:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action algorithm = PAN+A2DP\n");
			btc8821a1ant_action_pan_edr_a2dp(btcoexist);
			break;
		case BT_8821A_1ANT_COEX_ALGO_PANEDR_HID:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action algorithm = PAN(EDR)+HID\n");
			btc8821a1ant_action_pan_edr_hid(btcoexist);
			break;
		case BT_8821A_1ANT_COEX_ALGO_HID_A2DP_PANEDR:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action algorithm = HID+A2DP+PAN\n");
			btc8821a1ant_action_hid_a2dp_pan_edr(btcoexist);
			break;
		case BT_8821A_1ANT_COEX_ALGO_HID_A2DP:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action algorithm = HID+A2DP\n");
			btc8821a1ant_action_hid_a2dp(btcoexist);
			break;
		default:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], Action algorithm = coexist All Off!!\n");
			/*btc8821a1ant_coex_all_off(btcoexist);*/
			break;
		}
		coex_dm->pre_algorithm = coex_dm->cur_algorithm;
	}
}