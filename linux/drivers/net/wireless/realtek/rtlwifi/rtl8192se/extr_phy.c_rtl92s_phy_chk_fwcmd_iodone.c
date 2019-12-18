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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WFM5 ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 scalar_t__ rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void rtl92s_phy_chk_fwcmd_iodone(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u16 pollingcnt = 10000;
	u32 tmpvalue;

	/* Make sure that CMD IO has be accepted by FW. */
	do {
		udelay(10);

		tmpvalue = rtl_read_dword(rtlpriv, WFM5);
		if (tmpvalue == 0)
			break;
	} while (--pollingcnt);

	if (pollingcnt == 0)
		pr_err("Set FW Cmd fail!!\n");
}