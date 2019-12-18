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
struct rtl_hal {scalar_t__ macphymode; scalar_t__ interfaceindex; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int MAC0_ON ; 
 int MAC1_ON ; 
 int /*<<< orphan*/  REG_MAC0 ; 
 int /*<<< orphan*/  REG_MAC1 ; 
 int /*<<< orphan*/  REG_POWER_OFF_IN_PROCESS ; 
 scalar_t__ SINGLEMAC_SINGLEPHY ; 
 int /*<<< orphan*/  globalmutex_power ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool rtl92d_phy_check_poweroff(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 u1btmp;
	unsigned long flags;

	if (rtlhal->macphymode == SINGLEMAC_SINGLEPHY) {
		u1btmp = rtl_read_byte(rtlpriv, REG_MAC0);
		rtl_write_byte(rtlpriv, REG_MAC0, u1btmp & (~MAC0_ON));
		return true;
	}
	spin_lock_irqsave(&globalmutex_power, flags);
	if (rtlhal->interfaceindex == 0) {
		u1btmp = rtl_read_byte(rtlpriv, REG_MAC0);
		rtl_write_byte(rtlpriv, REG_MAC0, u1btmp & (~MAC0_ON));
		u1btmp = rtl_read_byte(rtlpriv, REG_MAC1);
		u1btmp &= MAC1_ON;
	} else {
		u1btmp = rtl_read_byte(rtlpriv, REG_MAC1);
		rtl_write_byte(rtlpriv, REG_MAC1, u1btmp & (~MAC1_ON));
		u1btmp = rtl_read_byte(rtlpriv, REG_MAC0);
		u1btmp &= MAC0_ON;
	}
	if (u1btmp) {
		spin_unlock_irqrestore(&globalmutex_power, flags);
		return false;
	}
	u1btmp = rtl_read_byte(rtlpriv, REG_POWER_OFF_IN_PROCESS);
	u1btmp |= BIT(7);
	rtl_write_byte(rtlpriv, REG_POWER_OFF_IN_PROCESS, u1btmp);
	spin_unlock_irqrestore(&globalmutex_power, flags);
	return true;
}