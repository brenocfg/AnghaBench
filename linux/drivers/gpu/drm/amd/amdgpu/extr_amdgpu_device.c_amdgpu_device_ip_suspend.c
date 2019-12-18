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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int amdgpu_device_ip_suspend_phase1 (struct amdgpu_device*) ; 
 int amdgpu_device_ip_suspend_phase2 (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_virt_release_full_gpu (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  amdgpu_virt_request_full_gpu (struct amdgpu_device*,int) ; 

int amdgpu_device_ip_suspend(struct amdgpu_device *adev)
{
	int r;

	if (amdgpu_sriov_vf(adev))
		amdgpu_virt_request_full_gpu(adev, false);

	r = amdgpu_device_ip_suspend_phase1(adev);
	if (r)
		return r;
	r = amdgpu_device_ip_suspend_phase2(adev);

	if (amdgpu_sriov_vf(adev))
		amdgpu_virt_release_full_gpu(adev, false);

	return r;
}