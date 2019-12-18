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
struct evergreen_power_info {int /*<<< orphan*/  requested_rps; } ;
struct amdgpu_ps {int dummy; } ;
struct TYPE_3__ {struct amdgpu_ps* requested_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct amdgpu_device {TYPE_2__ pm; } ;

/* Variables and functions */
 struct evergreen_power_info* evergreen_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ni_update_requested_ps (struct amdgpu_device*,struct amdgpu_ps*) ; 
 int /*<<< orphan*/  si_apply_state_adjust_rules (struct amdgpu_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int si_dpm_pre_set_power_state(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct evergreen_power_info *eg_pi = evergreen_get_pi(adev);
	struct amdgpu_ps requested_ps = *adev->pm.dpm.requested_ps;
	struct amdgpu_ps *new_ps = &requested_ps;

	ni_update_requested_ps(adev, new_ps);
	si_apply_state_adjust_rules(adev, &eg_pi->requested_rps);

	return 0;
}