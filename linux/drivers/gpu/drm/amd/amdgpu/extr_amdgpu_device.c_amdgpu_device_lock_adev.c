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
struct amdgpu_device {int in_gpu_reset; int /*<<< orphan*/  mp1_state; int /*<<< orphan*/  gpu_reset_counter; int /*<<< orphan*/  lock_reset; } ;

/* Variables and functions */
#define  AMD_RESET_METHOD_MODE1 129 
#define  AMD_RESET_METHOD_MODE2 128 
 int /*<<< orphan*/  PP_MP1_STATE_NONE ; 
 int /*<<< orphan*/  PP_MP1_STATE_RESET ; 
 int /*<<< orphan*/  PP_MP1_STATE_SHUTDOWN ; 
 int /*<<< orphan*/  amdgpu_amdkfd_pre_reset (struct amdgpu_device*) ; 
 int amdgpu_asic_reset_method (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool amdgpu_device_lock_adev(struct amdgpu_device *adev, bool trylock)
{
	if (trylock) {
		if (!mutex_trylock(&adev->lock_reset))
			return false;
	} else
		mutex_lock(&adev->lock_reset);

	atomic_inc(&adev->gpu_reset_counter);
	adev->in_gpu_reset = 1;
	switch (amdgpu_asic_reset_method(adev)) {
	case AMD_RESET_METHOD_MODE1:
		adev->mp1_state = PP_MP1_STATE_SHUTDOWN;
		break;
	case AMD_RESET_METHOD_MODE2:
		adev->mp1_state = PP_MP1_STATE_RESET;
		break;
	default:
		adev->mp1_state = PP_MP1_STATE_NONE;
		break;
	}
	/* Block kfd: SRIOV would do it separately */
	if (!amdgpu_sriov_vf(adev))
                amdgpu_amdkfd_pre_reset(adev);

	return true;
}