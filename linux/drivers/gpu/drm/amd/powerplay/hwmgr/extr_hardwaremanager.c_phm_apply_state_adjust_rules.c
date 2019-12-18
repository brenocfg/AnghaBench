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
struct pp_power_state {int dummy; } ;
struct pp_hwmgr {TYPE_1__* hwmgr_func; } ;
struct TYPE_2__ {int (* apply_state_adjust_rules ) (struct pp_hwmgr*,struct pp_power_state*,struct pp_power_state const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PHM_FUNC_CHECK (struct pp_hwmgr*) ; 
 int stub1 (struct pp_hwmgr*,struct pp_power_state*,struct pp_power_state const*) ; 

int phm_apply_state_adjust_rules(struct pp_hwmgr *hwmgr,
				   struct pp_power_state *adjusted_ps,
			     const struct pp_power_state *current_ps)
{
	PHM_FUNC_CHECK(hwmgr);

	if (hwmgr->hwmgr_func->apply_state_adjust_rules != NULL)
		return hwmgr->hwmgr_func->apply_state_adjust_rules(
									hwmgr,
								 adjusted_ps,
								 current_ps);
	return 0;
}