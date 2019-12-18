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
struct mwifiex_wmm_ac_status {int /*<<< orphan*/  flow_required; int /*<<< orphan*/  disabled; } ;
struct TYPE_2__ {struct mwifiex_wmm_ac_status* ac_status; } ;
struct mwifiex_private {TYPE_1__ wmm; } ;
typedef  enum mwifiex_wmm_ac_e { ____Placeholder_mwifiex_wmm_ac_e } mwifiex_wmm_ac_e ;

/* Variables and functions */
 int WMM_AC_BK ; 

__attribute__((used)) static enum mwifiex_wmm_ac_e
mwifiex_wmm_eval_downgrade_ac(struct mwifiex_private *priv,
			      enum mwifiex_wmm_ac_e eval_ac)
{
	int down_ac;
	enum mwifiex_wmm_ac_e ret_ac;
	struct mwifiex_wmm_ac_status *ac_status;

	ac_status = &priv->wmm.ac_status[eval_ac];

	if (!ac_status->disabled)
		/* Okay to use this AC, its enabled */
		return eval_ac;

	/* Setup a default return value of the lowest priority */
	ret_ac = WMM_AC_BK;

	/*
	 *  Find the highest AC that is enabled and does not require
	 *  admission control. The spec disallows downgrading to an AC,
	 *  which is enabled due to a completed admission control.
	 *  Unadmitted traffic is not to be sent on an AC with admitted
	 *  traffic.
	 */
	for (down_ac = WMM_AC_BK; down_ac < eval_ac; down_ac++) {
		ac_status = &priv->wmm.ac_status[down_ac];

		if (!ac_status->disabled && !ac_status->flow_required)
			/* AC is enabled and does not require admission
			   control */
			ret_ac = (enum mwifiex_wmm_ac_e) down_ac;
	}

	return ret_ac;
}