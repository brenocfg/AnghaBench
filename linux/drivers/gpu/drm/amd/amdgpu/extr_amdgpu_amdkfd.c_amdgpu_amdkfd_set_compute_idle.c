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
struct kgd_dev {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_2__ powerplay; int /*<<< orphan*/  smu; } ;
struct TYPE_3__ {scalar_t__ switch_power_profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  PP_SMC_POWER_PROFILE_COMPUTE ; 
 int /*<<< orphan*/  amdgpu_dpm_switch_power_profile (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 
 int /*<<< orphan*/  smu_switch_power_profile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void amdgpu_amdkfd_set_compute_idle(struct kgd_dev *kgd, bool idle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)kgd;

	if (is_support_sw_smu(adev))
		smu_switch_power_profile(&adev->smu,
					 PP_SMC_POWER_PROFILE_COMPUTE,
					 !idle);
	else if (adev->powerplay.pp_funcs &&
		 adev->powerplay.pp_funcs->switch_power_profile)
		amdgpu_dpm_switch_power_profile(adev,
						PP_SMC_POWER_PROFILE_COMPUTE,
						!idle);
}