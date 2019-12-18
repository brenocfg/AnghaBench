#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {scalar_t__ len; } ;
struct ring_info {struct sk_buff* skb; int /*<<< orphan*/  mapping; } ;
struct dma_desc {int dummy; } ;
struct b44 {int tx_cons; int /*<<< orphan*/  dev; TYPE_1__* sdev; struct ring_info* tx_buffers; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B44_DMATX_STAT ; 
 int /*<<< orphan*/  B44_GPTIMER ; 
 scalar_t__ B44_TX_WAKEUP_THRESH ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int DMATX_STAT_CDMASK ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int NEXT_TX (int) ; 
 scalar_t__ TX_BUFFS_AVAIL (struct b44*) ; 
 int br32 (struct b44*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bw32 (struct b44*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_consume_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_completed_queue (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b44_tx(struct b44 *bp)
{
	u32 cur, cons;
	unsigned bytes_compl = 0, pkts_compl = 0;

	cur  = br32(bp, B44_DMATX_STAT) & DMATX_STAT_CDMASK;
	cur /= sizeof(struct dma_desc);

	/* XXX needs updating when NETIF_F_SG is supported */
	for (cons = bp->tx_cons; cons != cur; cons = NEXT_TX(cons)) {
		struct ring_info *rp = &bp->tx_buffers[cons];
		struct sk_buff *skb = rp->skb;

		BUG_ON(skb == NULL);

		dma_unmap_single(bp->sdev->dma_dev,
				 rp->mapping,
				 skb->len,
				 DMA_TO_DEVICE);
		rp->skb = NULL;

		bytes_compl += skb->len;
		pkts_compl++;

		dev_consume_skb_irq(skb);
	}

	netdev_completed_queue(bp->dev, pkts_compl, bytes_compl);
	bp->tx_cons = cons;
	if (netif_queue_stopped(bp->dev) &&
	    TX_BUFFS_AVAIL(bp) > B44_TX_WAKEUP_THRESH)
		netif_wake_queue(bp->dev);

	bw32(bp, B44_GPTIMER, 0);
}