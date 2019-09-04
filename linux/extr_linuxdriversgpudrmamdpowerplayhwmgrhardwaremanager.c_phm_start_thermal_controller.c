#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  platformCaps; } ;
struct pp_hwmgr {TYPE_2__* hwmgr_func; TYPE_1__ platform_descriptor; struct amdgpu_device* adev; } ;
struct TYPE_8__ {int /*<<< orphan*/  max_temp; int /*<<< orphan*/  min_temp; } ;
struct TYPE_9__ {TYPE_3__ thermal; } ;
struct TYPE_10__ {TYPE_4__ dpm; } ;
struct amdgpu_device {TYPE_5__ pm; } ;
struct PP_TemperatureRange {int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int (* start_thermal_controller ) (struct pp_hwmgr*,struct PP_TemperatureRange*) ;int /*<<< orphan*/  (* get_thermal_temperature_range ) (struct pp_hwmgr*,struct PP_TemperatureRange*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PHM_PlatformCaps_ThermalController ; 
 int /*<<< orphan*/  TEMP_RANGE_MAX ; 
 int /*<<< orphan*/  TEMP_RANGE_MIN ; 
 scalar_t__ phm_cap_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pp_hwmgr*,struct PP_TemperatureRange*) ; 
 int stub2 (struct pp_hwmgr*,struct PP_TemperatureRange*) ; 

int phm_start_thermal_controller(struct pp_hwmgr *hwmgr)
{
	int ret = 0;
	struct PP_TemperatureRange range = {TEMP_RANGE_MIN, TEMP_RANGE_MAX};
	struct amdgpu_device *adev = hwmgr->adev;

	if (hwmgr->hwmgr_func->get_thermal_temperature_range)
		hwmgr->hwmgr_func->get_thermal_temperature_range(
				hwmgr, &range);

	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_ThermalController)
			&& hwmgr->hwmgr_func->start_thermal_controller != NULL)
		ret = hwmgr->hwmgr_func->start_thermal_controller(hwmgr, &range);

	adev->pm.dpm.thermal.min_temp = range.min;
	adev->pm.dpm.thermal.max_temp = range.max;

	return ret;
}