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
typedef  enum amd_powergating_state { ____Placeholder_amd_powergating_state } amd_powergating_state ;

/* Variables and functions */
 int AMD_PG_STATE_GATE ; 
 int vce_v2_0_start (struct amdgpu_device*) ; 
 int vce_v2_0_stop (struct amdgpu_device*) ; 

__attribute__((used)) static int vce_v2_0_set_powergating_state(void *handle,
					  enum amd_powergating_state state)
{
	/* This doesn't actually powergate the VCE block.
	 * That's done in the dpm code via the SMC.  This
	 * just re-inits the block as necessary.  The actual
	 * gating still happens in the dpm code.  We should
	 * revisit this when there is a cleaner line between
	 * the smc and the hw blocks
	 */
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (state == AMD_PG_STATE_GATE)
		return vce_v2_0_stop(adev);
	else
		return vce_v2_0_start(adev);
}