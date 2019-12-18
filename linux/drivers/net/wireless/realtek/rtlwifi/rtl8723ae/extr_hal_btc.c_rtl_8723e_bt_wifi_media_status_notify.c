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
struct TYPE_2__ {int /*<<< orphan*/  bt_coexistence; } ;
struct rtl_phy {int current_channel; scalar_t__ current_chan_bw; } ;
struct rtl_priv {TYPE_1__ btcoexist; struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 scalar_t__ HT_CHANNEL_WIDTH_20_40 ; 
 int RT_MEDIA_CONNECT ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ mgnt_link_status_query (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723e_fill_h2c_cmd (struct ieee80211_hw*,int,int,int*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl_8723e_bt_wifi_media_status_notify(struct ieee80211_hw *hw,
						bool mstatus)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	u8 h2c_parameter[3] = {0};
	u8 chnl;

	if (!rtlpriv->btcoexist.bt_coexistence)
		return;

	if (RT_MEDIA_CONNECT == mstatus)
		h2c_parameter[0] = 0x1; /* 0: disconnected, 1:connected */
	else
		h2c_parameter[0] = 0x0;

	if (mgnt_link_status_query(hw))	{
		chnl = rtlphy->current_channel;
		h2c_parameter[1] = chnl;
	}

	if (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40)
		h2c_parameter[2] = 0x30;
	else
		h2c_parameter[2] = 0x20;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		 "[BTCoex], FW write 0x19=0x%x\n",
		 h2c_parameter[0]<<16|h2c_parameter[1]<<8|h2c_parameter[2]);

	rtl8723e_fill_h2c_cmd(hw, 0x19, 3, h2c_parameter);
}