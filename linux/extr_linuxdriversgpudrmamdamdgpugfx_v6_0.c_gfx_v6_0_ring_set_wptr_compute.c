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
struct amdgpu_ring {int /*<<< orphan*/  wptr; struct amdgpu_device* adev; } ;
struct TYPE_2__ {struct amdgpu_ring* compute_ring; } ;
struct amdgpu_device {TYPE_1__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCP_RB1_WPTR ; 
 int /*<<< orphan*/  mmCP_RB2_WPTR ; 

__attribute__((used)) static void gfx_v6_0_ring_set_wptr_compute(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;

	if (ring == &adev->gfx.compute_ring[0]) {
		WREG32(mmCP_RB1_WPTR, lower_32_bits(ring->wptr));
		(void)RREG32(mmCP_RB1_WPTR);
	} else if (ring == &adev->gfx.compute_ring[1]) {
		WREG32(mmCP_RB2_WPTR, lower_32_bits(ring->wptr));
		(void)RREG32(mmCP_RB2_WPTR);
	} else {
		BUG();
	}

}