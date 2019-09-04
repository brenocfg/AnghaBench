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
 int ni_populate_smc_tdp_limits (struct radeon_device*,struct radeon_ps*) ; 
 int ni_restrict_performance_levels_before_switch (struct radeon_device*) ; 
 int rv770_halt_smc (struct radeon_device*) ; 
 int rv770_resume_smc (struct radeon_device*) ; 
 int rv770_set_sw_state (struct radeon_device*) ; 

__attribute__((used)) static int ni_power_control_set_level(struct radeon_device *rdev)
{
	struct radeon_ps *new_ps = rdev->pm.dpm.requested_ps;
	int ret;

	ret = ni_restrict_performance_levels_before_switch(rdev);
	if (ret)
		return ret;
	ret = rv770_halt_smc(rdev);
	if (ret)
		return ret;
	ret = ni_populate_smc_tdp_limits(rdev, new_ps);
	if (ret)
		return ret;
	ret = rv770_resume_smc(rdev);
	if (ret)
		return ret;
	ret = rv770_set_sw_state(rdev);
	if (ret)
		return ret;

	return 0;
}