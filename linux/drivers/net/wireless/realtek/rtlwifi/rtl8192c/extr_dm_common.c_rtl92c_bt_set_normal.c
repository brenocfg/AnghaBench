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
struct TYPE_4__ {scalar_t__ bt_service; int bt_edca_ul; int bt_edca_dl; int ratio_tx; int bt_rssi_state; } ;
struct TYPE_3__ {int mode; } ;
struct rtl_priv {TYPE_2__ btcoexist; TYPE_1__ mac80211; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BT_BUSY ; 
 scalar_t__ BT_IDLE ; 
 scalar_t__ BT_OTHERBUSY ; 
 int BT_RSSI_STATE_BG_EDCA_LOW ; 
 scalar_t__ BT_SCO ; 
 int WIRELESS_MODE_B ; 
 int WIRELESS_MODE_G ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl92c_bt_set_normal(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if (rtlpriv->btcoexist.bt_service == BT_OTHERBUSY) {
		rtlpriv->btcoexist.bt_edca_ul = 0x5ea72b;
		rtlpriv->btcoexist.bt_edca_dl = 0x5ea72b;
	} else if (rtlpriv->btcoexist.bt_service == BT_BUSY) {
		rtlpriv->btcoexist.bt_edca_ul = 0x5eb82f;
		rtlpriv->btcoexist.bt_edca_dl = 0x5eb82f;
	} else if (rtlpriv->btcoexist.bt_service == BT_SCO) {
		if (rtlpriv->btcoexist.ratio_tx > 160) {
			rtlpriv->btcoexist.bt_edca_ul = 0x5ea72f;
			rtlpriv->btcoexist.bt_edca_dl = 0x5ea72f;
		} else {
			rtlpriv->btcoexist.bt_edca_ul = 0x5ea32b;
			rtlpriv->btcoexist.bt_edca_dl = 0x5ea42b;
		}
	} else {
		rtlpriv->btcoexist.bt_edca_ul = 0;
		rtlpriv->btcoexist.bt_edca_dl = 0;
	}

	if ((rtlpriv->btcoexist.bt_service != BT_IDLE) &&
	    (rtlpriv->mac80211.mode == WIRELESS_MODE_G ||
	     (rtlpriv->mac80211.mode == (WIRELESS_MODE_G | WIRELESS_MODE_B))) &&
	    (rtlpriv->btcoexist.bt_rssi_state &
	     BT_RSSI_STATE_BG_EDCA_LOW)) {
		rtlpriv->btcoexist.bt_edca_ul = 0x5eb82b;
		rtlpriv->btcoexist.bt_edca_dl = 0x5eb82b;
	}
}