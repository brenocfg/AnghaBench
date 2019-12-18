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
 int BGMAC_DMA_TX_BL_128 ; 
 int BGMAC_DMA_TX_BL_MASK ; 
 int BGMAC_DMA_TX_BL_SHIFT ; 
 scalar_t__ BGMAC_DMA_TX_CTL ; 
 int BGMAC_DMA_TX_ENABLE ; 
 int BGMAC_DMA_TX_MR_2 ; 
 int BGMAC_DMA_TX_MR_MASK ; 
 int BGMAC_DMA_TX_MR_SHIFT ; 
 int BGMAC_DMA_TX_PARITY_DISABLE ; 
 int BGMAC_DMA_TX_PC_16 ; 
 int BGMAC_DMA_TX_PC_MASK ; 
 int BGMAC_DMA_TX_PC_SHIFT ; 
 int BGMAC_DMA_TX_PT_8 ; 
 int BGMAC_DMA_TX_PT_MASK ; 
 int BGMAC_DMA_TX_PT_SHIFT ; 
 int BGMAC_FEAT_TX_MASK_SETUP ; 
 int bgmac_read (struct bgmac*,scalar_t__) ; 
 int /*<<< orphan*/  bgmac_write (struct bgmac*,scalar_t__,int) ; 

__attribute__((used)) static void bgmac_dma_tx_enable(struct bgmac *bgmac,
				struct bgmac_dma_ring *ring)
{
	u32 ctl;

	ctl = bgmac_read(bgmac, ring->mmio_base + BGMAC_DMA_TX_CTL);
	if (bgmac->feature_flags & BGMAC_FEAT_TX_MASK_SETUP) {
		ctl &= ~BGMAC_DMA_TX_BL_MASK;
		ctl |= BGMAC_DMA_TX_BL_128 << BGMAC_DMA_TX_BL_SHIFT;

		ctl &= ~BGMAC_DMA_TX_MR_MASK;
		ctl |= BGMAC_DMA_TX_MR_2 << BGMAC_DMA_TX_MR_SHIFT;

		ctl &= ~BGMAC_DMA_TX_PC_MASK;
		ctl |= BGMAC_DMA_TX_PC_16 << BGMAC_DMA_TX_PC_SHIFT;

		ctl &= ~BGMAC_DMA_TX_PT_MASK;
		ctl |= BGMAC_DMA_TX_PT_8 << BGMAC_DMA_TX_PT_SHIFT;
	}
	ctl |= BGMAC_DMA_TX_ENABLE;
	ctl |= BGMAC_DMA_TX_PARITY_DISABLE;
	bgmac_write(bgmac, ring->mmio_base + BGMAC_DMA_TX_CTL, ctl);
}