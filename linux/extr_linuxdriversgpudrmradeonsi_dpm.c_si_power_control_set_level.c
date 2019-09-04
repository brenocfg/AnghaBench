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
struct radeon_ps {int dummy; } ;
struct TYPE_3__ {struct radeon_ps* requested_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;

/* Variables and functions */
 int si_halt_smc (struct radeon_device*) ; 
 int si_populate_smc_tdp_limits (struct radeon_device*,struct radeon_ps*) ; 
 int si_populate_smc_tdp_limits_2 (struct radeon_device*,struct radeon_ps*) ; 
 int si_restrict_performance_levels_before_switch (struct radeon_device*) ; 
 int si_resume_smc (struct radeon_device*) ; 
 int si_set_sw_state (struct radeon_device*) ; 

__attribute__((used)) static int si_power_control_set_level(struct radeon_device *rdev)
{
	struct radeon_ps *new_ps = rdev->pm.dpm.requested_ps;
	int ret;

	ret = si_restrict_performance_levels_before_switch(rdev);
	if (ret)
		return ret;
	ret = si_halt_smc(rdev);
	if (ret)
		return ret;
	ret = si_populate_smc_tdp_limits(rdev, new_ps);
	if (ret)
		return ret;
	ret = si_populate_smc_tdp_limits_2(rdev, new_ps);
	if (ret)
		return ret;
	ret = si_resume_smc(rdev);
	if (ret)
		return ret;
	ret = si_set_sw_state(rdev);
	if (ret)
		return ret;
	return 0;
}