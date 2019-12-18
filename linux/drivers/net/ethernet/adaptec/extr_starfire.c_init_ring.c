#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  data; } ;
struct netdev_private {unsigned int dirty_rx; unsigned int dirty_tx; unsigned int rx_done; unsigned int tx_done; int rx_buf_sz; int /*<<< orphan*/ * tx_info; TYPE_4__* tx_done_q; TYPE_3__* rx_done_q; TYPE_2__* rx_ring; TYPE_1__* rx_info; scalar_t__ base; int /*<<< orphan*/  pci_dev; scalar_t__ reap_tx; scalar_t__ cur_tx; scalar_t__ cur_rx; } ;
struct net_device {int mtu; } ;
struct TYPE_8__ {scalar_t__ status; } ;
struct TYPE_7__ {scalar_t__ status; } ;
struct TYPE_6__ {scalar_t__ rxaddr; } ;
struct TYPE_5__ {int mapping; struct sk_buff* skb; } ;

/* Variables and functions */
 int DONE_Q_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int PKT_BUF_SZ ; 
 int RX_RING_SIZE ; 
 int RxDescEndRing ; 
 scalar_t__ RxDescQIdx ; 
 int RxDescValid ; 
 int TX_RING_SIZE ; 
 scalar_t__ cpu_to_dma (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int) ; 
 int pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void init_ring(struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	int i;

	np->cur_rx = np->cur_tx = np->reap_tx = 0;
	np->dirty_rx = np->dirty_tx = np->rx_done = np->tx_done = 0;

	np->rx_buf_sz = (dev->mtu <= 1500 ? PKT_BUF_SZ : dev->mtu + 32);

	/* Fill in the Rx buffers.  Handle allocation failure gracefully. */
	for (i = 0; i < RX_RING_SIZE; i++) {
		struct sk_buff *skb = netdev_alloc_skb(dev, np->rx_buf_sz);
		np->rx_info[i].skb = skb;
		if (skb == NULL)
			break;
		np->rx_info[i].mapping = pci_map_single(np->pci_dev, skb->data, np->rx_buf_sz, PCI_DMA_FROMDEVICE);
		if (pci_dma_mapping_error(np->pci_dev,
					  np->rx_info[i].mapping)) {
			dev_kfree_skb(skb);
			np->rx_info[i].skb = NULL;
			break;
		}
		/* Grrr, we cannot offset to correctly align the IP header. */
		np->rx_ring[i].rxaddr = cpu_to_dma(np->rx_info[i].mapping | RxDescValid);
	}
	writew(i - 1, np->base + RxDescQIdx);
	np->dirty_rx = (unsigned int)(i - RX_RING_SIZE);

	/* Clear the remainder of the Rx buffer ring. */
	for (  ; i < RX_RING_SIZE; i++) {
		np->rx_ring[i].rxaddr = 0;
		np->rx_info[i].skb = NULL;
		np->rx_info[i].mapping = 0;
	}
	/* Mark the last entry as wrapping the ring. */
	np->rx_ring[RX_RING_SIZE - 1].rxaddr |= cpu_to_dma(RxDescEndRing);

	/* Clear the completion rings. */
	for (i = 0; i < DONE_Q_SIZE; i++) {
		np->rx_done_q[i].status = 0;
		np->tx_done_q[i].status = 0;
	}

	for (i = 0; i < TX_RING_SIZE; i++)
		memset(&np->tx_info[i], 0, sizeof(np->tx_info[i]));
}