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

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_FW ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 scalar_t__ REG_HMETFR ; 
 scalar_t__ REG_SYS_FUNC_EN ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,scalar_t__) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void rtl92d_firmware_selfreset(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 u1b_tmp;
	u8 delay = 100;

	/* Set (REG_HMETFR + 3) to  0x20 is reset 8051 */
	rtl_write_byte(rtlpriv, REG_HMETFR + 3, 0x20);
	u1b_tmp = rtl_read_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	while (u1b_tmp & BIT(2)) {
		delay--;
		if (delay == 0)
			break;
		udelay(50);
		u1b_tmp = rtl_read_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	}
	WARN_ONCE((delay <= 0), "rtl8192de: 8051 reset failed!\n");
	RT_TRACE(rtlpriv, COMP_FW, DBG_DMESG,
		 "=====> 8051 reset success (%d)\n", delay);
}