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
 int AMD_CG_STATE_GATE ; 
 int /*<<< orphan*/  cik_enable_sdma_mgcg (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  cik_enable_sdma_mgls (struct amdgpu_device*,int) ; 

__attribute__((used)) static int cik_sdma_set_clockgating_state(void *handle,
					  enum amd_clockgating_state state)
{
	bool gate = false;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (state == AMD_CG_STATE_GATE)
		gate = true;

	cik_enable_sdma_mgcg(adev, gate);
	cik_enable_sdma_mgls(adev, gate);

	return 0;
}