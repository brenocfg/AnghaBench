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
struct rtl_hal {scalar_t__ macphymode; int interfaceindex; scalar_t__ current_bandtype; int /*<<< orphan*/  version; } ;
struct rtl_priv {struct rtl_hal rtlhal; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAND_ON_5G ; 
 int BIT (int) ; 
 scalar_t__ DUALMAC_DUALPHY ; 
 int /*<<< orphan*/  FINIT ; 
 int /*<<< orphan*/  INIT_IQK ; 
 scalar_t__ IS_92D_SINGLEPHY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int ROFDM0_ECCATHRESHOLD ; 
 int ROFDM0_XARXIQIMBALANCE ; 
 int ROFDM0_XATXIQIMBALANCE ; 
 int ROFDM0_XCTXAFE ; 
 int /*<<< orphan*/  RTPRINT (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int rtl_get_bbreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int,int) ; 

__attribute__((used)) static void _rtl92d_phy_patha_fill_iqk_matrix(struct ieee80211_hw *hw,
					      bool iqk_ok, long result[][8],
					      u8 final_candidate, bool txonly)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = &(rtlpriv->rtlhal);
	u32 oldval_0, val_x, tx0_a, reg;
	long val_y, tx0_c;
	bool is2t = IS_92D_SINGLEPHY(rtlhal->version) ||
	    rtlhal->macphymode == DUALMAC_DUALPHY;

	RTPRINT(rtlpriv, FINIT, INIT_IQK,
		"Path A IQ Calibration %s !\n", iqk_ok ? "Success" : "Failed");
	if (final_candidate == 0xFF) {
		return;
	} else if (iqk_ok) {
		oldval_0 = (rtl_get_bbreg(hw, ROFDM0_XATXIQIMBALANCE,
			MASKDWORD) >> 22) & 0x3FF;	/* OFDM0_D */
		val_x = result[final_candidate][0];
		if ((val_x & 0x00000200) != 0)
			val_x = val_x | 0xFFFFFC00;
		tx0_a = (val_x * oldval_0) >> 8;
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"X = 0x%x, tx0_a = 0x%x, oldval_0 0x%x\n",
			val_x, tx0_a, oldval_0);
		rtl_set_bbreg(hw, ROFDM0_XATXIQIMBALANCE, 0x3FF, tx0_a);
		rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD, BIT(24),
			      ((val_x * oldval_0 >> 7) & 0x1));
		val_y = result[final_candidate][1];
		if ((val_y & 0x00000200) != 0)
			val_y = val_y | 0xFFFFFC00;
		/* path B IQK result + 3 */
		if (rtlhal->interfaceindex == 1 &&
			rtlhal->current_bandtype == BAND_ON_5G)
			val_y += 3;
		tx0_c = (val_y * oldval_0) >> 8;
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"Y = 0x%lx, tx0_c = 0x%lx\n",
			val_y, tx0_c);
		rtl_set_bbreg(hw, ROFDM0_XCTXAFE, 0xF0000000,
			      ((tx0_c & 0x3C0) >> 6));
		rtl_set_bbreg(hw, ROFDM0_XATXIQIMBALANCE, 0x003F0000,
			      (tx0_c & 0x3F));
		if (is2t)
			rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD, BIT(26),
				      ((val_y * oldval_0 >> 7) & 0x1));
		RTPRINT(rtlpriv, FINIT, INIT_IQK, "0xC80 = 0x%x\n",
			rtl_get_bbreg(hw, ROFDM0_XATXIQIMBALANCE,
				      MASKDWORD));
		if (txonly) {
			RTPRINT(rtlpriv, FINIT, INIT_IQK,  "only Tx OK\n");
			return;
		}
		reg = result[final_candidate][2];
		rtl_set_bbreg(hw, ROFDM0_XARXIQIMBALANCE, 0x3FF, reg);
		reg = result[final_candidate][3] & 0x3F;
		rtl_set_bbreg(hw, ROFDM0_XARXIQIMBALANCE, 0xFC00, reg);
		reg = (result[final_candidate][3] >> 6) & 0xF;
		rtl_set_bbreg(hw, 0xca0, 0xF0000000, reg);
	}
}