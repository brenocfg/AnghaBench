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
struct amdgpu_ring {int ready; } ;
struct TYPE_2__ {struct amdgpu_ring ring_dec; } ;
struct amdgpu_device {TYPE_1__ vcn; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_PG_STATE_GATE ; 
 scalar_t__ RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCN ; 
 int /*<<< orphan*/  mmUVD_STATUS ; 
 int /*<<< orphan*/  vcn_v1_0_set_powergating_state (struct amdgpu_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vcn_v1_0_hw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct amdgpu_ring *ring = &adev->vcn.ring_dec;

	if (RREG32_SOC15(VCN, 0, mmUVD_STATUS))
		vcn_v1_0_set_powergating_state(adev, AMD_PG_STATE_GATE);

	ring->ready = false;

	return 0;
}