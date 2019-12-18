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
struct pp_hwmgr {TYPE_1__* hwmgr_func; } ;
struct pp_hw_power_state {int dummy; } ;
struct phm_set_power_state_input {struct pp_hw_power_state const* pnew_state; struct pp_hw_power_state const* pcurrent_state; } ;
struct TYPE_2__ {int (* power_state_set ) (struct pp_hwmgr*,struct phm_set_power_state_input*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PHM_FUNC_CHECK (struct pp_hwmgr*) ; 
 int stub1 (struct pp_hwmgr*,struct phm_set_power_state_input*) ; 

int phm_set_power_state(struct pp_hwmgr *hwmgr,
		    const struct pp_hw_power_state *pcurrent_state,
		    const struct pp_hw_power_state *pnew_power_state)
{
	struct phm_set_power_state_input states;

	PHM_FUNC_CHECK(hwmgr);

	states.pcurrent_state = pcurrent_state;
	states.pnew_state = pnew_power_state;

	if (NULL != hwmgr->hwmgr_func->power_state_set)
		return hwmgr->hwmgr_func->power_state_set(hwmgr, &states);

	return 0;
}