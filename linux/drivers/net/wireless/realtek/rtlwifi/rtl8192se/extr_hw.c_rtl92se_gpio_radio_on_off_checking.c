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
struct rtl_pci {int up_first_time; scalar_t__ being_init_adapter; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum rf_pwrstate { ____Placeholder_rf_pwrstate } rf_pwrstate ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RF ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int ERFOFF ; 
 int ERFON ; 
 scalar_t__ RT_IN_PS_LEVEL (struct rtl_ps_ctl*,int) ; 
 int RT_RF_OFF_LEVL_HALT_NIC ; 
 int /*<<< orphan*/  RT_SET_PS_LEVEL (struct rtl_ps_ctl*,int) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _rtl92s_phy_set_rfhalt (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl92se_power_domain_init (struct ieee80211_hw*) ; 
 int _rtl92se_rf_onoff_detect (struct ieee80211_hw*) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool rtl92se_gpio_radio_on_off_checking(struct ieee80211_hw *hw, u8 *valid)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	enum rf_pwrstate rfpwr_toset /*, cur_rfstate */;
	unsigned long flag = 0;
	bool actuallyset = false;
	bool turnonbypowerdomain = false;

	/* just 8191se can check gpio before firstup, 92c/92d have fixed it */
	if ((rtlpci->up_first_time == 1) || (rtlpci->being_init_adapter))
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

	/* cur_rfstate = ppsc->rfpwr_state;*/

	/* because after _rtl92s_phy_set_rfhalt, all power
	 * closed, so we must open some power for GPIO check,
	 * or we will always check GPIO RFOFF here,
	 * And we should close power after GPIO check */
	if (RT_IN_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC)) {
		_rtl92se_power_domain_init(hw);
		turnonbypowerdomain = true;
	}

	rfpwr_toset = _rtl92se_rf_onoff_detect(hw);

	if ((ppsc->hwradiooff) && (rfpwr_toset == ERFON)) {
		RT_TRACE(rtlpriv, COMP_RF, DBG_DMESG,
			 "RFKILL-HW Radio ON, RF ON\n");

		rfpwr_toset = ERFON;
		ppsc->hwradiooff = false;
		actuallyset = true;
	} else if ((!ppsc->hwradiooff) && (rfpwr_toset == ERFOFF)) {
		RT_TRACE(rtlpriv, COMP_RF,
			 DBG_DMESG, "RFKILL-HW Radio OFF, RF OFF\n");

		rfpwr_toset = ERFOFF;
		ppsc->hwradiooff = true;
		actuallyset = true;
	}

	if (actuallyset) {
		spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flag);
		ppsc->rfchange_inprogress = false;
		spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flag);

	/* this not include ifconfig wlan0 down case */
	/* } else if (rfpwr_toset == ERFOFF || cur_rfstate == ERFOFF) { */
	} else {
		/* because power_domain_init may be happen when
		 * _rtl92s_phy_set_rfhalt, this will open some powers
		 * and cause current increasing about 40 mA for ips,
		 * rfoff and ifconfig down, so we set
		 * _rtl92s_phy_set_rfhalt again here */
		if (ppsc->reg_rfps_level & RT_RF_OFF_LEVL_HALT_NIC &&
			turnonbypowerdomain) {
			_rtl92s_phy_set_rfhalt(hw);
			RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);
		}

		spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flag);
		ppsc->rfchange_inprogress = false;
		spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flag);
	}

	*valid = 1;
	return !ppsc->hwradiooff;

}