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
struct amdgpu_ps {int dummy; } ;
struct TYPE_3__ {struct amdgpu_ps* requested_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct amdgpu_device {TYPE_2__ pm; } ;

/* Variables and functions */
 int si_halt_smc (struct amdgpu_device*) ; 
 int si_populate_smc_tdp_limits (struct amdgpu_device*,struct amdgpu_ps*) ; 
 int si_populate_smc_tdp_limits_2 (struct amdgpu_device*,struct amdgpu_ps*) ; 
 int si_restrict_performance_levels_before_switch (struct amdgpu_device*) ; 
 int si_resume_smc (struct amdgpu_device*) ; 
 int si_set_sw_state (struct amdgpu_device*) ; 

__attribute__((used)) static int si_power_control_set_level(struct amdgpu_device *adev)
{
	struct amdgpu_ps *new_ps = adev->pm.dpm.requested_ps;
	int ret;

	ret = si_restrict_performance_levels_before_switch(adev);
	if (ret)
		return ret;
	ret = si_halt_smc(adev);
	if (ret)
		return ret;
	ret = si_populate_smc_tdp_limits(adev, new_ps);
	if (ret)
		return ret;
	ret = si_populate_smc_tdp_limits_2(adev, new_ps);
	if (ret)
		return ret;
	ret = si_resume_smc(adev);
	if (ret)
		return ret;
	ret = si_set_sw_state(adev);
	if (ret)
		return ret;
	return 0;
}