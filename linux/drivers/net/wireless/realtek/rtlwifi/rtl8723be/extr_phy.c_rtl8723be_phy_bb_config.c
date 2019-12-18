#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int crystalcap; } ;
struct rtl_priv {TYPE_1__ efuse; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int FEN_BBRSTB ; 
 int FEN_BB_GLB_RSTN ; 
 int FEN_DIO_PCIE ; 
 int FEN_PCIEA ; 
 int FEN_PPLL ; 
 scalar_t__ REG_AFE_XTAL_CTRL ; 
 int /*<<< orphan*/  REG_MAC_PHY_CTRL ; 
 scalar_t__ REG_RF_CTRL ; 
 scalar_t__ REG_SYS_FUNC_EN ; 
 int RF_EN ; 
 int RF_RSTB ; 
 int RF_SDMRSTB ; 
 int _rtl8723be_phy_bb8723b_config_parafile (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723_phy_init_bb_rf_reg_def (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_dword (struct rtl_priv*,int) ; 
 int rtl_read_word (struct rtl_priv*,scalar_t__) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,scalar_t__,int) ; 

bool rtl8723be_phy_bb_config(struct ieee80211_hw *hw)
{
	bool rtstatus = true;
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u16 regval;
	u8 b_reg_hwparafile = 1;
	u32 tmp;
	u8 crystalcap = rtlpriv->efuse.crystalcap;
	rtl8723_phy_init_bb_rf_reg_def(hw);
	regval = rtl_read_word(rtlpriv, REG_SYS_FUNC_EN);
	rtl_write_word(rtlpriv, REG_SYS_FUNC_EN,
		       regval | BIT(13) | BIT(0) | BIT(1));

	rtl_write_byte(rtlpriv, REG_RF_CTRL, RF_EN | RF_RSTB | RF_SDMRSTB);
	rtl_write_byte(rtlpriv, REG_SYS_FUNC_EN,
		       FEN_PPLL | FEN_PCIEA | FEN_DIO_PCIE |
		       FEN_BB_GLB_RSTN | FEN_BBRSTB);
	tmp = rtl_read_dword(rtlpriv, 0x4c);
	rtl_write_dword(rtlpriv, 0x4c, tmp | BIT(23));

	rtl_write_byte(rtlpriv, REG_AFE_XTAL_CTRL + 1, 0x80);

	if (b_reg_hwparafile == 1)
		rtstatus = _rtl8723be_phy_bb8723b_config_parafile(hw);

	crystalcap = crystalcap & 0x3F;
	rtl_set_bbreg(hw, REG_MAC_PHY_CTRL, 0xFFF000,
		      (crystalcap | crystalcap << 6));

	return rtstatus;
}