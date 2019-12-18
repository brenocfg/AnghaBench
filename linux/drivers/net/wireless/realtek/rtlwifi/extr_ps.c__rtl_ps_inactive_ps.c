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
struct rtl_ps_ctl {int swrf_processing; scalar_t__ inactive_pwrstate; int reg_rfps_level; } ;
struct rtl_priv {TYPE_1__* intf_ops; } ;
struct rtl_hal {scalar_t__ interface; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_aspm ) (struct ieee80211_hw*) ;int /*<<< orphan*/  (* disable_aspm ) (struct ieee80211_hw*) ;} ;

/* Variables and functions */
 scalar_t__ ERFOFF ; 
 scalar_t__ ERFON ; 
 scalar_t__ INTF_PCI ; 
 int /*<<< orphan*/  RF_CHANGE_BY_IPS ; 
 int /*<<< orphan*/  RT_CLEAR_PS_LEVEL (struct rtl_ps_ctl*,int /*<<< orphan*/ ) ; 
 scalar_t__ RT_IN_PS_LEVEL (struct rtl_ps_ctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_PS_LEVEL_ASPM ; 
 int RT_RF_OFF_LEVL_ASPM ; 
 int /*<<< orphan*/  RT_SET_PS_LEVEL (struct rtl_ps_ctl*,int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_ps_set_rf_state (struct ieee80211_hw*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl_ps_inactive_ps(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	ppsc->swrf_processing = true;

	if (ppsc->inactive_pwrstate == ERFON &&
	    rtlhal->interface == INTF_PCI) {
		if ((ppsc->reg_rfps_level & RT_RF_OFF_LEVL_ASPM) &&
		    RT_IN_PS_LEVEL(ppsc, RT_PS_LEVEL_ASPM) &&
		    rtlhal->interface == INTF_PCI) {
			rtlpriv->intf_ops->disable_aspm(hw);
			RT_CLEAR_PS_LEVEL(ppsc, RT_PS_LEVEL_ASPM);
		}
	}

	rtl_ps_set_rf_state(hw, ppsc->inactive_pwrstate,
			    RF_CHANGE_BY_IPS);

	if (ppsc->inactive_pwrstate == ERFOFF &&
	    rtlhal->interface == INTF_PCI) {
		if (ppsc->reg_rfps_level & RT_RF_OFF_LEVL_ASPM &&
		    !RT_IN_PS_LEVEL(ppsc, RT_PS_LEVEL_ASPM)) {
			rtlpriv->intf_ops->enable_aspm(hw);
			RT_SET_PS_LEVEL(ppsc, RT_PS_LEVEL_ASPM);
		}
	}

	ppsc->swrf_processing = false;
}