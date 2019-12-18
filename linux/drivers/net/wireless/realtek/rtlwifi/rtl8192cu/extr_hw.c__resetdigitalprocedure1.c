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
typedef  int u16 ;
struct rtl_priv {int dummy; } ;
struct rtl_hal {int fw_version; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int FEN_CPUEN ; 
 int FEN_ELDR ; 
 int FEN_HWPDN ; 
 scalar_t__ REG_AFE_PLL_CTRL ; 
 scalar_t__ REG_AFE_XTAL_CTRL ; 
 scalar_t__ REG_HMETFR ; 
 scalar_t__ REG_MCUFWDL ; 
 scalar_t__ REG_SYS_CLKR ; 
 scalar_t__ REG_SYS_FUNC_EN ; 
 scalar_t__ REG_SYS_ISO_CTRL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,scalar_t__) ; 
 int rtl_read_word (struct rtl_priv*,scalar_t__) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void  _resetdigitalprocedure1(struct ieee80211_hw *hw, bool withouthwsm)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	if (rtlhal->fw_version <=  0x20) {
		/*****************************
		f. MCUFWDL 0x80[7:0]=0		reset MCU ready status
		g. SYS_FUNC_EN 0x02[10]= 0	reset MCU reg, (8051 reset)
		h. SYS_FUNC_EN 0x02[15-12]= 5	reset MAC reg, DCORE
		i. SYS_FUNC_EN 0x02[10]= 1	enable MCU reg, (8051 enable)
		******************************/
		u16 valu16 = 0;

		rtl_write_byte(rtlpriv, REG_MCUFWDL, 0);
		valu16 = rtl_read_word(rtlpriv, REG_SYS_FUNC_EN);
		rtl_write_word(rtlpriv, REG_SYS_FUNC_EN, (valu16 &
			       (~FEN_CPUEN))); /* reset MCU ,8051 */
		valu16 = rtl_read_word(rtlpriv, REG_SYS_FUNC_EN)&0x0FFF;
		rtl_write_word(rtlpriv, REG_SYS_FUNC_EN, (valu16 |
			      (FEN_HWPDN|FEN_ELDR))); /* reset MAC */
		valu16 = rtl_read_word(rtlpriv, REG_SYS_FUNC_EN);
		rtl_write_word(rtlpriv, REG_SYS_FUNC_EN, (valu16 |
			       FEN_CPUEN)); /* enable MCU ,8051 */
	} else {
		u8 retry_cnts = 0;

		/* IF fw in RAM code, do reset */
		if (rtl_read_byte(rtlpriv, REG_MCUFWDL) & BIT(1)) {
			/* reset MCU ready status */
			rtl_write_byte(rtlpriv, REG_MCUFWDL, 0);
			/* 8051 reset by self */
			rtl_write_byte(rtlpriv, REG_HMETFR+3, 0x20);
			while ((retry_cnts++ < 100) &&
			       (FEN_CPUEN & rtl_read_word(rtlpriv,
			       REG_SYS_FUNC_EN))) {
				udelay(50);
			}
			if (retry_cnts >= 100) {
				pr_err("8051 reset failed!.........................\n");
				/* if 8051 reset fail, reset MAC. */
				rtl_write_byte(rtlpriv,
					       REG_SYS_FUNC_EN + 1,
					       0x50);
				udelay(100);
			}
		}
		/* Reset MAC and Enable 8051 */
		rtl_write_byte(rtlpriv, REG_SYS_FUNC_EN + 1, 0x54);
		rtl_write_byte(rtlpriv, REG_MCUFWDL, 0);
	}
	if (withouthwsm) {
		/*****************************
		  Without HW auto state machine
		g.SYS_CLKR 0x08[15:0] = 0x30A3		disable MAC clock
		h.AFE_PLL_CTRL 0x28[7:0] = 0x80		disable AFE PLL
		i.AFE_XTAL_CTRL 0x24[15:0] = 0x880F	gated AFE DIG_CLOCK
		j.SYS_ISu_CTRL 0x00[7:0] = 0xF9		isolated digital to PON
		******************************/
		rtl_write_word(rtlpriv, REG_SYS_CLKR, 0x70A3);
		rtl_write_byte(rtlpriv, REG_AFE_PLL_CTRL, 0x80);
		rtl_write_word(rtlpriv, REG_AFE_XTAL_CTRL, 0x880F);
		rtl_write_byte(rtlpriv, REG_SYS_ISO_CTRL, 0xF9);
	}
}