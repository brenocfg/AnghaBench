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
 int DIV_ROUND_UP (unsigned int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,unsigned int) ; 
 int EINVAL ; 
 struct radeon_fence* ERR_PTR (int) ; 
 int PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_BITBLT_MULTI ; 
 int RADEON_COLOR_FORMAT_ARGB8888 ; 
 int RADEON_DP_SRC_SOURCE_MEMORY ; 
 int /*<<< orphan*/  RADEON_DSTCACHE_CTLSTAT ; 
 int RADEON_GMC_BRUSH_NONE ; 
 int RADEON_GMC_CLR_CMP_CNTL_DIS ; 
 int RADEON_GMC_DST_CLIPPING ; 
 int RADEON_GMC_DST_PITCH_OFFSET_CNTL ; 
 int RADEON_GMC_SRC_CLIPPING ; 
 int RADEON_GMC_SRC_DATATYPE_COLOR ; 
 int RADEON_GMC_SRC_PITCH_OFFSET_CNTL ; 
 int RADEON_GMC_WR_MSK_DIS ; 
 int RADEON_GPU_PAGE_SIZE ; 
 int RADEON_RB2D_DC_FLUSH_ALL ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int RADEON_ROP3_S ; 
 int RADEON_WAIT_2D_IDLECLEAN ; 
 int RADEON_WAIT_DMA_GUI_IDLE ; 
 int RADEON_WAIT_HOST_IDLECLEAN ; 
 int /*<<< orphan*/  RADEON_WAIT_UNTIL ; 
 int radeon_fence_emit (struct radeon_device*,struct radeon_fence**,size_t) ; 
 int radeon_ring_lock (struct radeon_device*,struct radeon_ring*,unsigned int) ; 
 int /*<<< orphan*/  radeon_ring_unlock_commit (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_unlock_undo (struct radeon_device*,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 

struct radeon_fence *r100_copy_blit(struct radeon_device *rdev,
				    uint64_t src_offset,
				    uint64_t dst_offset,
				    unsigned num_gpu_pages,
				    struct dma_resv *resv)
{
	struct radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	struct radeon_fence *fence;
	uint32_t cur_pages;
	uint32_t stride_bytes = RADEON_GPU_PAGE_SIZE;
	uint32_t pitch;
	uint32_t stride_pixels;
	unsigned ndw;
	int num_loops;
	int r = 0;

	/* radeon limited to 16k stride */
	stride_bytes &= 0x3fff;
	/* radeon pitch is /64 */
	pitch = stride_bytes / 64;
	stride_pixels = stride_bytes / 4;
	num_loops = DIV_ROUND_UP(num_gpu_pages, 8191);

	/* Ask for enough room for blit + flush + fence */
	ndw = 64 + (10 * num_loops);
	r = radeon_ring_lock(rdev, ring, ndw);
	if (r) {
		DRM_ERROR("radeon: moving bo (%d) asking for %u dw.\n", r, ndw);
		return ERR_PTR(-EINVAL);
	}
	while (num_gpu_pages > 0) {
		cur_pages = num_gpu_pages;
		if (cur_pages > 8191) {
			cur_pages = 8191;
		}
		num_gpu_pages -= cur_pages;

		/* pages are in Y direction - height
		   page width in X direction - width */
		radeon_ring_write(ring, PACKET3(PACKET3_BITBLT_MULTI, 8));
		radeon_ring_write(ring,
				  RADEON_GMC_SRC_PITCH_OFFSET_CNTL |
				  RADEON_GMC_DST_PITCH_OFFSET_CNTL |
				  RADEON_GMC_SRC_CLIPPING |
				  RADEON_GMC_DST_CLIPPING |
				  RADEON_GMC_BRUSH_NONE |
				  (RADEON_COLOR_FORMAT_ARGB8888 << 8) |
				  RADEON_GMC_SRC_DATATYPE_COLOR |
				  RADEON_ROP3_S |
				  RADEON_DP_SRC_SOURCE_MEMORY |
				  RADEON_GMC_CLR_CMP_CNTL_DIS |
				  RADEON_GMC_WR_MSK_DIS);
		radeon_ring_write(ring, (pitch << 22) | (src_offset >> 10));
		radeon_ring_write(ring, (pitch << 22) | (dst_offset >> 10));
		radeon_ring_write(ring, (0x1fff) | (0x1fff << 16));
		radeon_ring_write(ring, 0);
		radeon_ring_write(ring, (0x1fff) | (0x1fff << 16));
		radeon_ring_write(ring, num_gpu_pages);
		radeon_ring_write(ring, num_gpu_pages);
		radeon_ring_write(ring, cur_pages | (stride_pixels << 16));
	}
	radeon_ring_write(ring, PACKET0(RADEON_DSTCACHE_CTLSTAT, 0));
	radeon_ring_write(ring, RADEON_RB2D_DC_FLUSH_ALL);
	radeon_ring_write(ring, PACKET0(RADEON_WAIT_UNTIL, 0));
	radeon_ring_write(ring,
			  RADEON_WAIT_2D_IDLECLEAN |
			  RADEON_WAIT_HOST_IDLECLEAN |
			  RADEON_WAIT_DMA_GUI_IDLE);
	r = radeon_fence_emit(rdev, &fence, RADEON_RING_TYPE_GFX_INDEX);
	if (r) {
		radeon_ring_unlock_undo(rdev, ring);
		return ERR_PTR(r);
	}
	radeon_ring_unlock_commit(rdev, ring, false);
	return fence;
}