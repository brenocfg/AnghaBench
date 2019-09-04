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
typedef  int uint32_t ;
struct radeon_ring {int ring_free_dw; int ring_size; int wptr; int ptr_mask; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int radeon_ring_get_rptr (struct radeon_device*,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_ring_lockup_update (struct radeon_device*,struct radeon_ring*) ; 

void radeon_ring_free_size(struct radeon_device *rdev, struct radeon_ring *ring)
{
	uint32_t rptr = radeon_ring_get_rptr(rdev, ring);

	/* This works because ring_size is a power of 2 */
	ring->ring_free_dw = rptr + (ring->ring_size / 4);
	ring->ring_free_dw -= ring->wptr;
	ring->ring_free_dw &= ring->ptr_mask;
	if (!ring->ring_free_dw) {
		/* this is an empty ring */
		ring->ring_free_dw = ring->ring_size / 4;
		/*  update lockup info to avoid false positive */
		radeon_ring_lockup_update(rdev, ring);
	}
}