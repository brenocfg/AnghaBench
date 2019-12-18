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
struct TYPE_3__ {void* bt_profile_action; void* bt_profile_case; int /*<<< orphan*/  cstate; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {int c2h_bt_info_original; scalar_t__ c2h_bt_info_req_sent; } ;

/* Variables and functions */
 int BTINFO_B_A2DP ; 
 int BTINFO_B_FTP ; 
 int BTINFO_B_HID ; 
 int BTINFO_B_SCO_BUSY ; 
 int BTINFO_B_SCO_ESCO ; 
 void* BT_COEX_MECH_COMMON ; 
 void* BT_COEX_MECH_FTP_A2DP ; 
 void* BT_COEX_MECH_HID_SCO_ESCO ; 
 void* BT_COEX_MECH_NONE ; 
 int /*<<< orphan*/  BT_COEX_STATE_BTINFO_B_FTP_A2DP ; 
 int /*<<< orphan*/  BT_COEX_STATE_BTINFO_B_HID_SCOESCO ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _rtl8723_dm_bt_check_wifi_state (struct ieee80211_hw*) ; 
 TYPE_2__ hal_coex_8723 ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_2_ant_ftp_a2dp (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_2_ant_hid_sco_esco (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_inq_page_monitor (struct ieee80211_hw*) ; 
 scalar_t__ rtl8723e_dm_bt_is_2_ant_common_action (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_reset_action_profile_state (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8723e_dm_bt_coexist_2_ant(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 bt_info_original;
	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		"[BTCoex] Get bt info by fw!!\n");

	_rtl8723_dm_bt_check_wifi_state(hw);

	if (hal_coex_8723.c2h_bt_info_req_sent) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"[BTCoex] c2h for bt_info not rcvd yet!!\n");
	}

	bt_info_original = hal_coex_8723.c2h_bt_info_original;

	/* when bt inquiry or page scan, we have to set h2c 0x25 */
	/* ignore wlanact for continuous 4x2secs */
	rtl8723e_dm_bt_inq_page_monitor(hw);
	rtl8723e_dm_bt_reset_action_profile_state(hw);

	if (rtl8723e_dm_bt_is_2_ant_common_action(hw)) {
		rtlpriv->btcoexist.bt_profile_case = BT_COEX_MECH_COMMON;
		rtlpriv->btcoexist.bt_profile_action = BT_COEX_MECH_COMMON;
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		"Action 2-Ant common.\n");
	} else {
		if ((bt_info_original & BTINFO_B_HID) ||
			(bt_info_original & BTINFO_B_SCO_BUSY) ||
			(bt_info_original & BTINFO_B_SCO_ESCO)) {
				rtlpriv->btcoexist.cstate |=
					BT_COEX_STATE_BTINFO_B_HID_SCOESCO;
				rtlpriv->btcoexist.bt_profile_case =
					BT_COEX_MECH_HID_SCO_ESCO;
				rtlpriv->btcoexist.bt_profile_action =
					BT_COEX_MECH_HID_SCO_ESCO;
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					 "[BTCoex], BTInfo: bHid|bSCOBusy|bSCOeSCO\n");
				rtl8723e_dm_bt_2_ant_hid_sco_esco(hw);
		} else if ((bt_info_original & BTINFO_B_FTP) ||
				(bt_info_original & BTINFO_B_A2DP)) {
				rtlpriv->btcoexist.cstate |=
					BT_COEX_STATE_BTINFO_B_FTP_A2DP;
				rtlpriv->btcoexist.bt_profile_case =
					BT_COEX_MECH_FTP_A2DP;
				rtlpriv->btcoexist.bt_profile_action =
					BT_COEX_MECH_FTP_A2DP;
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					 "BTInfo: bFTP|bA2DP\n");
				rtl8723e_dm_bt_2_ant_ftp_a2dp(hw);
		} else {
				rtlpriv->btcoexist.cstate |=
					BT_COEX_STATE_BTINFO_B_HID_SCOESCO;
				rtlpriv->btcoexist.bt_profile_case =
					BT_COEX_MECH_NONE;
				rtlpriv->btcoexist.bt_profile_action =
					BT_COEX_MECH_NONE;
				RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					 "[BTCoex], BTInfo: undefined case!!!!\n");
				rtl8723e_dm_bt_2_ant_hid_sco_esco(hw);
		}
	}
}