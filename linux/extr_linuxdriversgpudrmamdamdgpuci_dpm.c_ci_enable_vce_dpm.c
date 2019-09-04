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
struct TYPE_12__ {int vce_dpm_enable_mask; } ;
struct ci_power_info {TYPE_6__ dpm_level_enable_mask; int /*<<< orphan*/  caps_vce_dpm; } ;
struct TYPE_8__ {int count; TYPE_1__* entries; } ;
struct amdgpu_clock_and_voltage_limits {scalar_t__ vddc; } ;
struct TYPE_9__ {TYPE_2__ vce_clock_voltage_dependency_table; struct amdgpu_clock_and_voltage_limits max_clock_voltage_on_dc; struct amdgpu_clock_and_voltage_limits max_clock_voltage_on_ac; } ;
struct TYPE_10__ {TYPE_3__ dyn_state; } ;
struct TYPE_11__ {TYPE_4__ dpm; scalar_t__ ac_power; } ;
struct amdgpu_device {TYPE_5__ pm; } ;
struct TYPE_7__ {scalar_t__ v; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_VCEDPM_Disable ; 
 int /*<<< orphan*/  PPSMC_MSG_VCEDPM_Enable ; 
 int /*<<< orphan*/  PPSMC_MSG_VCEDPM_SetEnabledMask ; 
 scalar_t__ PPSMC_Result_OK ; 
 scalar_t__ amdgpu_ci_send_msg_to_smc (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ci_send_msg_to_smc_with_parameter (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int ci_enable_vce_dpm(struct amdgpu_device *adev, bool enable)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	const struct amdgpu_clock_and_voltage_limits *max_limits;
	int i;

	if (adev->pm.ac_power)
		max_limits = &adev->pm.dpm.dyn_state.max_clock_voltage_on_ac;
	else
		max_limits = &adev->pm.dpm.dyn_state.max_clock_voltage_on_dc;

	if (enable) {
		pi->dpm_level_enable_mask.vce_dpm_enable_mask = 0;
		for (i = adev->pm.dpm.dyn_state.vce_clock_voltage_dependency_table.count - 1; i >= 0; i--) {
			if (adev->pm.dpm.dyn_state.vce_clock_voltage_dependency_table.entries[i].v <= max_limits->vddc) {
				pi->dpm_level_enable_mask.vce_dpm_enable_mask |= 1 << i;

				if (!pi->caps_vce_dpm)
					break;
			}
		}

		amdgpu_ci_send_msg_to_smc_with_parameter(adev,
						  PPSMC_MSG_VCEDPM_SetEnabledMask,
						  pi->dpm_level_enable_mask.vce_dpm_enable_mask);
	}

	return (amdgpu_ci_send_msg_to_smc(adev, enable ?
				   PPSMC_MSG_VCEDPM_Enable : PPSMC_MSG_VCEDPM_Disable) == PPSMC_Result_OK) ?
		0 : -EINVAL;
}