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
typedef  size_t u8 ;
typedef  int u32 ;
struct rtl_phy {int**** tx_power_by_rate_offset; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BAND_ON_2_4G ; 
 int BAND_ON_5G ; 
 int /*<<< orphan*/  FPHY ; 
 int MAX_RF_PATH ; 
 int /*<<< orphan*/  PHY_TXPWR ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 size_t _rtl8723be_get_rate_section_index (int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8723be_store_tx_power_by_rate(struct ieee80211_hw *hw,
					      u32 band, u32 rfpath,
					      u32 txnum, u32 regaddr,
					      u32 bitmask, u32 data)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 rate_section = _rtl8723be_get_rate_section_index(regaddr);

	if (band != BAND_ON_2_4G && band != BAND_ON_5G) {
		RT_TRACE(rtlpriv, FPHY, PHY_TXPWR, "Invalid Band %d\n", band);
		return;
	}
	if (rfpath > MAX_RF_PATH - 1) {
		RT_TRACE(rtlpriv, FPHY, PHY_TXPWR,
			 "Invalid RfPath %d\n", rfpath);
		return;
	}
	if (txnum > MAX_RF_PATH - 1) {
		RT_TRACE(rtlpriv, FPHY, PHY_TXPWR, "Invalid TxNum %d\n", txnum);
		return;
	}

	rtlphy->tx_power_by_rate_offset[band][rfpath][txnum][rate_section] =
									data;

}