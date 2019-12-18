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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_ring {scalar_t__ idx; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CAYMAN_RING_TYPE_CP1_INDEX ; 
 int /*<<< orphan*/  CP_RB0_WPTR ; 
 int /*<<< orphan*/  CP_RB1_WPTR ; 
 int /*<<< orphan*/  CP_RB2_WPTR ; 
 scalar_t__ RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 

u32 cayman_gfx_get_wptr(struct radeon_device *rdev,
			struct radeon_ring *ring)
{
	u32 wptr;

	if (ring->idx == RADEON_RING_TYPE_GFX_INDEX)
		wptr = RREG32(CP_RB0_WPTR);
	else if (ring->idx == CAYMAN_RING_TYPE_CP1_INDEX)
		wptr = RREG32(CP_RB1_WPTR);
	else
		wptr = RREG32(CP_RB2_WPTR);

	return wptr;
}