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
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMDR ; 
 int /*<<< orphan*/  LDOV12D_CTRL ; 
 int /*<<< orphan*/  PHY_CCA ; 
 int /*<<< orphan*/  SPS1_CTRL ; 
 int /*<<< orphan*/  TXPAUSE ; 
 int /*<<< orphan*/  rtl8192se_gpiobit3_cfg_inputmode (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void _rtl92se_phy_set_rf_sleep(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 u1btmp;

	u1btmp = rtl_read_byte(rtlpriv, LDOV12D_CTRL);
	u1btmp |= BIT(0);

	rtl_write_byte(rtlpriv, LDOV12D_CTRL, u1btmp);
	rtl_write_byte(rtlpriv, SPS1_CTRL, 0x0);
	rtl_write_byte(rtlpriv, TXPAUSE, 0xFF);
	rtl_write_word(rtlpriv, CMDR, 0x57FC);
	udelay(100);

	rtl_write_word(rtlpriv, CMDR, 0x77FC);
	rtl_write_byte(rtlpriv, PHY_CCA, 0x0);
	udelay(10);

	rtl_write_word(rtlpriv, CMDR, 0x37FC);
	udelay(10);

	rtl_write_word(rtlpriv, CMDR, 0x77FC);
	udelay(10);

	rtl_write_word(rtlpriv, CMDR, 0x57FC);

	/* we should chnge GPIO to input mode
	 * this will drop away current about 25mA*/
	rtl8192se_gpiobit3_cfg_inputmode(hw);
}