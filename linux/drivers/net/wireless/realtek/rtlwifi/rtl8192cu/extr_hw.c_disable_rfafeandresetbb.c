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
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 int APSDOFF ; 
 int FEN_BB_GLB_RSTN ; 
 int FEN_USBA ; 
 int FEN_USBD ; 
 int /*<<< orphan*/  MASKBYTE0 ; 
 int /*<<< orphan*/  REG_APSD_CTRL ; 
 int /*<<< orphan*/  REG_SYS_FUNC_EN ; 
 int /*<<< orphan*/  REG_TXPAUSE ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_rfreg (struct ieee80211_hw*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void disable_rfafeandresetbb(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
/**************************************
a.	TXPAUSE 0x522[7:0] = 0xFF	Pause MAC TX queue
b.	RF path 0 offset 0x00 = 0x00	disable RF
c.	APSD_CTRL 0x600[7:0] = 0x40
d.	SYS_FUNC_EN 0x02[7:0] = 0x16	reset BB state machine
e.	SYS_FUNC_EN 0x02[7:0] = 0x14	reset BB state machine
***************************************/
	u8 erfpath = 0, value8 = 0;

	rtl_write_byte(rtlpriv, REG_TXPAUSE, 0xFF);
	rtl_set_rfreg(hw, (enum radio_path)erfpath, 0x0, MASKBYTE0, 0x0);

	value8 |= APSDOFF;
	rtl_write_byte(rtlpriv, REG_APSD_CTRL, value8); /*0x40*/
	value8 = 0;
	value8 |= (FEN_USBD | FEN_USBA | FEN_BB_GLB_RSTN);
	rtl_write_byte(rtlpriv, REG_SYS_FUNC_EN, value8);/*0x16*/
	value8 &= (~FEN_BB_GLB_RSTN);
	rtl_write_byte(rtlpriv, REG_SYS_FUNC_EN, value8); /*0x14*/
}