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
struct TYPE_2__ {scalar_t__ load_type; } ;
struct amdgpu_device {TYPE_1__ firmware; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  sdma_v4_0_ctx_switch_enable (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  sdma_v4_0_enable (struct amdgpu_device*,int) ; 
 int sdma_v4_0_gfx_resume (struct amdgpu_device*) ; 
 int sdma_v4_0_load_microcode (struct amdgpu_device*) ; 
 int sdma_v4_0_rlc_resume (struct amdgpu_device*) ; 

__attribute__((used)) static int sdma_v4_0_start(struct amdgpu_device *adev)
{
	int r = 0;

	if (amdgpu_sriov_vf(adev)) {
		sdma_v4_0_ctx_switch_enable(adev, false);
		sdma_v4_0_enable(adev, false);

		/* set RB registers */
		r = sdma_v4_0_gfx_resume(adev);
		return r;
	}

	if (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP) {
		r = sdma_v4_0_load_microcode(adev);
		if (r)
			return r;
	}

	/* unhalt the MEs */
	sdma_v4_0_enable(adev, true);
	/* enable sdma ring preemption */
	sdma_v4_0_ctx_switch_enable(adev, true);

	/* start the gfx rings and rlc compute queues */
	r = sdma_v4_0_gfx_resume(adev);
	if (r)
		return r;
	r = sdma_v4_0_rlc_resume(adev);

	return r;
}