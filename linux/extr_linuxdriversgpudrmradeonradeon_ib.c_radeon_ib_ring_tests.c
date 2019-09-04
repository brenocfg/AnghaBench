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
struct radeon_ring {int ready; } ;
struct radeon_device {int needs_reset; int accel_working; struct radeon_ring* ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int,...) ; 
 unsigned int RADEON_NUM_RINGS ; 
 unsigned int RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  radeon_fence_driver_force_completion (struct radeon_device*,unsigned int) ; 
 int radeon_ib_test (struct radeon_device*,unsigned int,struct radeon_ring*) ; 

int radeon_ib_ring_tests(struct radeon_device *rdev)
{
	unsigned i;
	int r;

	for (i = 0; i < RADEON_NUM_RINGS; ++i) {
		struct radeon_ring *ring = &rdev->ring[i];

		if (!ring->ready)
			continue;

		r = radeon_ib_test(rdev, i, ring);
		if (r) {
			radeon_fence_driver_force_completion(rdev, i);
			ring->ready = false;
			rdev->needs_reset = false;

			if (i == RADEON_RING_TYPE_GFX_INDEX) {
				/* oh, oh, that's really bad */
				DRM_ERROR("radeon: failed testing IB on GFX ring (%d).\n", r);
				rdev->accel_working = false;
				return r;

			} else {
				/* still not good, but we can live with it */
				DRM_ERROR("radeon: failed testing IB on ring %d (%d).\n", i, r);
			}
		}
	}
	return 0;
}