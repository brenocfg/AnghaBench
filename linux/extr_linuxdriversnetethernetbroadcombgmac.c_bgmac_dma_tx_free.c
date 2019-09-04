#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct device {int dummy; } ;
struct bgmac_slot_info {scalar_t__ dma_addr; TYPE_6__* skb; } ;
struct bgmac_dma_ring {int start; int end; TYPE_1__* cpu_base; struct bgmac_slot_info* slots; scalar_t__ index_base; scalar_t__ mmio_base; } ;
struct bgmac_dma_desc {int dummy; } ;
struct bgmac {TYPE_3__* net_dev; struct device* dma_dev; } ;
struct TYPE_10__ {scalar_t__ len; } ;
struct TYPE_8__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct TYPE_9__ {TYPE_2__ stats; } ;
struct TYPE_7__ {int /*<<< orphan*/  ctl1; int /*<<< orphan*/  ctl0; } ;

/* Variables and functions */
 int BGMAC_DESC_CTL0_SOF ; 
 int BGMAC_DESC_CTL1_LEN ; 
 int BGMAC_DMA_TX_STATDPTR ; 
 scalar_t__ BGMAC_DMA_TX_STATUS ; 
 int BGMAC_TX_RING_SLOTS ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int bgmac_read (struct bgmac*,scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb (TYPE_6__*) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_completed_queue (TYPE_3__*,unsigned int,unsigned int) ; 
 scalar_t__ netif_queue_stopped (TYPE_3__*) ; 
 int /*<<< orphan*/  netif_wake_queue (TYPE_3__*) ; 

__attribute__((used)) static void bgmac_dma_tx_free(struct bgmac *bgmac, struct bgmac_dma_ring *ring)
{
	struct device *dma_dev = bgmac->dma_dev;
	int empty_slot;
	unsigned bytes_compl = 0, pkts_compl = 0;

	/* The last slot that hardware didn't consume yet */
	empty_slot = bgmac_read(bgmac, ring->mmio_base + BGMAC_DMA_TX_STATUS);
	empty_slot &= BGMAC_DMA_TX_STATDPTR;
	empty_slot -= ring->index_base;
	empty_slot &= BGMAC_DMA_TX_STATDPTR;
	empty_slot /= sizeof(struct bgmac_dma_desc);

	while (ring->start != ring->end) {
		int slot_idx = ring->start % BGMAC_TX_RING_SLOTS;
		struct bgmac_slot_info *slot = &ring->slots[slot_idx];
		u32 ctl0, ctl1;
		int len;

		if (slot_idx == empty_slot)
			break;

		ctl0 = le32_to_cpu(ring->cpu_base[slot_idx].ctl0);
		ctl1 = le32_to_cpu(ring->cpu_base[slot_idx].ctl1);
		len = ctl1 & BGMAC_DESC_CTL1_LEN;
		if (ctl0 & BGMAC_DESC_CTL0_SOF)
			/* Unmap no longer used buffer */
			dma_unmap_single(dma_dev, slot->dma_addr, len,
					 DMA_TO_DEVICE);
		else
			dma_unmap_page(dma_dev, slot->dma_addr, len,
				       DMA_TO_DEVICE);

		if (slot->skb) {
			bgmac->net_dev->stats.tx_bytes += slot->skb->len;
			bgmac->net_dev->stats.tx_packets++;
			bytes_compl += slot->skb->len;
			pkts_compl++;

			/* Free memory! :) */
			dev_kfree_skb(slot->skb);
			slot->skb = NULL;
		}

		slot->dma_addr = 0;
		ring->start++;
	}

	if (!pkts_compl)
		return;

	netdev_completed_queue(bgmac->net_dev, pkts_compl, bytes_compl);

	if (netif_queue_stopped(bgmac->net_dev))
		netif_wake_queue(bgmac->net_dev);
}