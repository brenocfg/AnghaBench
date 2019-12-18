#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_14__ {int uvd_dpm_enable_mask; } ;
struct smu7_hwmgr {TYPE_7__ dpm_level_enable_mask; } ;
struct TYPE_10__ {scalar_t__ vddc; } ;
struct TYPE_9__ {scalar_t__ vddc; } ;
struct TYPE_11__ {TYPE_3__ max_clock_voltage_on_dc; TYPE_2__ max_clock_voltage_on_ac; struct phm_uvd_clock_voltage_dependency_table* uvd_clock_voltage_dependency_table; } ;
struct pp_hwmgr {scalar_t__ dpm_level; int /*<<< orphan*/  device; TYPE_4__ dyn_state; struct ci_smumgr* smu_backend; struct smu7_hwmgr* backend; struct amdgpu_device* adev; } ;
struct phm_uvd_clock_voltage_dependency_table {scalar_t__ count; TYPE_6__* entries; } ;
struct TYPE_12__ {scalar_t__ UvdBootLevel; } ;
struct ci_smumgr {TYPE_5__ smc_state_table; } ;
struct TYPE_8__ {scalar_t__ ac_power; } ;
struct amdgpu_device {TYPE_1__ pm; } ;
typedef  size_t int32_t ;
struct TYPE_13__ {scalar_t__ v; } ;

/* Variables and functions */
 scalar_t__ AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK ; 
 scalar_t__ AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK ; 
 scalar_t__ AMD_DPM_FORCED_LEVEL_PROFILE_PEAK ; 
 scalar_t__ AMD_DPM_FORCED_LEVEL_PROFILE_STANDARD ; 
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int /*<<< orphan*/  DPM_TABLE_475 ; 
 int /*<<< orphan*/  PHM_PlatformCaps_UVDDPM ; 
 int /*<<< orphan*/  PHM_WRITE_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PPSMC_MSG_UVDDPM_SetEnabledMask ; 
 scalar_t__ PP_CAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UvdBootLevel ; 
 int /*<<< orphan*/  ci_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ci_update_uvd_smc_table(struct pp_hwmgr *hwmgr)
{
	struct amdgpu_device *adev = hwmgr->adev;
	struct smu7_hwmgr *data = hwmgr->backend;
	struct ci_smumgr *smu_data = hwmgr->smu_backend;
	struct phm_uvd_clock_voltage_dependency_table *uvd_table =
			hwmgr->dyn_state.uvd_clock_voltage_dependency_table;
	uint32_t profile_mode_mask = AMD_DPM_FORCED_LEVEL_PROFILE_STANDARD |
					AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK |
					AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK |
					AMD_DPM_FORCED_LEVEL_PROFILE_PEAK;
	uint32_t max_vddc = adev->pm.ac_power ? hwmgr->dyn_state.max_clock_voltage_on_ac.vddc :
						hwmgr->dyn_state.max_clock_voltage_on_dc.vddc;
	int32_t i;

	if (PP_CAP(PHM_PlatformCaps_UVDDPM) || uvd_table->count <= 0)
		smu_data->smc_state_table.UvdBootLevel = 0;
	else
		smu_data->smc_state_table.UvdBootLevel = uvd_table->count - 1;

	PHM_WRITE_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, DPM_TABLE_475,
				UvdBootLevel, smu_data->smc_state_table.UvdBootLevel);

	data->dpm_level_enable_mask.uvd_dpm_enable_mask = 0;

	for (i = uvd_table->count - 1; i >= 0; i--) {
		if (uvd_table->entries[i].v <= max_vddc)
			data->dpm_level_enable_mask.uvd_dpm_enable_mask |= 1 << i;
		if (hwmgr->dpm_level & profile_mode_mask || !PP_CAP(PHM_PlatformCaps_UVDDPM))
			break;
	}
	ci_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_UVDDPM_SetEnabledMask,
				data->dpm_level_enable_mask.uvd_dpm_enable_mask);

	return 0;
}