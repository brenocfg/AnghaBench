#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_6__ {int bt_rssi_state; } ;
struct TYPE_5__ {long entry_min_undec_sm_pwdb; } ;
struct TYPE_4__ {scalar_t__ link_state; } ;
struct rtl_priv {TYPE_3__ btcoexist; TYPE_2__ dm; TYPE_1__ mac80211; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BT_RSSI_STATE_AMDPU_OFF ; 
 int BT_RSSI_STATE_BG_EDCA_LOW ; 
 int BT_RSSI_STATE_NORMAL_POWER ; 
 int BT_RSSI_STATE_SPECIAL_LOW ; 
 long GET_UNDECORATED_AVERAGE_RSSI (struct rtl_priv*) ; 
 scalar_t__ MAC80211_LINKED ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

u8 rtl92c_bt_rssi_state_change(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	long undec_sm_pwdb;
	u8 curr_bt_rssi_state = 0x00;

	if (rtlpriv->mac80211.link_state == MAC80211_LINKED) {
		undec_sm_pwdb = GET_UNDECORATED_AVERAGE_RSSI(rtlpriv);
	} else {
		if (rtlpriv->dm.entry_min_undec_sm_pwdb == 0)
			undec_sm_pwdb = 100;
		else
			undec_sm_pwdb = rtlpriv->dm.entry_min_undec_sm_pwdb;
	}

	/* Check RSSI to determine HighPower/NormalPower state for
	 * BT coexistence. */
	if (undec_sm_pwdb >= 67)
		curr_bt_rssi_state &= (~BT_RSSI_STATE_NORMAL_POWER);
	else if (undec_sm_pwdb < 62)
		curr_bt_rssi_state |= BT_RSSI_STATE_NORMAL_POWER;

	/* Check RSSI to determine AMPDU setting for BT coexistence. */
	if (undec_sm_pwdb >= 40)
		curr_bt_rssi_state &= (~BT_RSSI_STATE_AMDPU_OFF);
	else if (undec_sm_pwdb <= 32)
		curr_bt_rssi_state |= BT_RSSI_STATE_AMDPU_OFF;

	/* Marked RSSI state. It will be used to determine BT coexistence
	 * setting later. */
	if (undec_sm_pwdb < 35)
		curr_bt_rssi_state |=  BT_RSSI_STATE_SPECIAL_LOW;
	else
		curr_bt_rssi_state &= (~BT_RSSI_STATE_SPECIAL_LOW);

	/* Check BT state related to BT_Idle in B/G mode. */
	if (undec_sm_pwdb < 15)
		curr_bt_rssi_state |=  BT_RSSI_STATE_BG_EDCA_LOW;
	else
		curr_bt_rssi_state &= (~BT_RSSI_STATE_BG_EDCA_LOW);

	if (curr_bt_rssi_state != rtlpriv->btcoexist.bt_rssi_state) {
		rtlpriv->btcoexist.bt_rssi_state = curr_bt_rssi_state;
		return true;
	} else {
		return false;
	}
}