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
struct msm_dsi_pll {int (* restore_state ) (struct msm_dsi_pll*) ;int state_saved; } ;

/* Variables and functions */
 int stub1 (struct msm_dsi_pll*) ; 

int msm_dsi_pll_restore_state(struct msm_dsi_pll *pll)
{
	int ret;

	if (pll->restore_state && pll->state_saved) {
		ret = pll->restore_state(pll);
		if (ret)
			return ret;

		pll->state_saved = false;
	}

	return 0;
}