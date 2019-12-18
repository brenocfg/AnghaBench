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
typedef  int u32 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_FW ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int EIO ; 
 int FWDL_CHKSUM_RPT ; 
 int /*<<< orphan*/  FW_8192C_POLLING_DELAY ; 
 int MCUFWDL_RDY ; 
 int /*<<< orphan*/  REG_MCUFWDL ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int WINTINI_RDY ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  rtl8723be_firmware_selfreset (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

int rtl8723_fw_free_to_go(struct ieee80211_hw *hw, bool is_8723be,
			  int max_count)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	int err = -EIO;
	u32 counter = 0;
	u32 value32;

	do {
		value32 = rtl_read_dword(rtlpriv, REG_MCUFWDL);
	} while ((counter++ < max_count) &&
		 (!(value32 & FWDL_CHKSUM_RPT)));

	if (counter >= max_count) {
		pr_err("chksum report fail ! REG_MCUFWDL:0x%08x .\n",
		       value32);
		goto exit;
	}
	value32 = rtl_read_dword(rtlpriv, REG_MCUFWDL) | MCUFWDL_RDY;
	value32 &= ~WINTINI_RDY;
	rtl_write_dword(rtlpriv, REG_MCUFWDL, value32);

	if (is_8723be)
		rtl8723be_firmware_selfreset(hw);
	counter = 0;

	do {
		value32 = rtl_read_dword(rtlpriv, REG_MCUFWDL);
		if (value32 & WINTINI_RDY) {
			RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE,
				 "Polling FW ready success!! REG_MCUFWDL:0x%08x .\n",
				 value32);
			err = 0;
			goto exit;
		}

		mdelay(FW_8192C_POLLING_DELAY);

	} while (counter++ < max_count);

	pr_err("Polling FW ready fail!! REG_MCUFWDL:0x%08x .\n",
	       value32);

exit:
	return err;
}