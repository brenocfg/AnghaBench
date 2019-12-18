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
struct rtl_hal {scalar_t__ interfaceindex; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_FW ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  FW_MAC0_READY ; 
 int /*<<< orphan*/  FW_MAC1_READY ; 
 int MAC0_READY ; 
 int MAC1_READY ; 
 scalar_t__ POLLING_READY_TIMEOUT_COUNT ; 
 int /*<<< orphan*/  REG_MCUFWDL ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int _rtl92d_fw_init(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u32 counter;

	RT_TRACE(rtlpriv, COMP_FW, DBG_DMESG, "FW already have download\n");
	/* polling for FW ready */
	counter = 0;
	do {
		if (rtlhal->interfaceindex == 0) {
			if (rtl_read_byte(rtlpriv, FW_MAC0_READY) &
			    MAC0_READY) {
				RT_TRACE(rtlpriv, COMP_FW, DBG_DMESG,
					 "Polling FW ready success!! REG_MCUFWDL: 0x%x\n",
					 rtl_read_byte(rtlpriv,
						       FW_MAC0_READY));
				return 0;
			}
			udelay(5);
		} else {
			if (rtl_read_byte(rtlpriv, FW_MAC1_READY) &
			    MAC1_READY) {
				RT_TRACE(rtlpriv, COMP_FW, DBG_DMESG,
					 "Polling FW ready success!! REG_MCUFWDL: 0x%x\n",
					 rtl_read_byte(rtlpriv,
						       FW_MAC1_READY));
				return 0;
			}
			udelay(5);
		}
	} while (counter++ < POLLING_READY_TIMEOUT_COUNT);

	if (rtlhal->interfaceindex == 0) {
		RT_TRACE(rtlpriv, COMP_FW, DBG_DMESG,
			 "Polling FW ready fail!! MAC0 FW init not ready: 0x%x\n",
			 rtl_read_byte(rtlpriv, FW_MAC0_READY));
	} else {
		RT_TRACE(rtlpriv, COMP_FW, DBG_DMESG,
			 "Polling FW ready fail!! MAC1 FW init not ready: 0x%x\n",
			 rtl_read_byte(rtlpriv, FW_MAC1_READY));
	}
	RT_TRACE(rtlpriv, COMP_FW, DBG_DMESG,
		 "Polling FW ready fail!! REG_MCUFWDL:0x%08x\n",
		 rtl_read_dword(rtlpriv, REG_MCUFWDL));
	return -1;
}