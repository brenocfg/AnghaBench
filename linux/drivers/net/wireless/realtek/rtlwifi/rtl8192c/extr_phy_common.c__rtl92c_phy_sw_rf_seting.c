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
typedef  int u32 ;
struct rtl_phy {scalar_t__ current_chan_bw; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_hal {int /*<<< orphan*/  version; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ HT_CHANNEL_WIDTH_20 ; 
 scalar_t__ IS_81XXC_VENDOR_UMC_B_CUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  RF90_PATH_A ; 
 int /*<<< orphan*/  RFREG_OFFSET_MASK ; 
 int /*<<< orphan*/  RF_RX_G1 ; 
 int /*<<< orphan*/  rtl_get_rfreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_rfreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl92c_phy_sw_rf_seting(struct ieee80211_hw *hw, u8 channel)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	if (IS_81XXC_VENDOR_UMC_B_CUT(rtlhal->version)) {
		if (channel == 6 &&
		    rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20) {
			rtl_set_rfreg(hw, RF90_PATH_A, RF_RX_G1,
				      MASKDWORD, 0x00255);
		} else {
			u32 backuprf0x1A =
			  (u32)rtl_get_rfreg(hw, RF90_PATH_A, RF_RX_G1,
					     RFREG_OFFSET_MASK);
			rtl_set_rfreg(hw, RF90_PATH_A, RF_RX_G1, MASKDWORD,
				      backuprf0x1A);
		}
	}
}