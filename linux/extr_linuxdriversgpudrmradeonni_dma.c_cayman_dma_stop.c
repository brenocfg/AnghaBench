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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  visible_vram_size; } ;
struct radeon_device {TYPE_2__* ring; TYPE_1__ mc; TYPE_4__* asic; } ;
struct TYPE_7__ {size_t copy_ring_index; } ;
struct TYPE_8__ {TYPE_3__ copy; } ;
struct TYPE_6__ {int ready; } ;

/* Variables and functions */
 size_t CAYMAN_RING_TYPE_DMA1_INDEX ; 
 scalar_t__ DMA0_REGISTER_OFFSET ; 
 scalar_t__ DMA1_REGISTER_OFFSET ; 
 scalar_t__ DMA_RB_CNTL ; 
 int /*<<< orphan*/  DMA_RB_ENABLE ; 
 size_t R600_RING_TYPE_DMA_INDEX ; 
 int /*<<< orphan*/  RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ttm_set_active_vram_size (struct radeon_device*,int /*<<< orphan*/ ) ; 

void cayman_dma_stop(struct radeon_device *rdev)
{
	u32 rb_cntl;

	if ((rdev->asic->copy.copy_ring_index == R600_RING_TYPE_DMA_INDEX) ||
	    (rdev->asic->copy.copy_ring_index == CAYMAN_RING_TYPE_DMA1_INDEX))
		radeon_ttm_set_active_vram_size(rdev, rdev->mc.visible_vram_size);

	/* dma0 */
	rb_cntl = RREG32(DMA_RB_CNTL + DMA0_REGISTER_OFFSET);
	rb_cntl &= ~DMA_RB_ENABLE;
	WREG32(DMA_RB_CNTL + DMA0_REGISTER_OFFSET, rb_cntl);

	/* dma1 */
	rb_cntl = RREG32(DMA_RB_CNTL + DMA1_REGISTER_OFFSET);
	rb_cntl &= ~DMA_RB_ENABLE;
	WREG32(DMA_RB_CNTL + DMA1_REGISTER_OFFSET, rb_cntl);

	rdev->ring[R600_RING_TYPE_DMA_INDEX].ready = false;
	rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX].ready = false;
}