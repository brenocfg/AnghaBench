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
struct rtl_phy {int /*<<< orphan*/ **** tx_power_by_rate_offset; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 size_t BAND_ON_2_4G ; 
 int /*<<< orphan*/  CCK ; 
 int /*<<< orphan*/  COMP_POWER ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  HT_MCS0_MCS7 ; 
 int /*<<< orphan*/  HT_MCS8_MCS15 ; 
 int /*<<< orphan*/  OFDM ; 
 size_t RF90_PATH_A ; 
 size_t RF90_PATH_B ; 
 size_t RF_1TX ; 
 size_t RF_2TX ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _phy_convert_txpower_dbm_to_relative_value (int /*<<< orphan*/ *,int,int,size_t) ; 
 size_t _rtl92ee_phy_get_txpower_by_rate_base (struct ieee80211_hw*,size_t,size_t,size_t,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void phy_convert_txpwr_dbm_to_rel_val(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 base = 0, rf = 0, band = BAND_ON_2_4G;

	for (rf = RF90_PATH_A; rf <= RF90_PATH_B; ++rf) {
		if (rf == RF90_PATH_A) {
			base = _rtl92ee_phy_get_txpower_by_rate_base(hw, band,
								     rf, RF_1TX,
								     CCK);
			_phy_convert_txpower_dbm_to_relative_value(
				&rtlphy->tx_power_by_rate_offset
				[band][rf][RF_1TX][2],
				1, 1, base);
			_phy_convert_txpower_dbm_to_relative_value(
				&rtlphy->tx_power_by_rate_offset
				[band][rf][RF_1TX][3],
				1, 3, base);
		} else if (rf == RF90_PATH_B) {
			base = _rtl92ee_phy_get_txpower_by_rate_base(hw, band,
								     rf, RF_1TX,
								     CCK);
			_phy_convert_txpower_dbm_to_relative_value(
				&rtlphy->tx_power_by_rate_offset
				[band][rf][RF_1TX][3],
				0, 0, base);
			_phy_convert_txpower_dbm_to_relative_value(
				&rtlphy->tx_power_by_rate_offset
				[band][rf][RF_1TX][2],
				1, 3, base);
		}
		base = _rtl92ee_phy_get_txpower_by_rate_base(hw, band, rf,
							     RF_1TX, OFDM);
		_phy_convert_txpower_dbm_to_relative_value(
			&rtlphy->tx_power_by_rate_offset[band][rf][RF_1TX][0],
			0, 3, base);
		_phy_convert_txpower_dbm_to_relative_value(
			&rtlphy->tx_power_by_rate_offset[band][rf][RF_1TX][1],
			0, 3, base);

		base = _rtl92ee_phy_get_txpower_by_rate_base(hw, band, rf,
							     RF_1TX,
							     HT_MCS0_MCS7);
		_phy_convert_txpower_dbm_to_relative_value(
			&rtlphy->tx_power_by_rate_offset[band][rf][RF_1TX][4],
			0, 3, base);
		_phy_convert_txpower_dbm_to_relative_value(
			&rtlphy->tx_power_by_rate_offset[band][rf][RF_1TX][5],
			0, 3, base);

		base = _rtl92ee_phy_get_txpower_by_rate_base(hw, band, rf,
							     RF_2TX,
							     HT_MCS8_MCS15);
		_phy_convert_txpower_dbm_to_relative_value(
			&rtlphy->tx_power_by_rate_offset[band][rf][RF_2TX][6],
			0, 3, base);

		_phy_convert_txpower_dbm_to_relative_value(
			&rtlphy->tx_power_by_rate_offset[band][rf][RF_2TX][7],
			0, 3, base);
	}

	RT_TRACE(rtlpriv, COMP_POWER, DBG_TRACE,
		 "<==phy_convert_txpwr_dbm_to_rel_val()\n");
}