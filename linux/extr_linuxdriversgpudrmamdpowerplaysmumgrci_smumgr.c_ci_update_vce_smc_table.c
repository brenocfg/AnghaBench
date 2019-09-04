#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_12__ {int vce_dpm_enable_mask; } ;
struct smu7_hwmgr {TYPE_6__ dpm_level_enable_mask; } ;
struct TYPE_9__ {scalar_t__ vddc; } ;
struct TYPE_8__ {scalar_t__ vddc; } ;
struct TYPE_10__ {TYPE_3__ max_clock_voltage_on_dc; TYPE_2__ max_clock_voltage_on_ac; struct phm_vce_clock_voltage_dependency_table* vce_clock_voltage_dependency_table; } ;
struct pp_hwmgr {scalar_t__ dpm_level; int /*<<< orphan*/  device; TYPE_4__ dyn_state; struct smu7_hwmgr* backend; struct amdgpu_device* adev; } ;
struct phm_vce_clock_voltage_dependency_table {size_t count; TYPE_5__* entries; } ;
struct TYPE_7__ {scalar_t__ ac_power; } ;
struct amdgpu_device {TYPE_1__ pm; } ;
typedef  size_t int32_t ;
struct TYPE_11__ {scalar_t__ v; } ;

/* Variables and functions */
 scalar_t__ AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK ; 
 scalar_t__ AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK ; 
 scalar_t__ AMD_DPM_FORCED_LEVEL_PROFILE_PEAK ; 
 scalar_t__ AMD_DPM_FORCED_LEVEL_PROFILE_STANDARD ; 
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int /*<<< orphan*/  DPM_TABLE_475 ; 
 int /*<<< orphan*/  PHM_PlatformCaps_VCEDPM ; 
 int /*<<< orphan*/  PHM_WRITE_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPSMC_MSG_VCEDPM_SetEnabledMask ; 
 int /*<<< orphan*/  PP_CAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VceBootLevel ; 
 int /*<<< orphan*/  ci_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ci_update_vce_smc_table(struct pp_hwmgr *hwmgr)
{
	struct amdgpu_device *adev = hwmgr->adev;
	struct smu7_hwmgr *data = hwmgr->backend;
	struct phm_vce_clock_voltage_dependency_table *vce_table =
			hwmgr->dyn_state.vce_clock_voltage_dependency_table;
	uint32_t profile_mode_mask = AMD_DPM_FORCED_LEVEL_PROFILE_STANDARD |
					AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK |
					AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK |
					AMD_DPM_FORCED_LEVEL_PROFILE_PEAK;
	uint32_t max_vddc = adev->pm.ac_power ? hwmgr->dyn_state.max_clock_voltage_on_ac.vddc :
						hwmgr->dyn_state.max_clock_voltage_on_dc.vddc;
	int32_t i;

	PHM_WRITE_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, DPM_TABLE_475,
				VceBootLevel, 0); /* temp hard code to level 0, vce can set min evclk*/

	data->dpm_level_enable_mask.vce_dpm_enable_mask = 0;

	for (i = vce_table->count - 1; i >= 0; i--) {
		if (vce_table->entries[i].v <= max_vddc)
			data->dpm_level_enable_mask.vce_dpm_enable_mask |= 1 << i;
		if (hwmgr->dpm_level & profile_mode_mask || !PP_CAP(PHM_PlatformCaps_VCEDPM))
			break;
	}
	ci_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_VCEDPM_SetEnabledMask,
				data->dpm_level_enable_mask.vce_dpm_enable_mask);

	return 0;
}