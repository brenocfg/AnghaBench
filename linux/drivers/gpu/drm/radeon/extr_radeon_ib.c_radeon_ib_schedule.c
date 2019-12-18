#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct radeon_ring {int /*<<< orphan*/  ready; } ;
struct TYPE_4__ {int /*<<< orphan*/  last_vm_update; } ;
struct radeon_ib {size_t ring; int /*<<< orphan*/  fence; scalar_t__ vm; TYPE_1__ sync; int /*<<< orphan*/  length_dw; } ;
struct radeon_fence {int dummy; } ;
struct radeon_device {int /*<<< orphan*/  dev; struct radeon_ring* ring; } ;

/* Variables and functions */
 int EINVAL ; 
 int RADEON_NUM_SYNCS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int radeon_fence_emit (struct radeon_device*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  radeon_fence_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ring_ib_execute (struct radeon_device*,size_t,struct radeon_ib*) ; 
 int radeon_ring_lock (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_unlock_commit (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_unlock_undo (struct radeon_device*,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_sync_fence (TYPE_1__*,struct radeon_fence*) ; 
 int /*<<< orphan*/  radeon_sync_free (struct radeon_device*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int radeon_sync_rings (struct radeon_device*,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  radeon_vm_fence (struct radeon_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_vm_flush (struct radeon_device*,scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 struct radeon_fence* radeon_vm_grab_id (struct radeon_device*,scalar_t__,size_t) ; 

int radeon_ib_schedule(struct radeon_device *rdev, struct radeon_ib *ib,
		       struct radeon_ib *const_ib, bool hdp_flush)
{
	struct radeon_ring *ring = &rdev->ring[ib->ring];
	int r = 0;

	if (!ib->length_dw || !ring->ready) {
		/* TODO: Nothings in the ib we should report. */
		dev_err(rdev->dev, "couldn't schedule ib\n");
		return -EINVAL;
	}

	/* 64 dwords should be enough for fence too */
	r = radeon_ring_lock(rdev, ring, 64 + RADEON_NUM_SYNCS * 8);
	if (r) {
		dev_err(rdev->dev, "scheduling IB failed (%d).\n", r);
		return r;
	}

	/* grab a vm id if necessary */
	if (ib->vm) {
		struct radeon_fence *vm_id_fence;
		vm_id_fence = radeon_vm_grab_id(rdev, ib->vm, ib->ring);
		radeon_sync_fence(&ib->sync, vm_id_fence);
	}

	/* sync with other rings */
	r = radeon_sync_rings(rdev, &ib->sync, ib->ring);
	if (r) {
		dev_err(rdev->dev, "failed to sync rings (%d)\n", r);
		radeon_ring_unlock_undo(rdev, ring);
		return r;
	}

	if (ib->vm)
		radeon_vm_flush(rdev, ib->vm, ib->ring,
				ib->sync.last_vm_update);

	if (const_ib) {
		radeon_ring_ib_execute(rdev, const_ib->ring, const_ib);
		radeon_sync_free(rdev, &const_ib->sync, NULL);
	}
	radeon_ring_ib_execute(rdev, ib->ring, ib);
	r = radeon_fence_emit(rdev, &ib->fence, ib->ring);
	if (r) {
		dev_err(rdev->dev, "failed to emit fence for new IB (%d)\n", r);
		radeon_ring_unlock_undo(rdev, ring);
		return r;
	}
	if (const_ib) {
		const_ib->fence = radeon_fence_ref(ib->fence);
	}

	if (ib->vm)
		radeon_vm_fence(rdev, ib->vm, ib->fence);

	radeon_ring_unlock_commit(rdev, ring, hdp_flush);
	return 0;
}