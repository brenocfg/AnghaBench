#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct si_ps {int performance_level_count; } ;
struct amdgpu_ps {int dummy; } ;
struct TYPE_3__ {int forced_level; struct amdgpu_ps* current_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct amdgpu_device {TYPE_2__ pm; } ;
typedef  enum amd_dpm_forced_level { ____Placeholder_amd_dpm_forced_level } amd_dpm_forced_level ;

/* Variables and functions */
 int AMD_DPM_FORCED_LEVEL_AUTO ; 
 int AMD_DPM_FORCED_LEVEL_HIGH ; 
 int AMD_DPM_FORCED_LEVEL_LOW ; 
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_SetEnabledLevels ; 
 int /*<<< orphan*/  PPSMC_MSG_SetForcedLevels ; 
 scalar_t__ PPSMC_Result_OK ; 
 struct si_ps* si_get_ps (struct amdgpu_ps*) ; 
 scalar_t__ si_send_msg_to_smc_with_parameter (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int si_dpm_force_performance_level(void *handle,
				   enum amd_dpm_forced_level level)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct amdgpu_ps *rps = adev->pm.dpm.current_ps;
	struct  si_ps *ps = si_get_ps(rps);
	u32 levels = ps->performance_level_count;

	if (level == AMD_DPM_FORCED_LEVEL_HIGH) {
		if (si_send_msg_to_smc_with_parameter(adev, PPSMC_MSG_SetEnabledLevels, levels) != PPSMC_Result_OK)
			return -EINVAL;

		if (si_send_msg_to_smc_with_parameter(adev, PPSMC_MSG_SetForcedLevels, 1) != PPSMC_Result_OK)
			return -EINVAL;
	} else if (level == AMD_DPM_FORCED_LEVEL_LOW) {
		if (si_send_msg_to_smc_with_parameter(adev, PPSMC_MSG_SetForcedLevels, 0) != PPSMC_Result_OK)
			return -EINVAL;

		if (si_send_msg_to_smc_with_parameter(adev, PPSMC_MSG_SetEnabledLevels, 1) != PPSMC_Result_OK)
			return -EINVAL;
	} else if (level == AMD_DPM_FORCED_LEVEL_AUTO) {
		if (si_send_msg_to_smc_with_parameter(adev, PPSMC_MSG_SetForcedLevels, 0) != PPSMC_Result_OK)
			return -EINVAL;

		if (si_send_msg_to_smc_with_parameter(adev, PPSMC_MSG_SetEnabledLevels, levels) != PPSMC_Result_OK)
			return -EINVAL;
	}

	adev->pm.dpm.forced_level = level;

	return 0;
}