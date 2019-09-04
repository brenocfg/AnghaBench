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
typedef  int /*<<< orphan*/  uint32_t ;
struct pp_hwmgr {TYPE_1__* hwmgr_func; } ;
struct pp_hw_power_state {int dummy; } ;
struct TYPE_2__ {int (* get_performance_level ) (struct pp_hwmgr*,struct pp_hw_power_state const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  PHM_PerformanceLevelDesignation ;
typedef  int /*<<< orphan*/  PHM_PerformanceLevel ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PHM_FUNC_CHECK (struct pp_hwmgr*) ; 
 int stub1 (struct pp_hwmgr*,struct pp_hw_power_state const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int phm_get_performance_level(struct pp_hwmgr *hwmgr, const struct pp_hw_power_state *state,
				PHM_PerformanceLevelDesignation designation, uint32_t index,
				PHM_PerformanceLevel *level)
{
	PHM_FUNC_CHECK(hwmgr);
	if (hwmgr->hwmgr_func->get_performance_level == NULL)
		return -EINVAL;

	return hwmgr->hwmgr_func->get_performance_level(hwmgr, state, designation, index, level);


}