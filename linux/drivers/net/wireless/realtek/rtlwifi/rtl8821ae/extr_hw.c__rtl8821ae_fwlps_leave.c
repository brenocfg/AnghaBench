#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct rtl_ps_ctl {scalar_t__ low_power_enable; } ;
struct rtl_priv {TYPE_2__* cfg; } ;
struct rtl_hal {int allow_sw_to_change_hwclc; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int FW_PS_ACK ; 
 int FW_PS_ACTIVE_MODE ; 
 int FW_PS_STATE_ALL_ON_8821AE ; 
 int /*<<< orphan*/  HW_VAR_FW_PSMODE_STATUS ; 
 int /*<<< orphan*/  HW_VAR_H2C_FW_PWRMODE ; 
 int /*<<< orphan*/  HW_VAR_SET_RPWM ; 
 int /*<<< orphan*/  _rtl8821ae_set_fw_clock_on (struct ieee80211_hw*,int,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void _rtl8821ae_fwlps_leave(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool fw_current_inps = false;
	u8 rpwm_val = 0, fw_pwrmode = FW_PS_ACTIVE_MODE;

	if (ppsc->low_power_enable) {
		rpwm_val = (FW_PS_STATE_ALL_ON_8821AE|FW_PS_ACK);/* RF on */
		_rtl8821ae_set_fw_clock_on(hw, rpwm_val, false);
		rtlhal->allow_sw_to_change_hwclc = false;
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_H2C_FW_PWRMODE,
				(u8 *)(&fw_pwrmode));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
				(u8 *)(&fw_current_inps));
	} else {
		rpwm_val = FW_PS_STATE_ALL_ON_8821AE;	/* RF on */
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SET_RPWM,
				(u8 *)(&rpwm_val));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_H2C_FW_PWRMODE,
				(u8 *)(&fw_pwrmode));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
				(u8 *)(&fw_current_inps));
	}
}