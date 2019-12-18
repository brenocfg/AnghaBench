#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct bnx2_tx_ring_info {struct bnx2_sw_tx_bd* tx_buf_ring; } ;
struct bnx2_sw_tx_bd {int nr_frags; struct sk_buff* skb; } ;
struct bnx2_napi {struct bnx2_tx_ring_info tx_ring; } ;
struct bnx2 {int num_tx_rings; int /*<<< orphan*/  dev; TYPE_1__* pdev; struct bnx2_napi* bnx2_napi; } ;
struct TYPE_4__ {int /*<<< orphan*/ * frags; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BNX2_NEXT_TX_BD (int) ; 
 int BNX2_TX_DESC_CNT ; 
 size_t BNX2_TX_RING_IDX (int) ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct bnx2_sw_tx_bd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping ; 
 int /*<<< orphan*/  netdev_get_tx_queue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_tx_reset_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void
bnx2_free_tx_skbs(struct bnx2 *bp)
{
	int i;

	for (i = 0; i < bp->num_tx_rings; i++) {
		struct bnx2_napi *bnapi = &bp->bnx2_napi[i];
		struct bnx2_tx_ring_info *txr = &bnapi->tx_ring;
		int j;

		if (!txr->tx_buf_ring)
			continue;

		for (j = 0; j < BNX2_TX_DESC_CNT; ) {
			struct bnx2_sw_tx_bd *tx_buf = &txr->tx_buf_ring[j];
			struct sk_buff *skb = tx_buf->skb;
			int k, last;

			if (!skb) {
				j = BNX2_NEXT_TX_BD(j);
				continue;
			}

			dma_unmap_single(&bp->pdev->dev,
					 dma_unmap_addr(tx_buf, mapping),
					 skb_headlen(skb),
					 PCI_DMA_TODEVICE);

			tx_buf->skb = NULL;

			last = tx_buf->nr_frags;
			j = BNX2_NEXT_TX_BD(j);
			for (k = 0; k < last; k++, j = BNX2_NEXT_TX_BD(j)) {
				tx_buf = &txr->tx_buf_ring[BNX2_TX_RING_IDX(j)];
				dma_unmap_page(&bp->pdev->dev,
					dma_unmap_addr(tx_buf, mapping),
					skb_frag_size(&skb_shinfo(skb)->frags[k]),
					PCI_DMA_TODEVICE);
			}
			dev_kfree_skb(skb);
		}
		netdev_tx_reset_queue(netdev_get_tx_queue(bp->dev, i));
	}
}