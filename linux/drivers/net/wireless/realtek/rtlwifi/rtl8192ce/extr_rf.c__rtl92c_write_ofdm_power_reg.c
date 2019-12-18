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
struct rtl_phy {int dummy; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPHY ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  PHY_TXPWR ; 
 int RF6052_MAX_TX_PWR ; 
 scalar_t__ RF_2T2R ; 
 int /*<<< orphan*/  RTPRINT (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int RTXAGC_A_MCS03_MCS00 ; 
 int RTXAGC_A_MCS07_MCS04 ; 
 int RTXAGC_A_MCS11_MCS08 ; 
 int RTXAGC_A_MCS15_MCS12 ; 
 int RTXAGC_A_RATE18_06 ; 
 int RTXAGC_A_RATE54_24 ; 
 int RTXAGC_B_MCS03_MCS00 ; 
 int RTXAGC_B_MCS07_MCS04 ; 
 int RTXAGC_B_MCS11_MCS08 ; 
 int RTXAGC_B_MCS15_MCS12 ; 
 int RTXAGC_B_RATE18_06 ; 
 int RTXAGC_B_RATE54_24 ; 
 scalar_t__ get_rf_type (struct rtl_phy*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 

__attribute__((used)) static void _rtl92c_write_ofdm_power_reg(struct ieee80211_hw *hw,
					 u8 index, u32 *value)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);

	u16 regoffset_a[6] = {
		RTXAGC_A_RATE18_06, RTXAGC_A_RATE54_24,
		RTXAGC_A_MCS03_MCS00, RTXAGC_A_MCS07_MCS04,
		RTXAGC_A_MCS11_MCS08, RTXAGC_A_MCS15_MCS12
	};
	u16 regoffset_b[6] = {
		RTXAGC_B_RATE18_06, RTXAGC_B_RATE54_24,
		RTXAGC_B_MCS03_MCS00, RTXAGC_B_MCS07_MCS04,
		RTXAGC_B_MCS11_MCS08, RTXAGC_B_MCS15_MCS12
	};
	u8 i, rf, pwr_val[4];
	u32 writeval;
	u16 regoffset;

	for (rf = 0; rf < 2; rf++) {
		writeval = value[rf];
		for (i = 0; i < 4; i++) {
			pwr_val[i] = (u8)((writeval & (0x7f <<
							(i * 8))) >> (i * 8));

			if (pwr_val[i] > RF6052_MAX_TX_PWR)
				pwr_val[i] = RF6052_MAX_TX_PWR;
		}
		writeval = (pwr_val[3] << 24) | (pwr_val[2] << 16) |
		    (pwr_val[1] << 8) | pwr_val[0];

		if (rf == 0)
			regoffset = regoffset_a[index];
		else
			regoffset = regoffset_b[index];
		rtl_set_bbreg(hw, regoffset, MASKDWORD, writeval);

		RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
			"Set 0x%x = %08x\n", regoffset, writeval);

		if (((get_rf_type(rtlphy) == RF_2T2R) &&
		     (regoffset == RTXAGC_A_MCS15_MCS12 ||
		      regoffset == RTXAGC_B_MCS15_MCS12)) ||
		    ((get_rf_type(rtlphy) != RF_2T2R) &&
		     (regoffset == RTXAGC_A_MCS07_MCS04 ||
		      regoffset == RTXAGC_B_MCS07_MCS04))) {

			writeval = pwr_val[3];
			if (regoffset == RTXAGC_A_MCS15_MCS12 ||
			    regoffset == RTXAGC_A_MCS07_MCS04)
				regoffset = 0xc90;
			if (regoffset == RTXAGC_B_MCS15_MCS12 ||
			    regoffset == RTXAGC_B_MCS07_MCS04)
				regoffset = 0xc98;

			for (i = 0; i < 3; i++) {
				writeval = (writeval > 6) ? (writeval - 6) : 0;
				rtl_write_byte(rtlpriv, (u32) (regoffset + i),
					       (u8)writeval);
			}
		}
	}
}