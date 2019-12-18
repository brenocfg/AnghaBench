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
struct kgd_dev {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_device_gpu_recover (struct amdgpu_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ amdgpu_device_should_recover_gpu (struct amdgpu_device*) ; 

void amdgpu_amdkfd_gpu_reset(struct kgd_dev *kgd)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)kgd;

	if (amdgpu_device_should_recover_gpu(adev))
		amdgpu_device_gpu_recover(adev, NULL);
}