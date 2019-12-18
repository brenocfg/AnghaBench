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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct rtl_ps_ctl {int rfchange_inprogress; int rfpwr_state; int hwradiooff; int /*<<< orphan*/  rfoff_reason; } ;
struct TYPE_6__ {int /*<<< orphan*/  rf_ps_lock; } ;
struct rtl_priv {TYPE_3__ locks; TYPE_2__* cfg; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum rf_pwrstate { ____Placeholder_rf_pwrstate } rf_pwrstate ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_rf_power_state ) (struct ieee80211_hw*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  DBG_WARNING ; 
#define  ERFOFF 130 
#define  ERFON 129 
#define  ERFSLEEP 128 
 int /*<<< orphan*/  RF_CHANGE_BY_HW ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int) ; 

__attribute__((used)) static bool rtl_ps_set_rf_state(struct ieee80211_hw *hw,
				enum rf_pwrstate state_toset,
				u32 changesource)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	enum rf_pwrstate rtstate;
	bool actionallowed = false;
	u16 rfwait_cnt = 0;

	/*Only one thread can change
	 *the RF state at one time, and others
	 *should wait to be executed.
	 */
	while (true) {
		spin_lock(&rtlpriv->locks.rf_ps_lock);
		if (ppsc->rfchange_inprogress) {
			spin_unlock(&rtlpriv->locks.rf_ps_lock);

			RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
				 "RF Change in progress! Wait to set..state_toset(%d).\n",
				  state_toset);

			/* Set RF after the previous action is done.  */
			while (ppsc->rfchange_inprogress) {
				rfwait_cnt++;
				mdelay(1);
				/*Wait too long, return false to avoid
				 *to be stuck here.
				 */
				if (rfwait_cnt > 100)
					return false;
			}
		} else {
			ppsc->rfchange_inprogress = true;
			spin_unlock(&rtlpriv->locks.rf_ps_lock);
			break;
		}
	}

	rtstate = ppsc->rfpwr_state;

	switch (state_toset) {
	case ERFON:
		ppsc->rfoff_reason &= (~changesource);

		if ((changesource == RF_CHANGE_BY_HW) &&
		    (ppsc->hwradiooff)) {
			ppsc->hwradiooff = false;
		}

		if (!ppsc->rfoff_reason) {
			ppsc->rfoff_reason = 0;
			actionallowed = true;
		}

		break;

	case ERFOFF:

		if ((changesource == RF_CHANGE_BY_HW) && !ppsc->hwradiooff) {
			ppsc->hwradiooff = true;
		}

		ppsc->rfoff_reason |= changesource;
		actionallowed = true;
		break;

	case ERFSLEEP:
		ppsc->rfoff_reason |= changesource;
		actionallowed = true;
		break;

	default:
		pr_err("switch case %#x not processed\n", state_toset);
		break;
	}

	if (actionallowed)
		rtlpriv->cfg->ops->set_rf_power_state(hw, state_toset);

	spin_lock(&rtlpriv->locks.rf_ps_lock);
	ppsc->rfchange_inprogress = false;
	spin_unlock(&rtlpriv->locks.rf_ps_lock);

	return actionallowed;
}