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
struct radeon_ring {int /*<<< orphan*/  rptr_save_reg; } ;
struct radeon_device {struct radeon_ring* ring; } ;

/* Variables and functions */
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  r600_cp_stop (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_ring_fini (struct radeon_device*,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_scratch_free (struct radeon_device*,int /*<<< orphan*/ ) ; 

void r600_cp_fini(struct radeon_device *rdev)
{
	struct radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	r600_cp_stop(rdev);
	radeon_ring_fini(rdev, ring);
	radeon_scratch_free(rdev, ring->rptr_save_reg);
}