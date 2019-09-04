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
struct radeon_ps {int dummy; } ;
struct TYPE_3__ {int forced_level; struct radeon_ps* current_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;
struct ni_ps {int performance_level_count; } ;
typedef  enum radeon_dpm_forced_level { ____Placeholder_radeon_dpm_forced_level } radeon_dpm_forced_level ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_SetEnabledLevels ; 
 int /*<<< orphan*/  PPSMC_MSG_SetForcedLevels ; 
 scalar_t__ PPSMC_Result_OK ; 
 int RADEON_DPM_FORCED_LEVEL_AUTO ; 
 int RADEON_DPM_FORCED_LEVEL_HIGH ; 
 int RADEON_DPM_FORCED_LEVEL_LOW ; 
 struct ni_ps* ni_get_ps (struct radeon_ps*) ; 
 scalar_t__ si_send_msg_to_smc_with_parameter (struct radeon_device*,int /*<<< orphan*/ ,int) ; 

int si_dpm_force_performance_level(struct radeon_device *rdev,
				   enum radeon_dpm_forced_level level)
{
	struct radeon_ps *rps = rdev->pm.dpm.current_ps;
	struct ni_ps *ps = ni_get_ps(rps);
	u32 levels = ps->performance_level_count;

	if (level == RADEON_DPM_FORCED_LEVEL_HIGH) {
		if (si_send_msg_to_smc_with_parameter(rdev, PPSMC_MSG_SetEnabledLevels, levels) != PPSMC_Result_OK)
			return -EINVAL;

		if (si_send_msg_to_smc_with_parameter(rdev, PPSMC_MSG_SetForcedLevels, 1) != PPSMC_Result_OK)
			return -EINVAL;
	} else if (level == RADEON_DPM_FORCED_LEVEL_LOW) {
		if (si_send_msg_to_smc_with_parameter(rdev, PPSMC_MSG_SetForcedLevels, 0) != PPSMC_Result_OK)
			return -EINVAL;

		if (si_send_msg_to_smc_with_parameter(rdev, PPSMC_MSG_SetEnabledLevels, 1) != PPSMC_Result_OK)
			return -EINVAL;
	} else if (level == RADEON_DPM_FORCED_LEVEL_AUTO) {
		if (si_send_msg_to_smc_with_parameter(rdev, PPSMC_MSG_SetForcedLevels, 0) != PPSMC_Result_OK)
			return -EINVAL;

		if (si_send_msg_to_smc_with_parameter(rdev, PPSMC_MSG_SetEnabledLevels, levels) != PPSMC_Result_OK)
			return -EINVAL;
	}

	rdev->pm.dpm.forced_level = level;

	return 0;
}