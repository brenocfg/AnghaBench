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
 int amdgpu_uvd_resume (struct amdgpu_device*) ; 
 int uvd_v5_0_hw_init (struct amdgpu_device*) ; 

__attribute__((used)) static int uvd_v5_0_resume(void *handle)
{
	int r;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	r = amdgpu_uvd_resume(adev);
	if (r)
		return r;

	return uvd_v5_0_hw_init(adev);
}