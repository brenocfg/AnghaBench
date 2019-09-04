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
struct TYPE_2__ {int (* disable_clock_power_gating ) (struct pp_hwmgr*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PHM_FUNC_CHECK (struct pp_hwmgr*) ; 
 int stub1 (struct pp_hwmgr*) ; 

int phm_disable_clock_power_gatings(struct pp_hwmgr *hwmgr)
{
	PHM_FUNC_CHECK(hwmgr);

	if (NULL != hwmgr->hwmgr_func->disable_clock_power_gating)
		return hwmgr->hwmgr_func->disable_clock_power_gating(hwmgr);

	return 0;
}