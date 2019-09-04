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
typedef  unsigned int u32 ;
struct device {int dummy; } ;
struct bgmac_slot_info {int /*<<< orphan*/  dma_addr; scalar_t__ skb; } ;
struct bgmac_dma_ring {struct bgmac_slot_info* slots; struct bgmac_dma_desc* cpu_base; } ;
struct bgmac_dma_desc {int /*<<< orphan*/  ctl1; } ;
struct bgmac {struct device* dma_dev; } ;

/* Variables and functions */
 unsigned int BGMAC_DESC_CTL1_LEN ; 
 int BGMAC_TX_RING_SLOTS ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb (scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bgmac_dma_tx_ring_free(struct bgmac *bgmac,
				   struct bgmac_dma_ring *ring)
{
	struct device *dma_dev = bgmac->dma_dev;
	struct bgmac_dma_desc *dma_desc = ring->cpu_base;
	struct bgmac_slot_info *slot;
	int i;

	for (i = 0; i < BGMAC_TX_RING_SLOTS; i++) {
		u32 ctl1 = le32_to_cpu(dma_desc[i].ctl1);
		unsigned int len = ctl1 & BGMAC_DESC_CTL1_LEN;

		slot = &ring->slots[i];
		dev_kfree_skb(slot->skb);

		if (!slot->dma_addr)
			continue;

		if (slot->skb)
			dma_unmap_single(dma_dev, slot->dma_addr,
					 len, DMA_TO_DEVICE);
		else
			dma_unmap_page(dma_dev, slot->dma_addr,
				       len, DMA_TO_DEVICE);
	}
}