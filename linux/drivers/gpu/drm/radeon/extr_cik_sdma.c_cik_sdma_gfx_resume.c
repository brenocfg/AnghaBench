#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct radeon_ring {int ring_size; int gpu_addr; int wptr; int ready; int /*<<< orphan*/  idx; } ;
struct TYPE_8__ {int /*<<< orphan*/  real_vram_size; } ;
struct TYPE_5__ {int gpu_addr; scalar_t__ enabled; } ;
struct radeon_device {TYPE_4__ mc; TYPE_3__* asic; TYPE_1__ wb; struct radeon_ring* ring; } ;
struct TYPE_6__ {size_t copy_ring_index; } ;
struct TYPE_7__ {TYPE_2__ copy; } ;

/* Variables and functions */
 size_t CAYMAN_RING_TYPE_DMA1_INDEX ; 
 int CAYMAN_WB_DMA1_RPTR_OFFSET ; 
 size_t R600_RING_TYPE_DMA_INDEX ; 
 int R600_WB_DMA_RPTR_OFFSET ; 
 int SDMA0_GFX_IB_CNTL ; 
 int SDMA0_GFX_RB_BASE ; 
 int SDMA0_GFX_RB_BASE_HI ; 
 int SDMA0_GFX_RB_CNTL ; 
 int SDMA0_GFX_RB_RPTR ; 
 int SDMA0_GFX_RB_RPTR_ADDR_HI ; 
 int SDMA0_GFX_RB_RPTR_ADDR_LO ; 
 int SDMA0_GFX_RB_WPTR ; 
 int SDMA0_REGISTER_OFFSET ; 
 int SDMA0_SEM_INCOMPLETE_TIMER_CNTL ; 
 int SDMA0_SEM_WAIT_FAIL_TIMER_CNTL ; 
 int SDMA1_REGISTER_OFFSET ; 
 int SDMA_IB_ENABLE ; 
 int SDMA_IB_SWAP_ENABLE ; 
 int SDMA_RB_ENABLE ; 
 int SDMA_RB_SWAP_ENABLE ; 
 int SDMA_RPTR_WRITEBACK_ENABLE ; 
 int SDMA_RPTR_WRITEBACK_SWAP_ENABLE ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int order_base_2 (int) ; 
 int radeon_ring_test (struct radeon_device*,int /*<<< orphan*/ ,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_ttm_set_active_vram_size (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static int cik_sdma_gfx_resume(struct radeon_device *rdev)
{
	struct radeon_ring *ring;
	u32 rb_cntl, ib_cntl;
	u32 rb_bufsz;
	u32 reg_offset, wb_offset;
	int i, r;

	for (i = 0; i < 2; i++) {
		if (i == 0) {
			ring = &rdev->ring[R600_RING_TYPE_DMA_INDEX];
			reg_offset = SDMA0_REGISTER_OFFSET;
			wb_offset = R600_WB_DMA_RPTR_OFFSET;
		} else {
			ring = &rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX];
			reg_offset = SDMA1_REGISTER_OFFSET;
			wb_offset = CAYMAN_WB_DMA1_RPTR_OFFSET;
		}

		WREG32(SDMA0_SEM_INCOMPLETE_TIMER_CNTL + reg_offset, 0);
		WREG32(SDMA0_SEM_WAIT_FAIL_TIMER_CNTL + reg_offset, 0);

		/* Set ring buffer size in dwords */
		rb_bufsz = order_base_2(ring->ring_size / 4);
		rb_cntl = rb_bufsz << 1;
#ifdef __BIG_ENDIAN
		rb_cntl |= SDMA_RB_SWAP_ENABLE | SDMA_RPTR_WRITEBACK_SWAP_ENABLE;
#endif
		WREG32(SDMA0_GFX_RB_CNTL + reg_offset, rb_cntl);

		/* Initialize the ring buffer's read and write pointers */
		WREG32(SDMA0_GFX_RB_RPTR + reg_offset, 0);
		WREG32(SDMA0_GFX_RB_WPTR + reg_offset, 0);

		/* set the wb address whether it's enabled or not */
		WREG32(SDMA0_GFX_RB_RPTR_ADDR_HI + reg_offset,
		       upper_32_bits(rdev->wb.gpu_addr + wb_offset) & 0xFFFFFFFF);
		WREG32(SDMA0_GFX_RB_RPTR_ADDR_LO + reg_offset,
		       ((rdev->wb.gpu_addr + wb_offset) & 0xFFFFFFFC));

		if (rdev->wb.enabled)
			rb_cntl |= SDMA_RPTR_WRITEBACK_ENABLE;

		WREG32(SDMA0_GFX_RB_BASE + reg_offset, ring->gpu_addr >> 8);
		WREG32(SDMA0_GFX_RB_BASE_HI + reg_offset, ring->gpu_addr >> 40);

		ring->wptr = 0;
		WREG32(SDMA0_GFX_RB_WPTR + reg_offset, ring->wptr << 2);

		/* enable DMA RB */
		WREG32(SDMA0_GFX_RB_CNTL + reg_offset, rb_cntl | SDMA_RB_ENABLE);

		ib_cntl = SDMA_IB_ENABLE;
#ifdef __BIG_ENDIAN
		ib_cntl |= SDMA_IB_SWAP_ENABLE;
#endif
		/* enable DMA IBs */
		WREG32(SDMA0_GFX_IB_CNTL + reg_offset, ib_cntl);

		ring->ready = true;

		r = radeon_ring_test(rdev, ring->idx, ring);
		if (r) {
			ring->ready = false;
			return r;
		}
	}

	if ((rdev->asic->copy.copy_ring_index == R600_RING_TYPE_DMA_INDEX) ||
	    (rdev->asic->copy.copy_ring_index == CAYMAN_RING_TYPE_DMA1_INDEX))
		radeon_ttm_set_active_vram_size(rdev, rdev->mc.real_vram_size);

	return 0;
}