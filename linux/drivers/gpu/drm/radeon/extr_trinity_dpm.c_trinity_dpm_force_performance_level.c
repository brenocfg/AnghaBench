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
struct trinity_ps {int num_levels; } ;
struct radeon_ps {int dummy; } ;
struct trinity_power_info {struct radeon_ps current_rps; } ;
struct TYPE_3__ {int forced_level; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;
typedef  enum radeon_dpm_forced_level { ____Placeholder_radeon_dpm_forced_level } radeon_dpm_forced_level ;

/* Variables and functions */
 int EINVAL ; 
 int RADEON_DPM_FORCED_LEVEL_HIGH ; 
 int RADEON_DPM_FORCED_LEVEL_LOW ; 
 int trinity_dpm_n_levels_disabled (struct radeon_device*,int) ; 
 struct trinity_power_info* trinity_get_pi (struct radeon_device*) ; 
 struct trinity_ps* trinity_get_ps (struct radeon_ps*) ; 

int trinity_dpm_force_performance_level(struct radeon_device *rdev,
					enum radeon_dpm_forced_level level)
{
	struct trinity_power_info *pi = trinity_get_pi(rdev);
	struct radeon_ps *rps = &pi->current_rps;
	struct trinity_ps *ps = trinity_get_ps(rps);
	int i, ret;

	if (ps->num_levels <= 1)
		return 0;

	if (level == RADEON_DPM_FORCED_LEVEL_HIGH) {
		/* not supported by the hw */
		return -EINVAL;
	} else if (level == RADEON_DPM_FORCED_LEVEL_LOW) {
		ret = trinity_dpm_n_levels_disabled(rdev, ps->num_levels - 1);
		if (ret)
			return ret;
	} else {
		for (i = 0; i < ps->num_levels; i++) {
			ret = trinity_dpm_n_levels_disabled(rdev, 0);
			if (ret)
				return ret;
		}
	}

	rdev->pm.dpm.forced_level = level;

	return 0;
}