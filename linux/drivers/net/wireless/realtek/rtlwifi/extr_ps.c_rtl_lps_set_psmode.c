#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_6__ {scalar_t__ opp_ps; } ;
struct rtl_ps_ctl {scalar_t__ dot11_psmode; int smart_ps; int /*<<< orphan*/  fwctrl_psmode; int /*<<< orphan*/  pwr_mode; TYPE_1__ p2p_ps_info; scalar_t__ report_linked; scalar_t__ fwctrl_lps; } ;
struct TYPE_8__ {TYPE_2__* btc_ops; } ;
struct rtl_priv {TYPE_5__* cfg; TYPE_3__ btcoexist; } ;
struct rtl_mac {scalar_t__ opmode; scalar_t__ link_state; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_10__ {TYPE_4__* ops; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,scalar_t__*) ;scalar_t__ (* get_btc_status ) () ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* btc_lps_notify ) (struct rtl_priv*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RF ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 scalar_t__ EACTIVE ; 
 int /*<<< orphan*/  FW_PS_ACTIVE_MODE ; 
 int /*<<< orphan*/  HW_VAR_FW_LPS_ACTION ; 
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  P2P_PS_ENABLE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ rtl_get_fwlps_doze (struct ieee80211_hw*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 int /*<<< orphan*/  rtl_p2p_ps_cmd (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub2 () ; 
 int /*<<< orphan*/  stub3 (struct rtl_priv*,scalar_t__) ; 
 scalar_t__ stub4 () ; 
 int /*<<< orphan*/  stub5 (struct rtl_priv*,scalar_t__) ; 
 int /*<<< orphan*/  stub6 (struct ieee80211_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 

void rtl_lps_set_psmode(struct ieee80211_hw *hw, u8 rt_psmode)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool enter_fwlps;

	if (mac->opmode == NL80211_IFTYPE_ADHOC)
		return;

	if (mac->link_state != MAC80211_LINKED)
		return;

	if (ppsc->dot11_psmode == rt_psmode && rt_psmode == EACTIVE)
		return;

	/* Update power save mode configured. */
	ppsc->dot11_psmode = rt_psmode;

	/*
	 *<FW control LPS>
	 *1. Enter PS mode
	 *   Set RPWM to Fw to turn RF off and send H2C fw_pwrmode
	 *   cmd to set Fw into PS mode.
	 *2. Leave PS mode
	 *   Send H2C fw_pwrmode cmd to Fw to set Fw into Active
	 *   mode and set RPWM to turn RF on.
	 */

	if ((ppsc->fwctrl_lps) && ppsc->report_linked) {
		if (ppsc->dot11_psmode == EACTIVE) {
			RT_TRACE(rtlpriv, COMP_RF, DBG_DMESG,
				 "FW LPS leave ps_mode:%x\n",
				  FW_PS_ACTIVE_MODE);
			enter_fwlps = false;
			ppsc->pwr_mode = FW_PS_ACTIVE_MODE;
			ppsc->smart_ps = 0;
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_FW_LPS_ACTION,
						      (u8 *)(&enter_fwlps));
			if (ppsc->p2p_ps_info.opp_ps)
				rtl_p2p_ps_cmd(hw , P2P_PS_ENABLE);

			if (rtlpriv->cfg->ops->get_btc_status())
				rtlpriv->btcoexist.btc_ops->btc_lps_notify(rtlpriv, rt_psmode);
		} else {
			if (rtl_get_fwlps_doze(hw)) {
				RT_TRACE(rtlpriv, COMP_RF, DBG_DMESG,
					 "FW LPS enter ps_mode:%x\n",
					 ppsc->fwctrl_psmode);
				if (rtlpriv->cfg->ops->get_btc_status())
					rtlpriv->btcoexist.btc_ops->btc_lps_notify(rtlpriv, rt_psmode);
				enter_fwlps = true;
				ppsc->pwr_mode = ppsc->fwctrl_psmode;
				ppsc->smart_ps = 2;
				rtlpriv->cfg->ops->set_hw_reg(hw,
							HW_VAR_FW_LPS_ACTION,
							(u8 *)(&enter_fwlps));

			} else {
				/* Reset the power save related parameters. */
				ppsc->dot11_psmode = EACTIVE;
			}
		}
	}
}