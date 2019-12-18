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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  REG_DBI_CTRL ; 
 int /*<<< orphan*/  REG_DBI_FLAG ; 
 int /*<<< orphan*/  REG_DBI_RDATA ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

u32 rtl92de_read_dword_dbi(struct ieee80211_hw *hw, u16 offset, u8 direct)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 value;

	rtl_write_word(rtlpriv, REG_DBI_CTRL, (offset & 0xFFC));
	rtl_write_byte(rtlpriv, REG_DBI_FLAG, BIT(1) | direct);
	udelay(10);
	value = rtl_read_dword(rtlpriv, REG_DBI_RDATA);
	return value;
}