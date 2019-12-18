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
struct rtl_hal {scalar_t__ current_bandtype; } ;
struct rtl_priv {struct rtl_hal rtlhal; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAND_ON_5G ; 
 int BIT (int) ; 
 int /*<<< orphan*/  FINIT ; 
 int /*<<< orphan*/  INIT_IQK ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  ROFDM0_AGCRSSITABLE ; 
 int /*<<< orphan*/  ROFDM0_ECCATHRESHOLD ; 
 int /*<<< orphan*/  ROFDM0_XBRXIQIMBALANCE ; 
 int /*<<< orphan*/  ROFDM0_XBTXIQIMBALANCE ; 
 int /*<<< orphan*/  ROFDM0_XDTXAFE ; 
 int /*<<< orphan*/  RTPRINT (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int rtl_get_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void _rtl92d_phy_pathb_fill_iqk_matrix(struct ieee80211_hw *hw,
	bool iqk_ok, long result[][8], u8 final_candidate, bool txonly)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = &(rtlpriv->rtlhal);
	u32 oldval_1, val_x, tx1_a, reg;
	long val_y, tx1_c;

	RTPRINT(rtlpriv, FINIT, INIT_IQK, "Path B IQ Calibration %s !\n",
		iqk_ok ? "Success" : "Failed");
	if (final_candidate == 0xFF) {
		return;
	} else if (iqk_ok) {
		oldval_1 = (rtl_get_bbreg(hw, ROFDM0_XBTXIQIMBALANCE,
					  MASKDWORD) >> 22) & 0x3FF;
		val_x = result[final_candidate][4];
		if ((val_x & 0x00000200) != 0)
			val_x = val_x | 0xFFFFFC00;
		tx1_a = (val_x * oldval_1) >> 8;
		RTPRINT(rtlpriv, FINIT, INIT_IQK, "X = 0x%x, tx1_a = 0x%x\n",
			val_x, tx1_a);
		rtl_set_bbreg(hw, ROFDM0_XBTXIQIMBALANCE, 0x3FF, tx1_a);
		rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD, BIT(28),
			      ((val_x * oldval_1 >> 7) & 0x1));
		val_y = result[final_candidate][5];
		if ((val_y & 0x00000200) != 0)
			val_y = val_y | 0xFFFFFC00;
		if (rtlhal->current_bandtype == BAND_ON_5G)
			val_y += 3;
		tx1_c = (val_y * oldval_1) >> 8;
		RTPRINT(rtlpriv, FINIT, INIT_IQK, "Y = 0x%lx, tx1_c = 0x%lx\n",
			val_y, tx1_c);
		rtl_set_bbreg(hw, ROFDM0_XDTXAFE, 0xF0000000,
			      ((tx1_c & 0x3C0) >> 6));
		rtl_set_bbreg(hw, ROFDM0_XBTXIQIMBALANCE, 0x003F0000,
			      (tx1_c & 0x3F));
		rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD, BIT(30),
			      ((val_y * oldval_1 >> 7) & 0x1));
		if (txonly)
			return;
		reg = result[final_candidate][6];
		rtl_set_bbreg(hw, ROFDM0_XBRXIQIMBALANCE, 0x3FF, reg);
		reg = result[final_candidate][7] & 0x3F;
		rtl_set_bbreg(hw, ROFDM0_XBRXIQIMBALANCE, 0xFC00, reg);
		reg = (result[final_candidate][7] >> 6) & 0xF;
		rtl_set_bbreg(hw, ROFDM0_AGCRSSITABLE, 0x0000F000, reg);
	}
}