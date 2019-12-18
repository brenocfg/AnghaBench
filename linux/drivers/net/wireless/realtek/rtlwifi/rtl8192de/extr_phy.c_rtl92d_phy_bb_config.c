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
struct TYPE_2__ {int /*<<< orphan*/  version; } ;
struct rtl_priv {TYPE_1__ rtlhal; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int FEN_BBRSTB ; 
 int FEN_BB_GLB_RSTN ; 
 int FEN_DIO_PCIE ; 
 int FEN_PCIEA ; 
 int FEN_PPLL ; 
 int /*<<< orphan*/  IS_92D_SINGLEPHY (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_AFE_PLL_CTRL ; 
 scalar_t__ REG_AFE_XTAL_CTRL ; 
 int /*<<< orphan*/  REG_LEDCFG0 ; 
 scalar_t__ REG_RF_CTRL ; 
 scalar_t__ REG_SYS_FUNC_EN ; 
 int RF_EN ; 
 int RF_RSTB ; 
 int RF_SDMRSTB ; 
 int _rtl92d_phy_bb_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl92d_phy_init_bb_rf_register_definition (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,scalar_t__) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int rtl_read_word (struct rtl_priv*,scalar_t__) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,scalar_t__,int) ; 

bool rtl92d_phy_bb_config(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u16 regval;
	u32 regvaldw;
	u8 value;

	_rtl92d_phy_init_bb_rf_register_definition(hw);
	regval = rtl_read_word(rtlpriv, REG_SYS_FUNC_EN);
	rtl_write_word(rtlpriv, REG_SYS_FUNC_EN,
		       regval | BIT(13) | BIT(0) | BIT(1));
	rtl_write_byte(rtlpriv, REG_AFE_PLL_CTRL, 0x83);
	rtl_write_byte(rtlpriv, REG_AFE_PLL_CTRL + 1, 0xdb);
	/* 0x1f bit7 bit6 represent for mac0/mac1 driver ready */
	value = rtl_read_byte(rtlpriv, REG_RF_CTRL);
	rtl_write_byte(rtlpriv, REG_RF_CTRL, value | RF_EN | RF_RSTB |
		RF_SDMRSTB);
	rtl_write_byte(rtlpriv, REG_SYS_FUNC_EN, FEN_PPLL | FEN_PCIEA |
		FEN_DIO_PCIE | FEN_BB_GLB_RSTN | FEN_BBRSTB);
	rtl_write_byte(rtlpriv, REG_AFE_XTAL_CTRL + 1, 0x80);
	if (!(IS_92D_SINGLEPHY(rtlpriv->rtlhal.version))) {
		regvaldw = rtl_read_dword(rtlpriv, REG_LEDCFG0);
		rtl_write_dword(rtlpriv, REG_LEDCFG0, regvaldw | BIT(23));
	}

	return _rtl92d_phy_bb_config(hw);
}