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
struct TYPE_2__ {int (* stop_thermal_controller ) (struct pp_hwmgr*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PHM_FUNC_CHECK (struct pp_hwmgr*) ; 
 int stub1 (struct pp_hwmgr*) ; 

int phm_stop_thermal_controller(struct pp_hwmgr *hwmgr)
{
	PHM_FUNC_CHECK(hwmgr);

	if (hwmgr->hwmgr_func->stop_thermal_controller == NULL)
		return -EINVAL;

	return hwmgr->hwmgr_func->stop_thermal_controller(hwmgr);
}