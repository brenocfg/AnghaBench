#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int vce_active; int /*<<< orphan*/  vce_level; } ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; TYPE_3__ dpm; } ;
struct TYPE_6__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_4__ pm; TYPE_2__ powerplay; } ;
struct TYPE_5__ {scalar_t__ set_powergating_by_smu; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_CG_STATE_GATE ; 
 int /*<<< orphan*/  AMD_CG_STATE_UNGATE ; 
 int /*<<< orphan*/  AMD_IP_BLOCK_TYPE_VCE ; 
 int /*<<< orphan*/  AMD_PG_STATE_GATE ; 
 int /*<<< orphan*/  AMD_PG_STATE_UNGATE ; 
 int /*<<< orphan*/  AMD_VCE_LEVEL_AC_ALL ; 
 int /*<<< orphan*/  amdgpu_device_ip_set_clockgating_state (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_device_ip_set_powergating_state (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_dpm_set_powergating_by_smu (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_pm_compute_clocks (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void amdgpu_dpm_enable_vce(struct amdgpu_device *adev, bool enable)
{
	if (adev->powerplay.pp_funcs->set_powergating_by_smu) {
		/* enable/disable VCE */
		mutex_lock(&adev->pm.mutex);
		amdgpu_dpm_set_powergating_by_smu(adev, AMD_IP_BLOCK_TYPE_VCE, !enable);
		mutex_unlock(&adev->pm.mutex);
	} else {
		if (enable) {
			mutex_lock(&adev->pm.mutex);
			adev->pm.dpm.vce_active = true;
			/* XXX select vce level based on ring/task */
			adev->pm.dpm.vce_level = AMD_VCE_LEVEL_AC_ALL;
			mutex_unlock(&adev->pm.mutex);
			amdgpu_device_ip_set_clockgating_state(adev, AMD_IP_BLOCK_TYPE_VCE,
							       AMD_CG_STATE_UNGATE);
			amdgpu_device_ip_set_powergating_state(adev, AMD_IP_BLOCK_TYPE_VCE,
							       AMD_PG_STATE_UNGATE);
			amdgpu_pm_compute_clocks(adev);
		} else {
			amdgpu_device_ip_set_powergating_state(adev, AMD_IP_BLOCK_TYPE_VCE,
							       AMD_PG_STATE_GATE);
			amdgpu_device_ip_set_clockgating_state(adev, AMD_IP_BLOCK_TYPE_VCE,
							       AMD_CG_STATE_GATE);
			mutex_lock(&adev->pm.mutex);
			adev->pm.dpm.vce_active = false;
			mutex_unlock(&adev->pm.mutex);
			amdgpu_pm_compute_clocks(adev);
		}

	}
}