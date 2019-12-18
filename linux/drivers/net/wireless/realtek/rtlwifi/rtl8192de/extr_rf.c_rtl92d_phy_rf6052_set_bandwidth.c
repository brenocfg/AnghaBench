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
struct rtl_phy {int num_total_rfpath; int* rfreg_chnlval; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_RF ; 
 int /*<<< orphan*/  DBG_LOUD ; 
#define  HT_CHANNEL_WIDTH_20 129 
#define  HT_CHANNEL_WIDTH_20_40 128 
 int /*<<< orphan*/  RF_CHNLBW ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_rfreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int,int) ; 

void rtl92d_phy_rf6052_set_bandwidth(struct ieee80211_hw *hw, u8 bandwidth)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	u8 rfpath;

	switch (bandwidth) {
	case HT_CHANNEL_WIDTH_20:
		for (rfpath = 0; rfpath < rtlphy->num_total_rfpath; rfpath++) {
			rtlphy->rfreg_chnlval[rfpath] = ((rtlphy->rfreg_chnlval
					[rfpath] & 0xfffff3ff) | 0x0400);
			rtl_set_rfreg(hw, rfpath, RF_CHNLBW, BIT(10) |
				      BIT(11), 0x01);

			RT_TRACE(rtlpriv, COMP_RF, DBG_LOUD,
				 "20M RF 0x18 = 0x%x\n",
				 rtlphy->rfreg_chnlval[rfpath]);
		}

		break;
	case HT_CHANNEL_WIDTH_20_40:
		for (rfpath = 0; rfpath < rtlphy->num_total_rfpath; rfpath++) {
			rtlphy->rfreg_chnlval[rfpath] =
			    ((rtlphy->rfreg_chnlval[rfpath] & 0xfffff3ff));
			rtl_set_rfreg(hw, rfpath, RF_CHNLBW, BIT(10) | BIT(11),
				      0x00);
			RT_TRACE(rtlpriv, COMP_RF, DBG_LOUD,
				 "40M RF 0x18 = 0x%x\n",
				 rtlphy->rfreg_chnlval[rfpath]);
		}
		break;
	default:
		pr_err("unknown bandwidth: %#X\n", bandwidth);
		break;
	}
}