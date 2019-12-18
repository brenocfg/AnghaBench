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
struct dig_t {scalar_t__ presta_cstate; scalar_t__ cursta_cstate; int cur_igvalue; scalar_t__ pre_igvalue; int /*<<< orphan*/  back_val; int /*<<< orphan*/  dig_ext_port_stage; scalar_t__ rssi_val_min; } ;
struct rtl_priv {struct dig_t dm_digtable; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_DIG ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  DIG_EXT_PORT_STAGE_MAX ; 
 scalar_t__ DIG_STA_BEFORE_CONNECT ; 
 scalar_t__ DIG_STA_CONNECT ; 
 scalar_t__ DIG_STA_DISCONNECT ; 
 int /*<<< orphan*/  DM_DIG_BACKOFF_DEFAULT ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ rtl8723e_dm_initial_gain_min_pwdb (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723e_dm_write_dig (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92c_dm_ctrl_initgain_by_rssi (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8723e_dm_initial_gain_sta(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *dm_digtable = &rtlpriv->dm_digtable;

	RT_TRACE(rtlpriv, COMP_DIG, DBG_TRACE,
		 "presta_cstate = %x, cursta_cstate = %x\n",
		  dm_digtable->presta_cstate,
		  dm_digtable->cursta_cstate);

	if (dm_digtable->presta_cstate == dm_digtable->cursta_cstate ||
	    dm_digtable->cursta_cstate == DIG_STA_BEFORE_CONNECT ||
	    dm_digtable->cursta_cstate == DIG_STA_CONNECT) {
		if (dm_digtable->cursta_cstate != DIG_STA_DISCONNECT) {
			dm_digtable->rssi_val_min =
			    rtl8723e_dm_initial_gain_min_pwdb(hw);
			rtl92c_dm_ctrl_initgain_by_rssi(hw);
		}
	} else {
		dm_digtable->rssi_val_min = 0;
		dm_digtable->dig_ext_port_stage = DIG_EXT_PORT_STAGE_MAX;
		dm_digtable->back_val = DM_DIG_BACKOFF_DEFAULT;
		dm_digtable->cur_igvalue = 0x20;
		dm_digtable->pre_igvalue = 0;
		rtl8723e_dm_write_dig(hw);
	}
}