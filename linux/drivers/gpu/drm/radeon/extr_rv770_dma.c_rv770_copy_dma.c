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
struct TYPE_3__ {int dma_ring_index; } ;
struct TYPE_4__ {TYPE_1__ copy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int DMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DMA_PACKET_COPY ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 struct radeon_fence* ERR_PTR (int) ; 
 unsigned int RADEON_GPU_PAGE_SHIFT ; 
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

struct radeon_fence *rv770_copy_dma(struct radeon_device *rdev,
				    uint64_t src_offset, uint64_t dst_offset,
				    unsigned num_gpu_pages,
				    struct dma_resv *resv)
{
	struct radeon_fence *fence;
	struct radeon_sync sync;
	int ring_index = rdev->asic->copy.dma_ring_index;
	struct radeon_ring *ring = &rdev->ring[ring_index];
	u32 size_in_dw, cur_size_in_dw;
	int i, num_loops;
	int r = 0;

	radeon_sync_create(&sync);

	size_in_dw = (num_gpu_pages << RADEON_GPU_PAGE_SHIFT) / 4;
	num_loops = DIV_ROUND_UP(size_in_dw, 0xFFFF);
	r = radeon_ring_lock(rdev, ring, num_loops * 5 + 8);
	if (r) {
		DRM_ERROR("radeon: moving bo (%d).\n", r);
		radeon_sync_free(rdev, &sync, NULL);
		return ERR_PTR(r);
	}

	radeon_sync_resv(rdev, &sync, resv, false);
	radeon_sync_rings(rdev, &sync, ring->idx);

	for (i = 0; i < num_loops; i++) {
		cur_size_in_dw = size_in_dw;
		if (cur_size_in_dw > 0xFFFF)
			cur_size_in_dw = 0xFFFF;
		size_in_dw -= cur_size_in_dw;
		radeon_ring_write(ring, DMA_PACKET(DMA_PACKET_COPY, 0, 0, cur_size_in_dw));
		radeon_ring_write(ring, dst_offset & 0xfffffffc);
		radeon_ring_write(ring, src_offset & 0xfffffffc);
		radeon_ring_write(ring, upper_32_bits(dst_offset) & 0xff);
		radeon_ring_write(ring, upper_32_bits(src_offset) & 0xff);
		src_offset += cur_size_in_dw * 4;
		dst_offset += cur_size_in_dw * 4;
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