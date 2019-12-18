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
struct device {int dummy; } ;
struct bgmac_slot_info {scalar_t__ dma_addr; int /*<<< orphan*/  buf; } ;
struct bgmac_dma_ring {struct bgmac_slot_info* slots; } ;
struct bgmac {struct device* dma_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGMAC_RX_BUF_SIZE ; 
 int BGMAC_RX_RING_SLOTS ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_head_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bgmac_dma_rx_ring_free(struct bgmac *bgmac,
				   struct bgmac_dma_ring *ring)
{
	struct device *dma_dev = bgmac->dma_dev;
	struct bgmac_slot_info *slot;
	int i;

	for (i = 0; i < BGMAC_RX_RING_SLOTS; i++) {
		slot = &ring->slots[i];
		if (!slot->dma_addr)
			continue;

		dma_unmap_single(dma_dev, slot->dma_addr,
				 BGMAC_RX_BUF_SIZE,
				 DMA_FROM_DEVICE);
		put_page(virt_to_head_page(slot->buf));
		slot->dma_addr = 0;
	}
}