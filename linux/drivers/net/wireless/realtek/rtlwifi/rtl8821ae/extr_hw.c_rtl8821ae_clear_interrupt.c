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
typedef  int /*<<< orphan*/  u32 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_HISR ; 
 int /*<<< orphan*/  REG_HISRE ; 
 int /*<<< orphan*/  REG_HSISR ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8821ae_clear_interrupt(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 tmp = rtl_read_dword(rtlpriv, REG_HISR);

	rtl_write_dword(rtlpriv, REG_HISR, tmp);

	tmp = rtl_read_dword(rtlpriv, REG_HISRE);
	rtl_write_dword(rtlpriv, REG_HISRE, tmp);

	tmp = rtl_read_dword(rtlpriv, REG_HSISR);
	rtl_write_dword(rtlpriv, REG_HSISR, tmp);
}