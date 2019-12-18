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
struct radeon_ring {int ring_size; unsigned int align_mask; int ring_free_dw; unsigned int count_dw; int /*<<< orphan*/  wptr; int /*<<< orphan*/  wptr_old; int /*<<< orphan*/  idx; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int radeon_fence_wait_next (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ring_free_size (struct radeon_device*,struct radeon_ring*) ; 

int radeon_ring_alloc(struct radeon_device *rdev, struct radeon_ring *ring, unsigned ndw)
{
	int r;

	/* make sure we aren't trying to allocate more space than there is on the ring */
	if (ndw > (ring->ring_size / 4))
		return -ENOMEM;
	/* Align requested size with padding so unlock_commit can
	 * pad safely */
	radeon_ring_free_size(rdev, ring);
	ndw = (ndw + ring->align_mask) & ~ring->align_mask;
	while (ndw > (ring->ring_free_dw - 1)) {
		radeon_ring_free_size(rdev, ring);
		if (ndw < ring->ring_free_dw) {
			break;
		}
		r = radeon_fence_wait_next(rdev, ring->idx);
		if (r)
			return r;
	}
	ring->count_dw = ndw;
	ring->wptr_old = ring->wptr;
	return 0;
}