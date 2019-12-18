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
typedef  int u32 ;
struct bgmac_dma_ring {scalar_t__ mmio_base; } ;
struct bgmac {int feature_flags; } ;

/* Variables and functions */
 int BGMAC_DMA_RX_ADDREXT_MASK ; 
 int BGMAC_DMA_RX_BL_128 ; 
 int BGMAC_DMA_RX_BL_MASK ; 
 int BGMAC_DMA_RX_BL_SHIFT ; 
 scalar_t__ BGMAC_DMA_RX_CTL ; 
 int BGMAC_DMA_RX_ENABLE ; 
 int BGMAC_DMA_RX_FRAME_OFFSET_SHIFT ; 
 int BGMAC_DMA_RX_OVERFLOW_CONT ; 
 int BGMAC_DMA_RX_PARITY_DISABLE ; 
 int BGMAC_DMA_RX_PC_8 ; 
 int BGMAC_DMA_RX_PC_MASK ; 
 int BGMAC_DMA_RX_PC_SHIFT ; 
 int BGMAC_DMA_RX_PT_1 ; 
 int BGMAC_DMA_RX_PT_MASK ; 
 int BGMAC_DMA_RX_PT_SHIFT ; 
 int BGMAC_FEAT_RX_MASK_SETUP ; 
 int BGMAC_RX_FRAME_OFFSET ; 
 int bgmac_read (struct bgmac*,scalar_t__) ; 
 int /*<<< orphan*/  bgmac_write (struct bgmac*,scalar_t__,int) ; 

__attribute__((used)) static void bgmac_dma_rx_enable(struct bgmac *bgmac,
				struct bgmac_dma_ring *ring)
{
	u32 ctl;

	ctl = bgmac_read(bgmac, ring->mmio_base + BGMAC_DMA_RX_CTL);

	/* preserve ONLY bits 16-17 from current hardware value */
	ctl &= BGMAC_DMA_RX_ADDREXT_MASK;

	if (bgmac->feature_flags & BGMAC_FEAT_RX_MASK_SETUP) {
		ctl &= ~BGMAC_DMA_RX_BL_MASK;
		ctl |= BGMAC_DMA_RX_BL_128 << BGMAC_DMA_RX_BL_SHIFT;

		ctl &= ~BGMAC_DMA_RX_PC_MASK;
		ctl |= BGMAC_DMA_RX_PC_8 << BGMAC_DMA_RX_PC_SHIFT;

		ctl &= ~BGMAC_DMA_RX_PT_MASK;
		ctl |= BGMAC_DMA_RX_PT_1 << BGMAC_DMA_RX_PT_SHIFT;
	}
	ctl |= BGMAC_DMA_RX_ENABLE;
	ctl |= BGMAC_DMA_RX_PARITY_DISABLE;
	ctl |= BGMAC_DMA_RX_OVERFLOW_CONT;
	ctl |= BGMAC_RX_FRAME_OFFSET << BGMAC_DMA_RX_FRAME_OFFSET_SHIFT;
	bgmac_write(bgmac, ring->mmio_base + BGMAC_DMA_RX_CTL, ctl);
}