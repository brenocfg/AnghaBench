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
struct bgmac_dma_ring {int end; scalar_t__ index_base; scalar_t__ mmio_base; } ;
struct bgmac_dma_desc {int dummy; } ;
struct bgmac {int dummy; } ;

/* Variables and functions */
 scalar_t__ BGMAC_DMA_RX_INDEX ; 
 int /*<<< orphan*/  bgmac_write (struct bgmac*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dma_wmb () ; 

__attribute__((used)) static void bgmac_dma_rx_update_index(struct bgmac *bgmac,
				      struct bgmac_dma_ring *ring)
{
	dma_wmb();

	bgmac_write(bgmac, ring->mmio_base + BGMAC_DMA_RX_INDEX,
		    ring->index_base +
		    ring->end * sizeof(struct bgmac_dma_desc));
}