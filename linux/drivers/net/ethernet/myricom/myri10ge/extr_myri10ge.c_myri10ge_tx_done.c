#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; } ;
struct pci_dev {int dummy; } ;
struct netdev_queue {int dummy; } ;
struct myri10ge_tx_buf {int pkt_done; int done; int mask; int req; int /*<<< orphan*/  wake_queue; int /*<<< orphan*/  send_stop; scalar_t__ queue_active; TYPE_4__* info; } ;
struct TYPE_7__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct myri10ge_slice_state {TYPE_3__* mgp; int /*<<< orphan*/  dev; TYPE_1__ stats; struct myri10ge_tx_buf tx; } ;
struct TYPE_10__ {scalar_t__ last; struct sk_buff* skb; } ;
struct TYPE_9__ {int ss; scalar_t__ running; TYPE_2__* dev; struct pci_dev* pdev; } ;
struct TYPE_8__ {int real_num_tx_queues; } ;

/* Variables and functions */
 scalar_t__ MYRI10GE_ETH_RUNNING ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 scalar_t__ __netif_tx_trylock (struct netdev_queue*) ; 
 int /*<<< orphan*/  __netif_tx_unlock (struct netdev_queue*) ; 
 int /*<<< orphan*/  bus ; 
 int /*<<< orphan*/  dev_consume_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_addr (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int dma_unmap_len (TYPE_4__*,int) ; 
 int /*<<< orphan*/  dma_unmap_len_set (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  mb () ; 
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,struct myri10ge_slice_state*) ; 
 scalar_t__ netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  pci_unmap_page (struct pci_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_be32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
myri10ge_tx_done(struct myri10ge_slice_state *ss, int mcp_index)
{
	struct pci_dev *pdev = ss->mgp->pdev;
	struct myri10ge_tx_buf *tx = &ss->tx;
	struct netdev_queue *dev_queue;
	struct sk_buff *skb;
	int idx, len;

	while (tx->pkt_done != mcp_index) {
		idx = tx->done & tx->mask;
		skb = tx->info[idx].skb;

		/* Mark as free */
		tx->info[idx].skb = NULL;
		if (tx->info[idx].last) {
			tx->pkt_done++;
			tx->info[idx].last = 0;
		}
		tx->done++;
		len = dma_unmap_len(&tx->info[idx], len);
		dma_unmap_len_set(&tx->info[idx], len, 0);
		if (skb) {
			ss->stats.tx_bytes += skb->len;
			ss->stats.tx_packets++;
			dev_consume_skb_irq(skb);
			if (len)
				pci_unmap_single(pdev,
						 dma_unmap_addr(&tx->info[idx],
								bus), len,
						 PCI_DMA_TODEVICE);
		} else {
			if (len)
				pci_unmap_page(pdev,
					       dma_unmap_addr(&tx->info[idx],
							      bus), len,
					       PCI_DMA_TODEVICE);
		}
	}

	dev_queue = netdev_get_tx_queue(ss->dev, ss - ss->mgp->ss);
	/*
	 * Make a minimal effort to prevent the NIC from polling an
	 * idle tx queue.  If we can't get the lock we leave the queue
	 * active. In this case, either a thread was about to start
	 * using the queue anyway, or we lost a race and the NIC will
	 * waste some of its resources polling an inactive queue for a
	 * while.
	 */

	if ((ss->mgp->dev->real_num_tx_queues > 1) &&
	    __netif_tx_trylock(dev_queue)) {
		if (tx->req == tx->done) {
			tx->queue_active = 0;
			put_be32(htonl(1), tx->send_stop);
			mb();
		}
		__netif_tx_unlock(dev_queue);
	}

	/* start the queue if we've stopped it */
	if (netif_tx_queue_stopped(dev_queue) &&
	    tx->req - tx->done < (tx->mask >> 1) &&
	    ss->mgp->running == MYRI10GE_ETH_RUNNING) {
		tx->wake_queue++;
		netif_tx_wake_queue(dev_queue);
	}
}