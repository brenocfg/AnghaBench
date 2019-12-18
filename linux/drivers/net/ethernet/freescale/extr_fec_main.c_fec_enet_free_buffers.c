#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct fec_enet_private {unsigned int num_rx_queues; unsigned int num_tx_queues; struct fec_enet_priv_tx_q** tx_queue; scalar_t__ rx_align; TYPE_1__* pdev; struct fec_enet_priv_rx_q** rx_queue; } ;
struct TYPE_5__ {unsigned int ring_size; struct bufdesc* base; } ;
struct fec_enet_priv_tx_q {struct sk_buff** tx_skbuff; int /*<<< orphan*/ ** tx_bounce; TYPE_2__ bd; } ;
struct TYPE_6__ {unsigned int ring_size; struct bufdesc* base; } ;
struct fec_enet_priv_rx_q {TYPE_3__ bd; struct sk_buff** rx_skbuff; } ;
struct bufdesc {int /*<<< orphan*/  cbd_bufaddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ FEC_ENET_RX_FRSIZE ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fec32_to_cpu (int /*<<< orphan*/ ) ; 
 struct bufdesc* fec_enet_get_nextdesc (struct bufdesc*,TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void fec_enet_free_buffers(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	unsigned int i;
	struct sk_buff *skb;
	struct bufdesc	*bdp;
	struct fec_enet_priv_tx_q *txq;
	struct fec_enet_priv_rx_q *rxq;
	unsigned int q;

	for (q = 0; q < fep->num_rx_queues; q++) {
		rxq = fep->rx_queue[q];
		bdp = rxq->bd.base;
		for (i = 0; i < rxq->bd.ring_size; i++) {
			skb = rxq->rx_skbuff[i];
			rxq->rx_skbuff[i] = NULL;
			if (skb) {
				dma_unmap_single(&fep->pdev->dev,
						 fec32_to_cpu(bdp->cbd_bufaddr),
						 FEC_ENET_RX_FRSIZE - fep->rx_align,
						 DMA_FROM_DEVICE);
				dev_kfree_skb(skb);
			}
			bdp = fec_enet_get_nextdesc(bdp, &rxq->bd);
		}
	}

	for (q = 0; q < fep->num_tx_queues; q++) {
		txq = fep->tx_queue[q];
		bdp = txq->bd.base;
		for (i = 0; i < txq->bd.ring_size; i++) {
			kfree(txq->tx_bounce[i]);
			txq->tx_bounce[i] = NULL;
			skb = txq->tx_skbuff[i];
			txq->tx_skbuff[i] = NULL;
			dev_kfree_skb(skb);
		}
	}
}