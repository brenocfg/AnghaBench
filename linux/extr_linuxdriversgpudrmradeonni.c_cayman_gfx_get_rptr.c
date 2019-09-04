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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_ring {int rptr_offs; scalar_t__ idx; } ;
struct TYPE_2__ {int /*<<< orphan*/ * wb; scalar_t__ enabled; } ;
struct radeon_device {TYPE_1__ wb; } ;

/* Variables and functions */
 scalar_t__ CAYMAN_RING_TYPE_CP1_INDEX ; 
 int /*<<< orphan*/  CP_RB0_RPTR ; 
 int /*<<< orphan*/  CP_RB1_RPTR ; 
 int /*<<< orphan*/  CP_RB2_RPTR ; 
 scalar_t__ RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 

u32 cayman_gfx_get_rptr(struct radeon_device *rdev,
			struct radeon_ring *ring)
{
	u32 rptr;

	if (rdev->wb.enabled)
		rptr = rdev->wb.wb[ring->rptr_offs/4];
	else {
		if (ring->idx == RADEON_RING_TYPE_GFX_INDEX)
			rptr = RREG32(CP_RB0_RPTR);
		else if (ring->idx == CAYMAN_RING_TYPE_CP1_INDEX)
			rptr = RREG32(CP_RB1_RPTR);
		else
			rptr = RREG32(CP_RB2_RPTR);
	}

	return rptr;
}