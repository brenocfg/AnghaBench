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
struct amd_pp_simple_clock_info {int dummy; } ;
struct TYPE_2__ {int (* get_dal_power_level ) (struct pp_hwmgr*,struct amd_pp_simple_clock_info*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PHM_FUNC_CHECK (struct pp_hwmgr*) ; 
 int stub1 (struct pp_hwmgr*,struct amd_pp_simple_clock_info*) ; 

int phm_get_dal_power_level(struct pp_hwmgr *hwmgr,
		struct amd_pp_simple_clock_info *info)
{
	PHM_FUNC_CHECK(hwmgr);

	if (info == NULL || hwmgr->hwmgr_func->get_dal_power_level == NULL)
		return -EINVAL;
	return hwmgr->hwmgr_func->get_dal_power_level(hwmgr, info);
}