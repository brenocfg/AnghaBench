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
 int /*<<< orphan*/  AMD_CG_STATE_GATE ; 
 int amdgpu_uvd_suspend (struct amdgpu_device*) ; 
 int uvd_v5_0_hw_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  uvd_v5_0_set_clockgating_state (struct amdgpu_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uvd_v5_0_suspend(void *handle)
{
	int r;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	r = uvd_v5_0_hw_fini(adev);
	if (r)
		return r;
	uvd_v5_0_set_clockgating_state(adev, AMD_CG_STATE_GATE);

	return amdgpu_uvd_suspend(adev);
}