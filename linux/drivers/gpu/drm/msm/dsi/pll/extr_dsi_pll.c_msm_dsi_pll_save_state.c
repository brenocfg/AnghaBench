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
struct msm_dsi_pll {int state_saved; int /*<<< orphan*/  (* save_state ) (struct msm_dsi_pll*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct msm_dsi_pll*) ; 

void msm_dsi_pll_save_state(struct msm_dsi_pll *pll)
{
	if (pll->save_state) {
		pll->save_state(pll);
		pll->state_saved = true;
	}
}