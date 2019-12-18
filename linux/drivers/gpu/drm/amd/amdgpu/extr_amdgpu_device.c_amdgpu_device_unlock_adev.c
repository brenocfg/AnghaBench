#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct amdgpu_device {int /*<<< orphan*/  lock_reset; scalar_t__ in_gpu_reset; int /*<<< orphan*/  mp1_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  PP_MP1_STATE_NONE ; 
 int /*<<< orphan*/  amdgpu_amdkfd_post_reset (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_vf_error_trans_all (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_device_unlock_adev(struct amdgpu_device *adev)
{
	/*unlock kfd: SRIOV would do it separately */
	if (!amdgpu_sriov_vf(adev))
                amdgpu_amdkfd_post_reset(adev);
	amdgpu_vf_error_trans_all(adev);
	adev->mp1_state = PP_MP1_STATE_NONE;
	adev->in_gpu_reset = 0;
	mutex_unlock(&adev->lock_reset);
}