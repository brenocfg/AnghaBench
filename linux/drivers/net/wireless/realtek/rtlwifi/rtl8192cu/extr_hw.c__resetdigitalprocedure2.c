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
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SYS_CLKR ; 
 scalar_t__ REG_SYS_ISO_CTRL ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _resetdigitalprocedure2(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
/*****************************
k. SYS_FUNC_EN 0x03[7:0] = 0x44		disable ELDR runction
l. SYS_CLKR 0x08[15:0] = 0x3083		disable ELDR clock
m. SYS_ISO_CTRL 0x01[7:0] = 0x83	isolated ELDR to PON
******************************/
	rtl_write_word(rtlpriv, REG_SYS_CLKR, 0x70A3);
	rtl_write_byte(rtlpriv, REG_SYS_ISO_CTRL+1, 0x82);
}