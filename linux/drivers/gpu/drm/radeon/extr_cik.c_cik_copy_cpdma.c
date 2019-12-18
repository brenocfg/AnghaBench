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
typedef  int uint64_t ;
typedef  int u32 ;
struct radeon_sync {int dummy; } ;
struct radeon_ring {int /*<<< orphan*/  idx; } ;
struct radeon_fence {int dummy; } ;
struct radeon_device {struct radeon_ring* ring; TYPE_2__* asic; } ;
struct dma_resv {int dummy; } ;
struct TYPE_3__ {int blit_ring_index; } ;
struct TYPE_4__ {TYPE_1__ copy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 struct radeon_fence* ERR_PTR (int) ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_DMA_DATA ; 
 int PACKET3_DMA_DATA_CP_SYNC ; 
 unsigned int RADEON_GPU_PAGE_SHIFT ; 
 int lower_32_bits (int) ; 
 int radeon_fence_emit (struct radeon_device*,struct radeon_fence**,int /*<<< orphan*/ ) ; 
 int radeon_ring_lock (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_unlock_commit (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_unlock_undo (struct radeon_device*,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_sync_create (struct radeon_sync*) ; 
 int /*<<< orphan*/  radeon_sync_free (struct radeon_device*,struct radeon_sync*,struct radeon_fence*) ; 
 int /*<<< orphan*/  radeon_sync_resv (struct radeon_device*,struct radeon_sync*,struct dma_resv*,int) ; 
 int /*<<< orphan*/  radeon_sync_rings (struct radeon_device*,struct radeon_sync*,int /*<<< orphan*/ ) ; 
 int upper_32_bits (int) ; 

struct radeon_fence *cik_copy_cpdma(struct radeon_device *rdev,
				    uint64_t src_offset, uint64_t dst_offset,
				    unsigned num_gpu_pages,
				    struct dma_resv *resv)
{
	struct radeon_fence *fence;
	struct radeon_sync sync;
	int ring_index = rdev->asic->copy.blit_ring_index;
	struct radeon_ring *ring = &rdev->ring[ring_index];
	u32 size_in_bytes, cur_size_in_bytes, control;
	int i, num_loops;
	int r = 0;

	radeon_sync_create(&sync);

	size_in_bytes = (num_gpu_pages << RADEON_GPU_PAGE_SHIFT);
	num_loops = DIV_ROUND_UP(size_in_bytes, 0x1fffff);
	r = radeon_ring_lock(rdev, ring, num_loops * 7 + 18);
	if (r) {
		DRM_ERROR("radeon: moving bo (%d).\n", r);
		radeon_sync_free(rdev, &sync, NULL);
		return ERR_PTR(r);
	}

	radeon_sync_resv(rdev, &sync, resv, false);
	radeon_sync_rings(rdev, &sync, ring->idx);

	for (i = 0; i < num_loops; i++) {
		cur_size_in_bytes = size_in_bytes;
		if (cur_size_in_bytes > 0x1fffff)
			cur_size_in_bytes = 0x1fffff;
		size_in_bytes -= cur_size_in_bytes;
		control = 0;
		if (size_in_bytes == 0)
			control |= PACKET3_DMA_DATA_CP_SYNC;
		radeon_ring_write(ring, PACKET3(PACKET3_DMA_DATA, 5));
		radeon_ring_write(ring, control);
		radeon_ring_write(ring, lower_32_bits(src_offset));
		radeon_ring_write(ring, upper_32_bits(src_offset));
		radeon_ring_write(ring, lower_32_bits(dst_offset));
		radeon_ring_write(ring, upper_32_bits(dst_offset));
		radeon_ring_write(ring, cur_size_in_bytes);
		src_offset += cur_size_in_bytes;
		dst_offset += cur_size_in_bytes;
	}

	r = radeon_fence_emit(rdev, &fence, ring->idx);
	if (r) {
		radeon_ring_unlock_undo(rdev, ring);
		radeon_sync_free(rdev, &sync, NULL);
		return ERR_PTR(r);
	}

	radeon_ring_unlock_commit(rdev, ring, false);
	radeon_sync_free(rdev, &sync, fence);

	return fence;
}