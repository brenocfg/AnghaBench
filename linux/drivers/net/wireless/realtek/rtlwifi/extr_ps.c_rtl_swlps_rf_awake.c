#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rtl_ps_ctl {int reg_rfps_level; } ;
struct TYPE_5__ {int /*<<< orphan*/  lps_mutex; } ;
struct TYPE_6__ {int /*<<< orphan*/  swctrl_lps; } ;
struct rtl_priv {TYPE_2__ locks; TYPE_1__* intf_ops; TYPE_3__ psc; } ;
struct rtl_mac {scalar_t__ link_state; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disable_aspm ) (struct ieee80211_hw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ERFON ; 
 scalar_t__ MAC80211_LINKED ; 
 int /*<<< orphan*/  RF_CHANGE_BY_PS ; 
 int /*<<< orphan*/  RT_CLEAR_PS_LEVEL (struct rtl_ps_ctl*,int /*<<< orphan*/ ) ; 
 scalar_t__ RT_IN_PS_LEVEL (struct rtl_ps_ctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_PS_LEVEL_ASPM ; 
 int RT_RF_LPS_LEVEL_ASPM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_ps_set_rf_state (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*) ; 

void rtl_swlps_rf_awake(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));

	if (!rtlpriv->psc.swctrl_lps)
		return;
	if (mac->link_state != MAC80211_LINKED)
		return;

	if (ppsc->reg_rfps_level & RT_RF_LPS_LEVEL_ASPM &&
	    RT_IN_PS_LEVEL(ppsc, RT_PS_LEVEL_ASPM)) {
		rtlpriv->intf_ops->disable_aspm(hw);
		RT_CLEAR_PS_LEVEL(ppsc, RT_PS_LEVEL_ASPM);
	}

	mutex_lock(&rtlpriv->locks.lps_mutex);
	rtl_ps_set_rf_state(hw, ERFON, RF_CHANGE_BY_PS);
	mutex_unlock(&rtlpriv->locks.lps_mutex);
}