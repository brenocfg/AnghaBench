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
typedef  enum amd_clockgating_state { ____Placeholder_amd_clockgating_state } amd_clockgating_state ;

/* Variables and functions */
 int athub_v2_0_set_clockgating (struct amdgpu_device*,int) ; 
 int mmhub_v2_0_set_clockgating (struct amdgpu_device*,int) ; 

__attribute__((used)) static int gmc_v10_0_set_clockgating_state(void *handle,
					   enum amd_clockgating_state state)
{
	int r;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	r = mmhub_v2_0_set_clockgating(adev, state);
	if (r)
		return r;

	return athub_v2_0_set_clockgating(adev, state);
}