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
typedef  size_t u32 ;
struct rtl_phy {size_t**** tx_power_by_rate_offset; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 size_t BAND_ON_2_4G ; 
 size_t BAND_ON_5G ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_WARNING ; 
 size_t MAX_RF_PATH ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,...) ; 
 size_t _rtl8821ae_get_rate_section_index (size_t) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8821ae_store_tx_power_by_rate(struct ieee80211_hw *hw,
					      u32 band, u32 rfpath,
					      u32 txnum, u32 regaddr,
					      u32 bitmask, u32 data)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 rate_section = _rtl8821ae_get_rate_section_index(regaddr);

	if (band != BAND_ON_2_4G && band != BAND_ON_5G) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_WARNING, "Invalid Band %d\n", band);
		band = BAND_ON_2_4G;
	}
	if (rfpath >= MAX_RF_PATH) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_WARNING, "Invalid RfPath %d\n", rfpath);
		rfpath = MAX_RF_PATH - 1;
	}
	if (txnum >= MAX_RF_PATH) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_WARNING, "Invalid TxNum %d\n", txnum);
		txnum = MAX_RF_PATH - 1;
	}
	rtlphy->tx_power_by_rate_offset[band][rfpath][txnum][rate_section] = data;
	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "TxPwrByRateOffset[Band %d][RfPath %d][TxNum %d][RateSection %d] = 0x%x\n",
		 band, rfpath, txnum, rate_section,
		 rtlphy->tx_power_by_rate_offset[band][rfpath][txnum][rate_section]);
}