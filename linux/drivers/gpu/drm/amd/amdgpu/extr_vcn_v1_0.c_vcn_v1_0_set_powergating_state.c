#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int cur_state; } ;
struct amdgpu_device {TYPE_1__ vcn; } ;
typedef  enum amd_powergating_state { ____Placeholder_amd_powergating_state } amd_powergating_state ;

/* Variables and functions */
 int AMD_PG_STATE_GATE ; 
 int vcn_v1_0_start (struct amdgpu_device*) ; 
 int vcn_v1_0_stop (struct amdgpu_device*) ; 

__attribute__((used)) static int vcn_v1_0_set_powergating_state(void *handle,
					  enum amd_powergating_state state)
{
	/* This doesn't actually powergate the VCN block.
	 * That's done in the dpm code via the SMC.  This
	 * just re-inits the block as necessary.  The actual
	 * gating still happens in the dpm code.  We should
	 * revisit this when there is a cleaner line between
	 * the smc and the hw blocks
	 */
	int ret;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if(state == adev->vcn.cur_state)
		return 0;

	if (state == AMD_PG_STATE_GATE)
		ret = vcn_v1_0_stop(adev);
	else
		ret = vcn_v1_0_start(adev);

	if(!ret)
		adev->vcn.cur_state = state;
	return ret;
}