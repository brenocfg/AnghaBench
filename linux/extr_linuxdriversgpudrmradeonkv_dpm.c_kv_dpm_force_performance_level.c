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

/* Variables and functions */
 int RADEON_DPM_FORCED_LEVEL_AUTO ; 
 int RADEON_DPM_FORCED_LEVEL_HIGH ; 
 int RADEON_DPM_FORCED_LEVEL_LOW ; 
 int kv_force_dpm_highest (struct radeon_device*) ; 
 int kv_force_dpm_lowest (struct radeon_device*) ; 
 int kv_unforce_levels (struct radeon_device*) ; 

int kv_dpm_force_performance_level(struct radeon_device *rdev,
				   enum radeon_dpm_forced_level level)
{
	int ret;

	if (level == RADEON_DPM_FORCED_LEVEL_HIGH) {
		ret = kv_force_dpm_highest(rdev);
		if (ret)
			return ret;
	} else if (level == RADEON_DPM_FORCED_LEVEL_LOW) {
		ret = kv_force_dpm_lowest(rdev);
		if (ret)
			return ret;
	} else if (level == RADEON_DPM_FORCED_LEVEL_AUTO) {
		ret = kv_unforce_levels(rdev);
		if (ret)
			return ret;
	}

	rdev->pm.dpm.forced_level = level;

	return 0;
}