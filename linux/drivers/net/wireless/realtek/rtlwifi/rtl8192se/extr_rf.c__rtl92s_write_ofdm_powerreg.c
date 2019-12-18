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
typedef  int u16 ;
struct rtl_phy {scalar_t__ rf_type; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_efuse {int* antenna_txpwdiff; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int RF6052_MAX_TX_PWR ; 
 scalar_t__ RF_2T2R ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int,int) ; 

__attribute__((used)) static void _rtl92s_write_ofdm_powerreg(struct ieee80211_hw *hw,
					u8 index, u32 val)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u16 regoffset[6] = {0xe00, 0xe04, 0xe10, 0xe14, 0xe18, 0xe1c};
	u8 i, rfa_pwr[4];
	u8 rfa_lower_bound = 0, rfa_upper_bound = 0, rf_pwr_diff = 0;
	u32 writeval = val;

	/* If path A and Path B coexist, we must limit Path A tx power.
	 * Protect Path B pwr over or under flow. We need to calculate
	 * upper and lower bound of path A tx power. */
	if (rtlphy->rf_type == RF_2T2R) {
		rf_pwr_diff = rtlefuse->antenna_txpwdiff[0];

		/* Diff=-8~-1 */
		if (rf_pwr_diff >= 8) {
			/* Prevent underflow!! */
			rfa_lower_bound = 0x10 - rf_pwr_diff;
		/* if (rf_pwr_diff >= 0) Diff = 0-7 */
		} else {
			rfa_upper_bound = RF6052_MAX_TX_PWR - rf_pwr_diff;
		}
	}

	for (i = 0; i < 4; i++) {
		rfa_pwr[i] = (u8)((writeval & (0x7f << (i * 8))) >> (i * 8));
		if (rfa_pwr[i]  > RF6052_MAX_TX_PWR)
			rfa_pwr[i]  = RF6052_MAX_TX_PWR;

		/* If path A and Path B coexist, we must limit Path A tx power.
		 * Protect Path B pwr over or under flow. We need to calculate
		 * upper and lower bound of path A tx power. */
		if (rtlphy->rf_type == RF_2T2R) {
			/* Diff=-8~-1 */
			if (rf_pwr_diff >= 8) {
				/* Prevent underflow!! */
				if (rfa_pwr[i] < rfa_lower_bound)
					rfa_pwr[i] = rfa_lower_bound;
			/* Diff = 0-7 */
			} else if (rf_pwr_diff >= 1) {
				/* Prevent overflow */
				if (rfa_pwr[i] > rfa_upper_bound)
					rfa_pwr[i] = rfa_upper_bound;
			}
		}

	}

	writeval = (rfa_pwr[3] << 24) | (rfa_pwr[2] << 16) | (rfa_pwr[1] << 8) |
				rfa_pwr[0];

	rtl_set_bbreg(hw, regoffset[index], 0x7f7f7f7f, writeval);
}