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
typedef  int u32 ;
struct rtl_ps_ctl {scalar_t__ support_backdoor; } ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 scalar_t__ rtl_read_byte (struct rtl_priv*,int) ; 
 int rtl_read_dword (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void _rtl88ee_enable_aspm_back_door(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	u8 tmp1byte = 0;
	u32 tmp4byte = 0, count = 0;

	rtl_write_word(rtlpriv, 0x354, 0x8104);
	rtl_write_word(rtlpriv, 0x358, 0x24);

	rtl_write_word(rtlpriv, 0x350, 0x70c);
	rtl_write_byte(rtlpriv, 0x352, 0x2);
	tmp1byte = rtl_read_byte(rtlpriv, 0x352);
	count = 0;
	while (tmp1byte && count < 20) {
		udelay(10);
		tmp1byte = rtl_read_byte(rtlpriv, 0x352);
		count++;
	}
	if (0 == tmp1byte) {
		tmp4byte = rtl_read_dword(rtlpriv, 0x34c);
		rtl_write_dword(rtlpriv, 0x348, tmp4byte|BIT(31));
		rtl_write_word(rtlpriv, 0x350, 0xf70c);
		rtl_write_byte(rtlpriv, 0x352, 0x1);
	}

	tmp1byte = rtl_read_byte(rtlpriv, 0x352);
	count = 0;
	while (tmp1byte && count < 20) {
		udelay(10);
		tmp1byte = rtl_read_byte(rtlpriv, 0x352);
		count++;
	}

	rtl_write_word(rtlpriv, 0x350, 0x718);
	rtl_write_byte(rtlpriv, 0x352, 0x2);
	tmp1byte = rtl_read_byte(rtlpriv, 0x352);
	count = 0;
	while (tmp1byte && count < 20) {
		udelay(10);
		tmp1byte = rtl_read_byte(rtlpriv, 0x352);
		count++;
	}

	if (ppsc->support_backdoor || (0 == tmp1byte)) {
		tmp4byte = rtl_read_dword(rtlpriv, 0x34c);
		rtl_write_dword(rtlpriv, 0x348, tmp4byte|BIT(11)|BIT(12));
		rtl_write_word(rtlpriv, 0x350, 0xf718);
		rtl_write_byte(rtlpriv, 0x352, 0x1);
	}

	tmp1byte = rtl_read_byte(rtlpriv, 0x352);
	count = 0;
	while (tmp1byte && count < 20) {
		udelay(10);
		tmp1byte = rtl_read_byte(rtlpriv, 0x352);
		count++;
	}
}