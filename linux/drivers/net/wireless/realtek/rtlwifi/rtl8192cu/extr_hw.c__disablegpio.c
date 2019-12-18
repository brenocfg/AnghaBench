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
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ REG_GPIO_MUXCFG ; 
 scalar_t__ REG_GPIO_PIN_CTRL ; 
 scalar_t__ REG_LEDCFG0 ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_dword (struct rtl_priv*,scalar_t__) ; 
 int rtl_read_word (struct rtl_priv*,scalar_t__) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,scalar_t__,int) ; 

__attribute__((used)) static void _disablegpio(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
/***************************************
j. GPIO_PIN_CTRL 0x44[31:0]=0x000
k. Value = GPIO_PIN_CTRL[7:0]
l.  GPIO_PIN_CTRL 0x44[31:0] = 0x00FF0000 | (value <<8); write ext PIN level
m. GPIO_MUXCFG 0x42 [15:0] = 0x0780
n. LEDCFG 0x4C[15:0] = 0x8080
***************************************/
	u8	value8;
	u16	value16;
	u32	value32;

	/* 1. Disable GPIO[7:0] */
	rtl_write_word(rtlpriv, REG_GPIO_PIN_CTRL+2, 0x0000);
	value32 = rtl_read_dword(rtlpriv, REG_GPIO_PIN_CTRL) & 0xFFFF00FF;
	value8 = (u8)(value32&0x000000FF);
	value32 |= ((value8<<8) | 0x00FF0000);
	rtl_write_dword(rtlpriv, REG_GPIO_PIN_CTRL, value32);
	/* 2. Disable GPIO[10:8] */
	rtl_write_byte(rtlpriv, REG_GPIO_MUXCFG+3, 0x00);
	value16 = rtl_read_word(rtlpriv, REG_GPIO_MUXCFG+2) & 0xFF0F;
	value8 = (u8)(value16&0x000F);
	value16 |= ((value8<<4) | 0x0780);
	rtl_write_word(rtlpriv, REG_GPIO_PIN_CTRL+2, value16);
	/* 3. Disable LED0 & 1 */
	rtl_write_word(rtlpriv, REG_LEDCFG0, 0x8080);
}