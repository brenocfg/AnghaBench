#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct rtl_ps_ctl {int rfchange_inprogress; int hwradiooff; int reg_rfps_level; scalar_t__ swrf_processing; } ;
struct TYPE_2__ {int /*<<< orphan*/  rf_ps_lock; } ;
struct rtl_priv {TYPE_1__ locks; } ;
struct rtl_pci {scalar_t__ being_init_adapter; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum rf_pwrstate { ____Placeholder_rf_pwrstate } rf_pwrstate ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_RF ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int ERFOFF ; 
 int ERFON ; 
 int /*<<< orphan*/  REG_GPIO_IO_SEL ; 
 int /*<<< orphan*/  REG_MAC_PINMUX_CFG ; 
 int RT_RF_OFF_LEVL_HALT_NIC ; 
 int /*<<< orphan*/  RT_SET_PS_LEVEL (struct rtl_ps_ctl*,int) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool rtl92de_gpio_radio_on_off_checking(struct ieee80211_hw *hw, u8 *valid)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	enum rf_pwrstate e_rfpowerstate_toset;
	u8 u1tmp;
	bool actuallyset = false;
	unsigned long flag;

	if (rtlpci->being_init_adapter)
		return false;
	if (ppsc->swrf_processing)
		return false;
	spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flag);
	if (ppsc->rfchange_inprogress) {
		spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flag);
		return false;
	} else {
		ppsc->rfchange_inprogress = true;
		spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flag);
	}
	rtl_write_byte(rtlpriv, REG_MAC_PINMUX_CFG, rtl_read_byte(rtlpriv,
			  REG_MAC_PINMUX_CFG) & ~(BIT(3)));
	u1tmp = rtl_read_byte(rtlpriv, REG_GPIO_IO_SEL);
	e_rfpowerstate_toset = (u1tmp & BIT(3)) ? ERFON : ERFOFF;
	if (ppsc->hwradiooff && (e_rfpowerstate_toset == ERFON)) {
		RT_TRACE(rtlpriv, COMP_RF, DBG_DMESG,
			 "GPIOChangeRF  - HW Radio ON, RF ON\n");
		e_rfpowerstate_toset = ERFON;
		ppsc->hwradiooff = false;
		actuallyset = true;
	} else if (!ppsc->hwradiooff && (e_rfpowerstate_toset == ERFOFF)) {
		RT_TRACE(rtlpriv, COMP_RF, DBG_DMESG,
			 "GPIOChangeRF  - HW Radio OFF, RF OFF\n");
		e_rfpowerstate_toset = ERFOFF;
		ppsc->hwradiooff = true;
		actuallyset = true;
	}
	if (actuallyset) {
		spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flag);
		ppsc->rfchange_inprogress = false;
		spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flag);
	} else {
		if (ppsc->reg_rfps_level & RT_RF_OFF_LEVL_HALT_NIC)
			RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);
		spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flag);
		ppsc->rfchange_inprogress = false;
		spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flag);
	}
	*valid = 1;
	return !ppsc->hwradiooff;
}