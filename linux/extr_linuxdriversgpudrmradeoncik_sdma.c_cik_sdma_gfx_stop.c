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
struct TYPE_7__ {int /*<<< orphan*/  visible_vram_size; } ;
struct radeon_device {TYPE_4__* ring; TYPE_3__ mc; TYPE_2__* asic; } ;
struct TYPE_8__ {int ready; } ;
struct TYPE_5__ {size_t copy_ring_index; } ;
struct TYPE_6__ {TYPE_1__ copy; } ;

/* Variables and functions */
 size_t CAYMAN_RING_TYPE_DMA1_INDEX ; 
 size_t R600_RING_TYPE_DMA_INDEX ; 
 int RREG32 (int) ; 
 int SDMA0_GFX_IB_CNTL ; 
 int SDMA0_GFX_RB_CNTL ; 
 int SDMA0_REGISTER_OFFSET ; 
 int SDMA1_REGISTER_OFFSET ; 
 int SDMA_RB_ENABLE ; 
 int SOFT_RESET_SDMA ; 
 int SOFT_RESET_SDMA1 ; 
 int SRBM_SOFT_RESET ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  radeon_ttm_set_active_vram_size (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void cik_sdma_gfx_stop(struct radeon_device *rdev)
{
	u32 rb_cntl, reg_offset;
	int i;

	if ((rdev->asic->copy.copy_ring_index == R600_RING_TYPE_DMA_INDEX) ||
	    (rdev->asic->copy.copy_ring_index == CAYMAN_RING_TYPE_DMA1_INDEX))
		radeon_ttm_set_active_vram_size(rdev, rdev->mc.visible_vram_size);

	for (i = 0; i < 2; i++) {
		if (i == 0)
			reg_offset = SDMA0_REGISTER_OFFSET;
		else
			reg_offset = SDMA1_REGISTER_OFFSET;
		rb_cntl = RREG32(SDMA0_GFX_RB_CNTL + reg_offset);
		rb_cntl &= ~SDMA_RB_ENABLE;
		WREG32(SDMA0_GFX_RB_CNTL + reg_offset, rb_cntl);
		WREG32(SDMA0_GFX_IB_CNTL + reg_offset, 0);
	}
	rdev->ring[R600_RING_TYPE_DMA_INDEX].ready = false;
	rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX].ready = false;

	/* FIXME use something else than big hammer but after few days can not
	 * seem to find good combination so reset SDMA blocks as it seems we
	 * do not shut them down properly. This fix hibernation and does not
	 * affect suspend to ram.
	 */
	WREG32(SRBM_SOFT_RESET, SOFT_RESET_SDMA | SOFT_RESET_SDMA1);
	(void)RREG32(SRBM_SOFT_RESET);
	udelay(50);
	WREG32(SRBM_SOFT_RESET, 0);
	(void)RREG32(SRBM_SOFT_RESET);
}