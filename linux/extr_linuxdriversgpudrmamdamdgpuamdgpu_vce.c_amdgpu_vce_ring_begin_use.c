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
struct amdgpu_ring {struct amdgpu_device* adev; } ;
struct TYPE_3__ {int /*<<< orphan*/  idle_mutex; int /*<<< orphan*/  idle_work; } ;
struct TYPE_4__ {scalar_t__ dpm_enabled; } ;
struct amdgpu_device {TYPE_1__ vce; TYPE_2__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_CG_STATE_UNGATE ; 
 int /*<<< orphan*/  AMD_IP_BLOCK_TYPE_VCE ; 
 int /*<<< orphan*/  AMD_PG_STATE_UNGATE ; 
 int /*<<< orphan*/  amdgpu_asic_set_vce_clocks (struct amdgpu_device*,int,int) ; 
 int /*<<< orphan*/  amdgpu_device_ip_set_clockgating_state (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_device_ip_set_powergating_state (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_dpm_enable_vce (struct amdgpu_device*,int) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void amdgpu_vce_ring_begin_use(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;
	bool set_clocks;

	if (amdgpu_sriov_vf(adev))
		return;

	mutex_lock(&adev->vce.idle_mutex);
	set_clocks = !cancel_delayed_work_sync(&adev->vce.idle_work);
	if (set_clocks) {
		if (adev->pm.dpm_enabled) {
			amdgpu_dpm_enable_vce(adev, true);
		} else {
			amdgpu_asic_set_vce_clocks(adev, 53300, 40000);
			amdgpu_device_ip_set_clockgating_state(adev, AMD_IP_BLOCK_TYPE_VCE,
							       AMD_CG_STATE_UNGATE);
			amdgpu_device_ip_set_powergating_state(adev, AMD_IP_BLOCK_TYPE_VCE,
							       AMD_PG_STATE_UNGATE);

		}
	}
	mutex_unlock(&adev->vce.idle_mutex);
}