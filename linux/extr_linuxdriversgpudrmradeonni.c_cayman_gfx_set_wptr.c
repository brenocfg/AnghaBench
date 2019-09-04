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
struct radeon_ring {scalar_t__ idx; int /*<<< orphan*/  wptr; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CAYMAN_RING_TYPE_CP1_INDEX ; 
 int /*<<< orphan*/  CP_RB0_WPTR ; 
 int /*<<< orphan*/  CP_RB1_WPTR ; 
 int /*<<< orphan*/  CP_RB2_WPTR ; 
 scalar_t__ RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cayman_gfx_set_wptr(struct radeon_device *rdev,
			 struct radeon_ring *ring)
{
	if (ring->idx == RADEON_RING_TYPE_GFX_INDEX) {
		WREG32(CP_RB0_WPTR, ring->wptr);
		(void)RREG32(CP_RB0_WPTR);
	} else if (ring->idx == CAYMAN_RING_TYPE_CP1_INDEX) {
		WREG32(CP_RB1_WPTR, ring->wptr);
		(void)RREG32(CP_RB1_WPTR);
	} else {
		WREG32(CP_RB2_WPTR, ring->wptr);
		(void)RREG32(CP_RB2_WPTR);
	}
}