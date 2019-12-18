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
 scalar_t__ REG_BACKDOOR_DBI_DATA ; 
 int /*<<< orphan*/  REG_BACKDOOR_DBI_RDATA ; 
 int /*<<< orphan*/  REG_BACKDOOR_DBI_WDATA ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 scalar_t__ rtl_read_byte (struct rtl_priv*,scalar_t__) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void _rtl92ee_enable_aspm_back_door(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	u32 tmp32 = 0, count = 0;
	u8 tmp8 = 0;

	rtl_write_word(rtlpriv, REG_BACKDOOR_DBI_DATA, 0x78);
	rtl_write_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2, 0x2);
	tmp8 = rtl_read_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2);
	count = 0;
	while (tmp8 && count < 20) {
		udelay(10);
		tmp8 = rtl_read_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2);
		count++;
	}

	if (0 == tmp8) {
		tmp32 = rtl_read_dword(rtlpriv, REG_BACKDOOR_DBI_RDATA);
		if ((tmp32 & 0xff00) != 0x2000) {
			tmp32 &= 0xffff00ff;
			rtl_write_dword(rtlpriv, REG_BACKDOOR_DBI_WDATA,
					tmp32 | BIT(13));
			rtl_write_word(rtlpriv, REG_BACKDOOR_DBI_DATA, 0xf078);
			rtl_write_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2, 0x1);

			tmp8 = rtl_read_byte(rtlpriv,
					     REG_BACKDOOR_DBI_DATA + 2);
			count = 0;
			while (tmp8 && count < 20) {
				udelay(10);
				tmp8 = rtl_read_byte(rtlpriv,
						     REG_BACKDOOR_DBI_DATA + 2);
				count++;
			}
		}
	}

	rtl_write_word(rtlpriv, REG_BACKDOOR_DBI_DATA, 0x70c);
	rtl_write_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2, 0x2);
	tmp8 = rtl_read_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2);
	count = 0;
	while (tmp8 && count < 20) {
		udelay(10);
		tmp8 = rtl_read_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2);
		count++;
	}
	if (0 == tmp8) {
		tmp32 = rtl_read_dword(rtlpriv, REG_BACKDOOR_DBI_RDATA);
		rtl_write_dword(rtlpriv, REG_BACKDOOR_DBI_WDATA,
				tmp32 | BIT(31));
		rtl_write_word(rtlpriv, REG_BACKDOOR_DBI_DATA, 0xf70c);
		rtl_write_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2, 0x1);
	}

	tmp8 = rtl_read_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2);
	count = 0;
	while (tmp8 && count < 20) {
		udelay(10);
		tmp8 = rtl_read_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2);
		count++;
	}

	rtl_write_word(rtlpriv, REG_BACKDOOR_DBI_DATA, 0x718);
	rtl_write_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2, 0x2);
	tmp8 = rtl_read_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2);
	count = 0;
	while (tmp8 && count < 20) {
		udelay(10);
		tmp8 = rtl_read_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2);
		count++;
	}
	if (ppsc->support_backdoor || (0 == tmp8)) {
		tmp32 = rtl_read_dword(rtlpriv, REG_BACKDOOR_DBI_RDATA);
		rtl_write_dword(rtlpriv, REG_BACKDOOR_DBI_WDATA,
				tmp32 | BIT(11) | BIT(12));
		rtl_write_word(rtlpriv, REG_BACKDOOR_DBI_DATA, 0xf718);
		rtl_write_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2, 0x1);
	}
	tmp8 = rtl_read_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2);
	count = 0;
	while (tmp8 && count < 20) {
		udelay(10);
		tmp8 = rtl_read_byte(rtlpriv, REG_BACKDOOR_DBI_DATA + 2);
		count++;
	}
}