#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_12__ {int /*<<< orphan*/  current_channel; } ;
struct TYPE_11__ {int /*<<< orphan*/  dynamic_txhighpower_lvl; int /*<<< orphan*/  dynamic_txpower_enable; } ;
struct TYPE_10__ {scalar_t__ bt_service; int bt_rssi_state; int bt_rfreg_origin_1e; scalar_t__ bt_edca_dl; scalar_t__ bt_edca_ul; } ;
struct TYPE_7__ {scalar_t__ vendor; scalar_t__ mode; } ;
struct rtl_priv {TYPE_6__ phy; TYPE_5__ dm; TYPE_4__ btcoexist; TYPE_3__* cfg; TYPE_1__ mac80211; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_9__ {TYPE_2__* ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_rfreg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int,int) ;} ;

/* Variables and functions */
 scalar_t__ BT_BUSY ; 
 scalar_t__ BT_IDLE ; 
 scalar_t__ BT_OTHER_ACTION ; 
 scalar_t__ BT_PAN ; 
 int BT_RSSI_STATE_NORMAL_POWER ; 
 int BT_RSSI_STATE_SPECIAL_LOW ; 
 int BT_RSSI_STATE_TXPOWER_LOW ; 
 scalar_t__ PEER_CISCO ; 
 int /*<<< orphan*/  REG_GPIO_MUXCFG ; 
 int /*<<< orphan*/  REG_GPIO_PIN_CTRL ; 
 int /*<<< orphan*/  RF90_PATH_A ; 
 int /*<<< orphan*/  TXHIGHPWRLEVEL_BT1 ; 
 int /*<<< orphan*/  TXHIGHPWRLEVEL_BT2 ; 
 int /*<<< orphan*/  TXHIGHPWRLEVEL_NORMAL ; 
 scalar_t__ WIRELESS_MODE_N_24G ; 
 int /*<<< orphan*/  rtl92c_bt_set_normal (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92c_phy_set_txpower_level (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void rtl92c_bt_ant_isolation(struct ieee80211_hw *hw, u8 tmp1byte)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	/* Only enable HW BT coexist when BT in "Busy" state. */
	if (rtlpriv->mac80211.vendor == PEER_CISCO &&
	    rtlpriv->btcoexist.bt_service == BT_OTHER_ACTION) {
		rtl_write_byte(rtlpriv, REG_GPIO_MUXCFG, 0xa0);
	} else {
		if ((rtlpriv->btcoexist.bt_service == BT_BUSY) &&
		    (rtlpriv->btcoexist.bt_rssi_state &
		     BT_RSSI_STATE_NORMAL_POWER)) {
			rtl_write_byte(rtlpriv, REG_GPIO_MUXCFG, 0xa0);
		} else if ((rtlpriv->btcoexist.bt_service ==
			    BT_OTHER_ACTION) && (rtlpriv->mac80211.mode <
			    WIRELESS_MODE_N_24G) &&
			    (rtlpriv->btcoexist.bt_rssi_state &
			    BT_RSSI_STATE_SPECIAL_LOW)) {
			rtl_write_byte(rtlpriv, REG_GPIO_MUXCFG, 0xa0);
		} else if (rtlpriv->btcoexist.bt_service == BT_PAN) {
			rtl_write_byte(rtlpriv, REG_GPIO_MUXCFG, tmp1byte);
		} else {
			rtl_write_byte(rtlpriv, REG_GPIO_MUXCFG, tmp1byte);
		}
	}

	if (rtlpriv->btcoexist.bt_service == BT_PAN)
		rtl_write_dword(rtlpriv, REG_GPIO_PIN_CTRL, 0x10100);
	else
		rtl_write_dword(rtlpriv, REG_GPIO_PIN_CTRL, 0x0);

	if (rtlpriv->btcoexist.bt_rssi_state &
	    BT_RSSI_STATE_NORMAL_POWER) {
		rtl92c_bt_set_normal(hw);
	} else {
		rtlpriv->btcoexist.bt_edca_ul = 0;
		rtlpriv->btcoexist.bt_edca_dl = 0;
	}

	if (rtlpriv->btcoexist.bt_service != BT_IDLE) {
		rtlpriv->cfg->ops->set_rfreg(hw,
				 RF90_PATH_A,
				 0x1e,
				 0xf0, 0xf);
	} else {
		rtlpriv->cfg->ops->set_rfreg(hw,
		     RF90_PATH_A, 0x1e, 0xf0,
		     rtlpriv->btcoexist.bt_rfreg_origin_1e);
	}

	if (!rtlpriv->dm.dynamic_txpower_enable) {
		if (rtlpriv->btcoexist.bt_service != BT_IDLE) {
			if (rtlpriv->btcoexist.bt_rssi_state &
				BT_RSSI_STATE_TXPOWER_LOW) {
				rtlpriv->dm.dynamic_txhighpower_lvl =
							TXHIGHPWRLEVEL_BT2;
			} else {
				rtlpriv->dm.dynamic_txhighpower_lvl =
					TXHIGHPWRLEVEL_BT1;
			}
		} else {
			rtlpriv->dm.dynamic_txhighpower_lvl =
				TXHIGHPWRLEVEL_NORMAL;
		}
		rtl92c_phy_set_txpower_level(hw,
			rtlpriv->phy.current_channel);
	}
}