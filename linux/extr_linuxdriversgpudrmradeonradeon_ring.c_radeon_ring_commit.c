#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct radeon_ring {size_t idx; int wptr; int align_mask; int /*<<< orphan*/  nop; } ;
struct radeon_device {TYPE_2__* asic; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* mmio_hdp_flush ) (struct radeon_device*) ;TYPE_1__** ring; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* hdp_flush ) (struct radeon_device*,struct radeon_ring*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  radeon_ring_set_wptr (struct radeon_device*,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct radeon_device*,struct radeon_ring*) ; 
 int /*<<< orphan*/  stub2 (struct radeon_device*) ; 

void radeon_ring_commit(struct radeon_device *rdev, struct radeon_ring *ring,
			bool hdp_flush)
{
	/* If we are emitting the HDP flush via the ring buffer, we need to
	 * do it before padding.
	 */
	if (hdp_flush && rdev->asic->ring[ring->idx]->hdp_flush)
		rdev->asic->ring[ring->idx]->hdp_flush(rdev, ring);
	/* We pad to match fetch size */
	while (ring->wptr & ring->align_mask) {
		radeon_ring_write(ring, ring->nop);
	}
	mb();
	/* If we are emitting the HDP flush via MMIO, we need to do it after
	 * all CPU writes to VRAM finished.
	 */
	if (hdp_flush && rdev->asic->mmio_hdp_flush)
		rdev->asic->mmio_hdp_flush(rdev);
	radeon_ring_set_wptr(rdev, ring);
}