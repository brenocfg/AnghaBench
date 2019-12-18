#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_5__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_3__ pm; TYPE_2__ powerplay; int /*<<< orphan*/  smu; } ;
struct TYPE_4__ {scalar_t__ set_powergating_by_smu; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_IP_BLOCK_TYPE_VCE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,char*,int) ; 
 int /*<<< orphan*/  amdgpu_dpm_set_powergating_by_smu (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int smu_dpm_set_power_gate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void amdgpu_dpm_enable_vce(struct amdgpu_device *adev, bool enable)
{
	int ret = 0;
	if (is_support_sw_smu(adev)) {
	    ret = smu_dpm_set_power_gate(&adev->smu, AMD_IP_BLOCK_TYPE_VCE, enable);
	    if (ret)
		DRM_ERROR("[SW SMU]: dpm enable vce failed, state = %s, ret = %d. \n",
			  enable ? "true" : "false", ret);
	} else if (adev->powerplay.pp_funcs->set_powergating_by_smu) {
		/* enable/disable VCE */
		mutex_lock(&adev->pm.mutex);
		amdgpu_dpm_set_powergating_by_smu(adev, AMD_IP_BLOCK_TYPE_VCE, !enable);
		mutex_unlock(&adev->pm.mutex);
	}
}