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
struct amdgpu_device {int flags; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int amdgpu_gpu_recovery ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 

__attribute__((used)) static bool amdgpu_bo_need_backup(struct amdgpu_device *adev)
{
	if (adev->flags & AMD_IS_APU)
		return false;

	if (amdgpu_gpu_recovery == 0 ||
	    (amdgpu_gpu_recovery == -1  && !amdgpu_sriov_vf(adev)))
		return false;

	return true;
}