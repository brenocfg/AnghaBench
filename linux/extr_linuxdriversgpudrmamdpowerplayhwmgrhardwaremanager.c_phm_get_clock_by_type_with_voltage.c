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
struct pp_clock_levels_with_voltage {int dummy; } ;
typedef  enum amd_pp_clock_type { ____Placeholder_amd_pp_clock_type } amd_pp_clock_type ;
struct TYPE_2__ {int (* get_clock_by_type_with_voltage ) (struct pp_hwmgr*,int,struct pp_clock_levels_with_voltage*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PHM_FUNC_CHECK (struct pp_hwmgr*) ; 
 int stub1 (struct pp_hwmgr*,int,struct pp_clock_levels_with_voltage*) ; 

int phm_get_clock_by_type_with_voltage(struct pp_hwmgr *hwmgr,
		enum amd_pp_clock_type type,
		struct pp_clock_levels_with_voltage *clocks)
{
	PHM_FUNC_CHECK(hwmgr);

	if (hwmgr->hwmgr_func->get_clock_by_type_with_voltage == NULL)
		return -EINVAL;

	return hwmgr->hwmgr_func->get_clock_by_type_with_voltage(hwmgr, type, clocks);

}