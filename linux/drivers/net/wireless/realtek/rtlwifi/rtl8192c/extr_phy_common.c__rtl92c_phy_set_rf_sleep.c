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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_POWER ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  REG_APSD_CTRL ; 
 int /*<<< orphan*/  REG_SPS0_CTRL ; 
 int /*<<< orphan*/  REG_SYS_FUNC_EN ; 
 int /*<<< orphan*/  REG_TXPAUSE ; 
 int /*<<< orphan*/  RF90_PATH_A ; 
 int /*<<< orphan*/  RFREG_OFFSET_MASK ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ rtl_get_rfreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_rfreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

void _rtl92c_phy_set_rf_sleep(struct ieee80211_hw *hw)
{
	u32 u4b_tmp;
	u8 delay = 5;
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_write_byte(rtlpriv, REG_TXPAUSE, 0xFF);
	rtl_set_rfreg(hw, RF90_PATH_A, 0x00, RFREG_OFFSET_MASK, 0x00);
	rtl_write_byte(rtlpriv, REG_APSD_CTRL, 0x40);
	u4b_tmp = rtl_get_rfreg(hw, RF90_PATH_A, 0, RFREG_OFFSET_MASK);
	while (u4b_tmp != 0 && delay > 0) {
		rtl_write_byte(rtlpriv, REG_APSD_CTRL, 0x0);
		rtl_set_rfreg(hw, RF90_PATH_A, 0x00, RFREG_OFFSET_MASK, 0x00);
		rtl_write_byte(rtlpriv, REG_APSD_CTRL, 0x40);
		u4b_tmp = rtl_get_rfreg(hw, RF90_PATH_A, 0, RFREG_OFFSET_MASK);
		delay--;
	}
	if (delay == 0) {
		rtl_write_byte(rtlpriv, REG_APSD_CTRL, 0x00);
		rtl_write_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE2);
		rtl_write_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE3);
		rtl_write_byte(rtlpriv, REG_TXPAUSE, 0x00);
		RT_TRACE(rtlpriv, COMP_POWER, DBG_TRACE,
			 "Switch RF timeout !!!.\n");
		return;
	}
	rtl_write_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE2);
	rtl_write_byte(rtlpriv, REG_SPS0_CTRL, 0x22);
}