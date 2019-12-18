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
struct radeon_ring {int /*<<< orphan*/  ready; } ;
struct radeon_device {struct radeon_ring* ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,int,int,...) ; 
 int RADEON_NUM_RINGS ; 
 int /*<<< orphan*/  radeon_test_ring_sync (struct radeon_device*,struct radeon_ring*,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_test_ring_sync2 (struct radeon_device*,struct radeon_ring*,struct radeon_ring*,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_test_sync_possible (struct radeon_ring*,struct radeon_ring*) ; 

void radeon_test_syncing(struct radeon_device *rdev)
{
	int i, j, k;

	for (i = 1; i < RADEON_NUM_RINGS; ++i) {
		struct radeon_ring *ringA = &rdev->ring[i];
		if (!ringA->ready)
			continue;

		for (j = 0; j < i; ++j) {
			struct radeon_ring *ringB = &rdev->ring[j];
			if (!ringB->ready)
				continue;

			if (!radeon_test_sync_possible(ringA, ringB))
				continue;

			DRM_INFO("Testing syncing between rings %d and %d...\n", i, j);
			radeon_test_ring_sync(rdev, ringA, ringB);

			DRM_INFO("Testing syncing between rings %d and %d...\n", j, i);
			radeon_test_ring_sync(rdev, ringB, ringA);

			for (k = 0; k < j; ++k) {
				struct radeon_ring *ringC = &rdev->ring[k];
				if (!ringC->ready)
					continue;

				if (!radeon_test_sync_possible(ringA, ringC))
					continue;

				if (!radeon_test_sync_possible(ringB, ringC))
					continue;

				DRM_INFO("Testing syncing between rings %d, %d and %d...\n", i, j, k);
				radeon_test_ring_sync2(rdev, ringA, ringB, ringC);

				DRM_INFO("Testing syncing between rings %d, %d and %d...\n", i, k, j);
				radeon_test_ring_sync2(rdev, ringA, ringC, ringB);

				DRM_INFO("Testing syncing between rings %d, %d and %d...\n", j, i, k);
				radeon_test_ring_sync2(rdev, ringB, ringA, ringC);

				DRM_INFO("Testing syncing between rings %d, %d and %d...\n", j, k, i);
				radeon_test_ring_sync2(rdev, ringB, ringC, ringA);

				DRM_INFO("Testing syncing between rings %d, %d and %d...\n", k, i, j);
				radeon_test_ring_sync2(rdev, ringC, ringA, ringB);

				DRM_INFO("Testing syncing between rings %d, %d and %d...\n", k, j, i);
				radeon_test_ring_sync2(rdev, ringC, ringB, ringA);
			}
		}
	}
}