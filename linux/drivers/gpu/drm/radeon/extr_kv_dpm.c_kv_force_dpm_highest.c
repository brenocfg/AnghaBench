#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct radeon_device {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ CHIP_KABINI ; 
 scalar_t__ CHIP_MULLINS ; 
 int /*<<< orphan*/  PPSMC_MSG_DPM_ForceState ; 
 int SMU7_MAX_LEVELS_GRAPHICS ; 
 int kv_dpm_get_enable_mask (struct radeon_device*,int*) ; 
 int kv_send_msg_to_smc_with_parameter (struct radeon_device*,int /*<<< orphan*/ ,int) ; 
 int kv_set_enabled_level (struct radeon_device*,int) ; 

__attribute__((used)) static int kv_force_dpm_highest(struct radeon_device *rdev)
{
	int ret;
	u32 enable_mask, i;

	ret = kv_dpm_get_enable_mask(rdev, &enable_mask);
	if (ret)
		return ret;

	for (i = SMU7_MAX_LEVELS_GRAPHICS - 1; i > 0; i--) {
		if (enable_mask & (1 << i))
			break;
	}

	if (rdev->family == CHIP_KABINI || rdev->family == CHIP_MULLINS)
		return kv_send_msg_to_smc_with_parameter(rdev, PPSMC_MSG_DPM_ForceState, i);
	else
		return kv_set_enabled_level(rdev, i);
}