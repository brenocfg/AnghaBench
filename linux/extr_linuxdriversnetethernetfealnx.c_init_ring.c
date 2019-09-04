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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct netdev_private {int rx_buf_sz; int free_tx_count; TYPE_2__* tx_ring; scalar_t__ tx_ring_dma; scalar_t__ really_tx_count; TYPE_2__* cur_tx_copy; TYPE_2__* cur_tx; TYPE_1__* rx_ring; int /*<<< orphan*/  pci_dev; scalar_t__ really_rx_count; TYPE_1__* lack_rxbuf; scalar_t__ rx_ring_dma; TYPE_1__* cur_rx; } ;
struct net_device {int mtu; } ;
struct fealnx_desc {int dummy; } ;
struct TYPE_4__ {struct TYPE_4__* next_desc_logical; scalar_t__ next_desc; int /*<<< orphan*/ * skbuff; scalar_t__ status; } ;
struct TYPE_3__ {int control; scalar_t__ status; int /*<<< orphan*/  buffer; struct sk_buff* skbuff; struct TYPE_3__* next_desc_logical; scalar_t__ next_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int PKT_BUF_SZ ; 
 int RBSShift ; 
 int RXIC ; 
 scalar_t__ RXOWN ; 
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_ring(struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	int i;

	/* initialize rx variables */
	np->rx_buf_sz = (dev->mtu <= 1500 ? PKT_BUF_SZ : dev->mtu + 32);
	np->cur_rx = &np->rx_ring[0];
	np->lack_rxbuf = np->rx_ring;
	np->really_rx_count = 0;

	/* initial rx descriptors. */
	for (i = 0; i < RX_RING_SIZE; i++) {
		np->rx_ring[i].status = 0;
		np->rx_ring[i].control = np->rx_buf_sz << RBSShift;
		np->rx_ring[i].next_desc = np->rx_ring_dma +
			(i + 1)*sizeof(struct fealnx_desc);
		np->rx_ring[i].next_desc_logical = &np->rx_ring[i + 1];
		np->rx_ring[i].skbuff = NULL;
	}

	/* for the last rx descriptor */
	np->rx_ring[i - 1].next_desc = np->rx_ring_dma;
	np->rx_ring[i - 1].next_desc_logical = np->rx_ring;

	/* allocate skb for rx buffers */
	for (i = 0; i < RX_RING_SIZE; i++) {
		struct sk_buff *skb = netdev_alloc_skb(dev, np->rx_buf_sz);

		if (skb == NULL) {
			np->lack_rxbuf = &np->rx_ring[i];
			break;
		}

		++np->really_rx_count;
		np->rx_ring[i].skbuff = skb;
		np->rx_ring[i].buffer = pci_map_single(np->pci_dev, skb->data,
			np->rx_buf_sz, PCI_DMA_FROMDEVICE);
		np->rx_ring[i].status = RXOWN;
		np->rx_ring[i].control |= RXIC;
	}

	/* initialize tx variables */
	np->cur_tx = &np->tx_ring[0];
	np->cur_tx_copy = &np->tx_ring[0];
	np->really_tx_count = 0;
	np->free_tx_count = TX_RING_SIZE;

	for (i = 0; i < TX_RING_SIZE; i++) {
		np->tx_ring[i].status = 0;
		/* do we need np->tx_ring[i].control = XXX; ?? */
		np->tx_ring[i].next_desc = np->tx_ring_dma +
			(i + 1)*sizeof(struct fealnx_desc);
		np->tx_ring[i].next_desc_logical = &np->tx_ring[i + 1];
		np->tx_ring[i].skbuff = NULL;
	}

	/* for the last tx descriptor */
	np->tx_ring[i - 1].next_desc = np->tx_ring_dma;
	np->tx_ring[i - 1].next_desc_logical = &np->tx_ring[0];
}