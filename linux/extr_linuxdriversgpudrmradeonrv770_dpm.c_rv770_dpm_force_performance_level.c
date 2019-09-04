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
struct TYPE_3__ {int forced_level; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;
typedef  enum radeon_dpm_forced_level { ____Placeholder_radeon_dpm_forced_level } radeon_dpm_forced_level ;
typedef  scalar_t__ PPSMC_Msg ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PPSMC_MSG_ForceHigh ; 
 scalar_t__ PPSMC_MSG_NoForcedLevel ; 
 scalar_t__ PPSMC_MSG_TwoLevelsDisabled ; 
 scalar_t__ PPSMC_MSG_ZeroLevelsDisabled ; 
 scalar_t__ PPSMC_Result_OK ; 
 int RADEON_DPM_FORCED_LEVEL_HIGH ; 
 int RADEON_DPM_FORCED_LEVEL_LOW ; 
 scalar_t__ rv770_send_msg_to_smc (struct radeon_device*,scalar_t__) ; 

int rv770_dpm_force_performance_level(struct radeon_device *rdev,
				      enum radeon_dpm_forced_level level)
{
	PPSMC_Msg msg;

	if (level == RADEON_DPM_FORCED_LEVEL_HIGH) {
		if (rv770_send_msg_to_smc(rdev, PPSMC_MSG_ZeroLevelsDisabled) != PPSMC_Result_OK)
			return -EINVAL;
		msg = PPSMC_MSG_ForceHigh;
	} else if (level == RADEON_DPM_FORCED_LEVEL_LOW) {
		if (rv770_send_msg_to_smc(rdev, PPSMC_MSG_NoForcedLevel) != PPSMC_Result_OK)
			return -EINVAL;
		msg = (PPSMC_Msg)(PPSMC_MSG_TwoLevelsDisabled);
	} else {
		if (rv770_send_msg_to_smc(rdev, PPSMC_MSG_NoForcedLevel) != PPSMC_Result_OK)
			return -EINVAL;
		msg = (PPSMC_Msg)(PPSMC_MSG_ZeroLevelsDisabled);
	}

	if (rv770_send_msg_to_smc(rdev, msg) != PPSMC_Result_OK)
		return -EINVAL;

	rdev->pm.dpm.forced_level = level;

	return 0;
}