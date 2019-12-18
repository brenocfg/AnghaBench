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
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ FWDL_CHKSUM_RPT ; 
 int /*<<< orphan*/  FW_8192C_POLLING_DELAY ; 
 scalar_t__ FW_8192C_POLLING_TIMEOUT_COUNT ; 
 scalar_t__ MCUFWDL_RDY ; 
 int /*<<< orphan*/  REG_MCUFWDL ; 
 scalar_t__ WINTINI_RDY ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  rtl88e_firmware_selfreset (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 scalar_t__ rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _rtl88e_fw_free_to_go(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	int err = -EIO;
	u32 counter = 0;
	u32 value32;

	do {
		value32 = rtl_read_dword(rtlpriv, REG_MCUFWDL);
	} while ((counter++ < FW_8192C_POLLING_TIMEOUT_COUNT) &&
		 (!(value32 & FWDL_CHKSUM_RPT)));

	if (counter >= FW_8192C_POLLING_TIMEOUT_COUNT) {
		pr_err("chksum report fail! REG_MCUFWDL:0x%08x .\n",
		       value32);
		goto exit;
	}
	value32 = rtl_read_dword(rtlpriv, REG_MCUFWDL);
	value32 |= MCUFWDL_RDY;
	value32 &= ~WINTINI_RDY;
	rtl_write_dword(rtlpriv, REG_MCUFWDL, value32);

	rtl88e_firmware_selfreset(hw);
	counter = 0;

	do {
		value32 = rtl_read_dword(rtlpriv, REG_MCUFWDL);
		if (value32 & WINTINI_RDY)
			return 0;

		udelay(FW_8192C_POLLING_DELAY);

	} while (counter++ < FW_8192C_POLLING_TIMEOUT_COUNT);

	pr_err("Polling FW ready fail!! REG_MCUFWDL:0x%08x .\n",
	       value32);

exit:
	return err;
}