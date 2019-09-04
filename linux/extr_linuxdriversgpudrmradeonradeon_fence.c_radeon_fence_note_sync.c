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
struct radeon_fence_driver {int /*<<< orphan*/ * sync_seq; } ;
struct radeon_fence {int ring; TYPE_1__* rdev; } ;
struct TYPE_2__ {struct radeon_fence_driver* fence_drv; } ;

/* Variables and functions */
 unsigned int RADEON_NUM_RINGS ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void radeon_fence_note_sync(struct radeon_fence *fence, int dst_ring)
{
	struct radeon_fence_driver *dst, *src;
	unsigned i;

	if (!fence) {
		return;
	}

	if (fence->ring == dst_ring) {
		return;
	}

	/* we are protected by the ring mutex */
	src = &fence->rdev->fence_drv[fence->ring];
	dst = &fence->rdev->fence_drv[dst_ring];
	for (i = 0; i < RADEON_NUM_RINGS; ++i) {
		if (i == dst_ring) {
			continue;
		}
		dst->sync_seq[i] = max(dst->sync_seq[i], src->sync_seq[i]);
	}
}