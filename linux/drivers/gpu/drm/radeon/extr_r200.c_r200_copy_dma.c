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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct radeon_ring {int dummy; } ;
struct radeon_fence {int dummy; } ;
struct radeon_device {struct radeon_ring* ring; } ;
struct dma_resv {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 struct radeon_fence* ERR_PTR (int) ; 
 int PACKET0 (int,int) ; 
 unsigned int RADEON_GPU_PAGE_SHIFT ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int RADEON_WAIT_DMA_GUI_IDLE ; 
 int RADEON_WAIT_UNTIL ; 
 int radeon_fence_emit (struct radeon_device*,struct radeon_fence**,size_t) ; 
 int radeon_ring_lock (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_unlock_commit (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_unlock_undo (struct radeon_device*,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 

struct radeon_fence *r200_copy_dma(struct radeon_device *rdev,
				   uint64_t src_offset,
				   uint64_t dst_offset,
				   unsigned num_gpu_pages,
				   struct dma_resv *resv)
{
	struct radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	struct radeon_fence *fence;
	uint32_t size;
	uint32_t cur_size;
	int i, num_loops;
	int r = 0;

	/* radeon pitch is /64 */
	size = num_gpu_pages << RADEON_GPU_PAGE_SHIFT;
	num_loops = DIV_ROUND_UP(size, 0x1FFFFF);
	r = radeon_ring_lock(rdev, ring, num_loops * 4 + 64);
	if (r) {
		DRM_ERROR("radeon: moving bo (%d).\n", r);
		return ERR_PTR(r);
	}
	/* Must wait for 2D idle & clean before DMA or hangs might happen */
	radeon_ring_write(ring, PACKET0(RADEON_WAIT_UNTIL, 0));
	radeon_ring_write(ring, (1 << 16));
	for (i = 0; i < num_loops; i++) {
		cur_size = size;
		if (cur_size > 0x1FFFFF) {
			cur_size = 0x1FFFFF;
		}
		size -= cur_size;
		radeon_ring_write(ring, PACKET0(0x720, 2));
		radeon_ring_write(ring, src_offset);
		radeon_ring_write(ring, dst_offset);
		radeon_ring_write(ring, cur_size | (1 << 31) | (1 << 30));
		src_offset += cur_size;
		dst_offset += cur_size;
	}
	radeon_ring_write(ring, PACKET0(RADEON_WAIT_UNTIL, 0));
	radeon_ring_write(ring, RADEON_WAIT_DMA_GUI_IDLE);
	r = radeon_fence_emit(rdev, &fence, RADEON_RING_TYPE_GFX_INDEX);
	if (r) {
		radeon_ring_unlock_undo(rdev, ring);
		return ERR_PTR(r);
	}
	radeon_ring_unlock_commit(rdev, ring, false);
	return fence;
}