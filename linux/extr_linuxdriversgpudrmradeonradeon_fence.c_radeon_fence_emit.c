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
typedef  scalar_t__ u64 ;
struct radeon_fence {int ring; int is_vm_update; scalar_t__ seq; int /*<<< orphan*/  base; struct radeon_device* rdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct radeon_device {int /*<<< orphan*/  ddev; scalar_t__ fence_context; TYPE_2__ fence_queue; TYPE_1__* fence_drv; } ;
struct TYPE_3__ {scalar_t__* sync_seq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_fence_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 struct radeon_fence* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_fence_ops ; 
 int /*<<< orphan*/  radeon_fence_ring_emit (struct radeon_device*,int,struct radeon_fence*) ; 
 int /*<<< orphan*/  radeon_fence_schedule_check (struct radeon_device*,int) ; 
 int /*<<< orphan*/  trace_radeon_fence_emit (int /*<<< orphan*/ ,int,scalar_t__) ; 

int radeon_fence_emit(struct radeon_device *rdev,
		      struct radeon_fence **fence,
		      int ring)
{
	u64 seq;

	/* we are protected by the ring emission mutex */
	*fence = kmalloc(sizeof(struct radeon_fence), GFP_KERNEL);
	if ((*fence) == NULL) {
		return -ENOMEM;
	}
	(*fence)->rdev = rdev;
	(*fence)->seq = seq = ++rdev->fence_drv[ring].sync_seq[ring];
	(*fence)->ring = ring;
	(*fence)->is_vm_update = false;
	dma_fence_init(&(*fence)->base, &radeon_fence_ops,
		       &rdev->fence_queue.lock,
		       rdev->fence_context + ring,
		       seq);
	radeon_fence_ring_emit(rdev, ring, *fence);
	trace_radeon_fence_emit(rdev->ddev, ring, (*fence)->seq);
	radeon_fence_schedule_check(rdev, ring);
	return 0;
}