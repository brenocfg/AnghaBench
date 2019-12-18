#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct rtl_phy {int current_chan_bw; int reg_837; int set_bwmode_inprogress; int /*<<< orphan*/  current_channel; int /*<<< orphan*/  rf_type; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BCCK_SYSTEM ; 
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_SCAN ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_TRACE ; 
#define  HT_CHANNEL_WIDTH_20 130 
#define  HT_CHANNEL_WIDTH_20_40 129 
#define  HT_CHANNEL_WIDTH_80 128 
 int /*<<< orphan*/  RADC_BUF_CLK ; 
 int /*<<< orphan*/  RCCAONSEC ; 
 int /*<<< orphan*/  RCCK_SYSTEM ; 
 int /*<<< orphan*/  RF_2T2R ; 
 int /*<<< orphan*/  RL1PEAKTH ; 
 int /*<<< orphan*/  RRFMOD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int VHT_DATA_SC_20_UPPER_OF_80MHZ ; 
 int _rtl8821ae_phy_get_secondary_chnl (struct rtl_priv*) ; 
 int /*<<< orphan*/  _rtl8821ae_phy_set_reg_bw (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  rtl8812ae_fixspur (struct ieee80211_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8821ae_phy_rf6052_set_bandwidth (struct ieee80211_hw*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 

void rtl8821ae_phy_set_bw_mode_callback(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 sub_chnl = 0;
	u8 l1pk_val = 0;

	RT_TRACE(rtlpriv, COMP_SCAN, DBG_TRACE,
		 "Switch to %s bandwidth\n",
		  (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20 ?
		  "20MHz" :
		  (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40 ?
		  "40MHz" : "80MHz")));

	_rtl8821ae_phy_set_reg_bw(rtlpriv, rtlphy->current_chan_bw);
	sub_chnl = _rtl8821ae_phy_get_secondary_chnl(rtlpriv);
	rtl_write_byte(rtlpriv, 0x0483, sub_chnl);

	switch (rtlphy->current_chan_bw) {
	case HT_CHANNEL_WIDTH_20:
		rtl_set_bbreg(hw, RRFMOD, 0x003003C3, 0x00300200);
		rtl_set_bbreg(hw, RADC_BUF_CLK, BIT(30), 0);

		if (rtlphy->rf_type == RF_2T2R)
			rtl_set_bbreg(hw, RL1PEAKTH, 0x03C00000, 7);
		else
			rtl_set_bbreg(hw, RL1PEAKTH, 0x03C00000, 8);
		break;
	case HT_CHANNEL_WIDTH_20_40:
		rtl_set_bbreg(hw, RRFMOD, 0x003003C3, 0x00300201);
		rtl_set_bbreg(hw, RADC_BUF_CLK, BIT(30), 0);
		rtl_set_bbreg(hw, RRFMOD, 0x3C, sub_chnl);
		rtl_set_bbreg(hw, RCCAONSEC, 0xf0000000, sub_chnl);

		if (rtlphy->reg_837 & BIT(2))
			l1pk_val = 6;
		else {
			if (rtlphy->rf_type == RF_2T2R)
				l1pk_val = 7;
			else
				l1pk_val = 8;
		}
		/* 0x848[25:22] = 0x6 */
		rtl_set_bbreg(hw, RL1PEAKTH, 0x03C00000, l1pk_val);

		if (sub_chnl == VHT_DATA_SC_20_UPPER_OF_80MHZ)
			rtl_set_bbreg(hw, RCCK_SYSTEM, BCCK_SYSTEM, 1);
		else
			rtl_set_bbreg(hw, RCCK_SYSTEM, BCCK_SYSTEM, 0);
		break;

	case HT_CHANNEL_WIDTH_80:
		 /* 0x8ac[21,20,9:6,1,0]=8'b11100010 */
		rtl_set_bbreg(hw, RRFMOD, 0x003003C3, 0x00300202);
		/* 0x8c4[30] = 1 */
		rtl_set_bbreg(hw, RADC_BUF_CLK, BIT(30), 1);
		rtl_set_bbreg(hw, RRFMOD, 0x3C, sub_chnl);
		rtl_set_bbreg(hw, RCCAONSEC, 0xf0000000, sub_chnl);

		if (rtlphy->reg_837 & BIT(2))
			l1pk_val = 5;
		else {
			if (rtlphy->rf_type == RF_2T2R)
				l1pk_val = 6;
			else
				l1pk_val = 7;
		}
		rtl_set_bbreg(hw, RL1PEAKTH, 0x03C00000, l1pk_val);

		break;
	default:
		pr_err("unknown bandwidth: %#X\n",
		       rtlphy->current_chan_bw);
		break;
	}

	rtl8812ae_fixspur(hw, rtlphy->current_chan_bw, rtlphy->current_channel);

	rtl8821ae_phy_rf6052_set_bandwidth(hw, rtlphy->current_chan_bw);
	rtlphy->set_bwmode_inprogress = false;

	RT_TRACE(rtlpriv, COMP_SCAN, DBG_LOUD, "\n");
}