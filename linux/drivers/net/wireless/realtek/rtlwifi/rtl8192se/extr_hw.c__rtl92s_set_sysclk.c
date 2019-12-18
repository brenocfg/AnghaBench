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
 scalar_t__ SYS_CLKR ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,scalar_t__) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u8 _rtl92s_set_sysclk(struct ieee80211_hw *hw, u8 data)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 waitcnt = 100;
	bool result = false;
	u8 tmp;

	rtl_write_byte(rtlpriv, SYS_CLKR + 1, data);

	/* Wait the MAC synchronized. */
	udelay(400);

	/* Check if it is set ready. */
	tmp = rtl_read_byte(rtlpriv, SYS_CLKR + 1);
	result = ((tmp & BIT(7)) == (data & BIT(7)));

	if ((data & (BIT(6) | BIT(7))) == false) {
		waitcnt = 100;
		tmp = 0;

		while (1) {
			waitcnt--;
			tmp = rtl_read_byte(rtlpriv, SYS_CLKR + 1);

			if ((tmp & BIT(6)))
				break;

			pr_err("wait for BIT(6) return value %x\n", tmp);

			if (waitcnt == 0)
				break;
			udelay(10);
		}

		if (waitcnt == 0)
			result = false;
		else
			result = true;
	}

	return result;
}