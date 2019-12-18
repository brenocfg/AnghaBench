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
struct TYPE_8__ {int /*<<< orphan*/  max_mem_emergency_temp; int /*<<< orphan*/  max_mem_crit_temp; int /*<<< orphan*/  min_mem_temp; int /*<<< orphan*/  max_hotspot_emergency_temp; int /*<<< orphan*/  max_hotspot_crit_temp; int /*<<< orphan*/  min_hotspot_temp; int /*<<< orphan*/  max_edge_emergency_temp; int /*<<< orphan*/  max_temp; int /*<<< orphan*/  min_temp; } ;
struct TYPE_9__ {TYPE_3__ thermal; } ;
struct TYPE_10__ {TYPE_4__ dpm; } ;
struct amdgpu_device {TYPE_5__ pm; } ;
struct PP_TemperatureRange {int /*<<< orphan*/  mem_emergency_max; int /*<<< orphan*/  mem_crit_max; int /*<<< orphan*/  mem_min; int /*<<< orphan*/  hotspot_emergency_max; int /*<<< orphan*/  hotspot_crit_max; int /*<<< orphan*/  hotspot_min; int /*<<< orphan*/  edge_emergency_max; int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
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
	struct PP_TemperatureRange range = {
		TEMP_RANGE_MIN,
		TEMP_RANGE_MAX,
		TEMP_RANGE_MAX,
		TEMP_RANGE_MIN,
		TEMP_RANGE_MAX,
		TEMP_RANGE_MAX,
		TEMP_RANGE_MIN,
		TEMP_RANGE_MAX,
		TEMP_RANGE_MAX};
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
	adev->pm.dpm.thermal.max_edge_emergency_temp = range.edge_emergency_max;
	adev->pm.dpm.thermal.min_hotspot_temp = range.hotspot_min;
	adev->pm.dpm.thermal.max_hotspot_crit_temp = range.hotspot_crit_max;
	adev->pm.dpm.thermal.max_hotspot_emergency_temp = range.hotspot_emergency_max;
	adev->pm.dpm.thermal.min_mem_temp = range.mem_min;
	adev->pm.dpm.thermal.max_mem_crit_temp = range.mem_crit_max;
	adev->pm.dpm.thermal.max_mem_emergency_temp = range.mem_emergency_max;

	return ret;
}