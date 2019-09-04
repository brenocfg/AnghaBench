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
struct bgmac_dma_ring {scalar_t__ mmio_base; } ;
struct bgmac {int dummy; } ;
typedef  enum bgmac_dma_ring_type { ____Placeholder_bgmac_dma_ring_type } bgmac_dma_ring_type ;

/* Variables and functions */
#define  BGMAC_DMA_RING_RX 129 
#define  BGMAC_DMA_RING_TX 128 
 scalar_t__ BGMAC_DMA_RX_RINGLO ; 
 scalar_t__ BGMAC_DMA_TX_RINGLO ; 
 int /*<<< orphan*/  bgmac_read (struct bgmac*,scalar_t__) ; 
 int /*<<< orphan*/  bgmac_write (struct bgmac*,scalar_t__,int) ; 

__attribute__((used)) static bool bgmac_dma_unaligned(struct bgmac *bgmac,
				struct bgmac_dma_ring *ring,
				enum bgmac_dma_ring_type ring_type)
{
	switch (ring_type) {
	case BGMAC_DMA_RING_TX:
		bgmac_write(bgmac, ring->mmio_base + BGMAC_DMA_TX_RINGLO,
			    0xff0);
		if (bgmac_read(bgmac, ring->mmio_base + BGMAC_DMA_TX_RINGLO))
			return true;
		break;
	case BGMAC_DMA_RING_RX:
		bgmac_write(bgmac, ring->mmio_base + BGMAC_DMA_RX_RINGLO,
			    0xff0);
		if (bgmac_read(bgmac, ring->mmio_base + BGMAC_DMA_RX_RINGLO))
			return true;
		break;
	}
	return false;
}