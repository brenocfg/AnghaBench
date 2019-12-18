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
struct rtl_ps_ctl {int /*<<< orphan*/  support_backdoor; scalar_t__ support_aspm; } ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtl92s_phy_check_ephy_switchready (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int,int) ; 

void rtl92s_phy_switch_ephy_parameter(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	/* The way to be capable to switch clock request
	 * when the PG setting does not support clock request.
	 * This is the backdoor solution to switch clock
	 * request before ASPM or D3. */
	rtl_write_dword(rtlpriv, 0x540, 0x73c11);
	rtl_write_dword(rtlpriv, 0x548, 0x2407c);

	/* Switch EPHY parameter!!!! */
	rtl_write_word(rtlpriv, 0x550, 0x1000);
	rtl_write_byte(rtlpriv, 0x554, 0x20);
	_rtl92s_phy_check_ephy_switchready(hw);

	rtl_write_word(rtlpriv, 0x550, 0xa0eb);
	rtl_write_byte(rtlpriv, 0x554, 0x3e);
	_rtl92s_phy_check_ephy_switchready(hw);

	rtl_write_word(rtlpriv, 0x550, 0xff80);
	rtl_write_byte(rtlpriv, 0x554, 0x39);
	_rtl92s_phy_check_ephy_switchready(hw);

	/* Delay L1 enter time */
	if (ppsc->support_aspm && !ppsc->support_backdoor)
		rtl_write_byte(rtlpriv, 0x560, 0x40);
	else
		rtl_write_byte(rtlpriv, 0x560, 0x00);

}