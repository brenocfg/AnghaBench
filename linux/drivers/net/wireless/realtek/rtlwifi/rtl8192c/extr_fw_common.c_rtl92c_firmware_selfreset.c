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
 scalar_t__ REG_HMETFR ; 
 scalar_t__ REG_SYS_FUNC_EN ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,scalar_t__) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void rtl92c_firmware_selfreset(struct ieee80211_hw *hw)
{
	u8 u1b_tmp;
	u8 delay = 100;
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_write_byte(rtlpriv, REG_HMETFR + 3, 0x20);
	u1b_tmp = rtl_read_byte(rtlpriv, REG_SYS_FUNC_EN + 1);

	while (u1b_tmp & BIT(2)) {
		delay--;
		if (delay == 0) {
			WARN_ONCE(true, "rtl8192c-common: 8051 reset fail.\n");
			break;
		}
		udelay(50);
		u1b_tmp = rtl_read_byte(rtlpriv, REG_SYS_FUNC_EN + 1);
	}
}