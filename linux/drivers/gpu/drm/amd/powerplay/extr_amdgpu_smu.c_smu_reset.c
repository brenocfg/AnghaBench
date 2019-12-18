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
struct smu_context {struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int smu_hw_fini (struct amdgpu_device*) ; 
 int smu_hw_init (struct amdgpu_device*) ; 

int smu_reset(struct smu_context *smu)
{
	struct amdgpu_device *adev = smu->adev;
	int ret = 0;

	ret = smu_hw_fini(adev);
	if (ret)
		return ret;

	ret = smu_hw_init(adev);
	if (ret)
		return ret;

	return ret;
}