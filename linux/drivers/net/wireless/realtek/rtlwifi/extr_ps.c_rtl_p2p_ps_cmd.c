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
typedef  int u8 ;
struct rtl_ps_ctl {int smart_ps; int pwr_mode; int /*<<< orphan*/  fw_current_inpsmode; } ;
struct rtl_p2p_ps_info {int p2p_ps_state; int /*<<< orphan*/  noa_num; int /*<<< orphan*/ * noa_start_time; int /*<<< orphan*/ * noa_interval; int /*<<< orphan*/  noa_index; int /*<<< orphan*/ * noa_duration; int /*<<< orphan*/ * noa_count_type; int /*<<< orphan*/  opp_ps; int /*<<< orphan*/  ctwindow; int /*<<< orphan*/  p2p_ps_mode; } ;
struct TYPE_4__ {struct rtl_p2p_ps_info p2p_ps_info; } ;
struct rtl_priv {TYPE_3__* cfg; TYPE_1__ psc; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_FW ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  HW_VAR_H2C_FW_P2P_PS_OFFLOAD ; 
 int /*<<< orphan*/  HW_VAR_H2C_FW_PWRMODE ; 
#define  P2P_PS_ALLSTASLEEP 132 
#define  P2P_PS_DISABLE 131 
#define  P2P_PS_ENABLE 130 
 int /*<<< orphan*/  P2P_PS_NONE ; 
#define  P2P_PS_SCAN 129 
#define  P2P_PS_SCAN_DONE 128 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 

void rtl_p2p_ps_cmd(struct ieee80211_hw *hw , u8 p2p_ps_state)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *rtlps = rtl_psc(rtl_priv(hw));
	struct rtl_p2p_ps_info  *p2pinfo = &(rtlpriv->psc.p2p_ps_info);

	RT_TRACE(rtlpriv, COMP_FW, DBG_LOUD, " p2p state %x\n" , p2p_ps_state);
	switch (p2p_ps_state) {
	case P2P_PS_DISABLE:
		p2pinfo->p2p_ps_state = p2p_ps_state;
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_H2C_FW_P2P_PS_OFFLOAD,
					      &p2p_ps_state);
		p2pinfo->noa_index = 0;
		p2pinfo->ctwindow = 0;
		p2pinfo->opp_ps = 0;
		p2pinfo->noa_num = 0;
		p2pinfo->p2p_ps_mode = P2P_PS_NONE;
		if (rtlps->fw_current_inpsmode) {
			if (rtlps->smart_ps == 0) {
				rtlps->smart_ps = 2;
				rtlpriv->cfg->ops->set_hw_reg(hw,
					 HW_VAR_H2C_FW_PWRMODE,
					 &rtlps->pwr_mode);
			}

		}
		break;
	case P2P_PS_ENABLE:
		if (p2pinfo->p2p_ps_mode > P2P_PS_NONE) {
			p2pinfo->p2p_ps_state = p2p_ps_state;

			if (p2pinfo->ctwindow > 0) {
				if (rtlps->smart_ps != 0) {
					rtlps->smart_ps = 0;
					rtlpriv->cfg->ops->set_hw_reg(hw,
						 HW_VAR_H2C_FW_PWRMODE,
						 &rtlps->pwr_mode);
				}
			}
			rtlpriv->cfg->ops->set_hw_reg(hw,
				 HW_VAR_H2C_FW_P2P_PS_OFFLOAD,
				 &p2p_ps_state);

		}
		break;
	case P2P_PS_SCAN:
	case P2P_PS_SCAN_DONE:
	case P2P_PS_ALLSTASLEEP:
		if (p2pinfo->p2p_ps_mode > P2P_PS_NONE) {
			p2pinfo->p2p_ps_state = p2p_ps_state;
			rtlpriv->cfg->ops->set_hw_reg(hw,
				 HW_VAR_H2C_FW_P2P_PS_OFFLOAD,
				 &p2p_ps_state);
		}
		break;
	default:
		break;
	}
	RT_TRACE(rtlpriv, COMP_FW, DBG_LOUD,
		 "ctwindow %x oppps %x\n",
		 p2pinfo->ctwindow , p2pinfo->opp_ps);
	RT_TRACE(rtlpriv, COMP_FW, DBG_LOUD,
		 "count %x duration %x index %x interval %x start time %x noa num %x\n",
		 p2pinfo->noa_count_type[0],
		 p2pinfo->noa_duration[0],
		 p2pinfo->noa_index,
		 p2pinfo->noa_interval[0],
		 p2pinfo->noa_start_time[0],
		 p2pinfo->noa_num);
	RT_TRACE(rtlpriv, COMP_FW, DBG_LOUD, "end\n");
}