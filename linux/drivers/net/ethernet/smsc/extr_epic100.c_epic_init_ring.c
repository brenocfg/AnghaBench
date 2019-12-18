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
struct net_device {int mtu; } ;
struct epic_tx_desc {int dummy; } ;
struct epic_rx_desc {int dummy; } ;
struct epic_private {unsigned int cur_rx; unsigned int dirty_rx; int rx_buf_sz; scalar_t__ tx_ring_dma; TYPE_2__* tx_ring; int /*<<< orphan*/ ** tx_skbuff; TYPE_1__* rx_ring; int /*<<< orphan*/  pci_dev; struct sk_buff** rx_skbuff; scalar_t__ rx_ring_dma; scalar_t__ cur_tx; scalar_t__ dirty_tx; scalar_t__ tx_full; } ;
struct TYPE_4__ {int txstatus; scalar_t__ next; } ;
struct TYPE_3__ {int buflength; scalar_t__ rxstatus; int /*<<< orphan*/  bufaddr; scalar_t__ next; } ;

/* Variables and functions */
 scalar_t__ DescOwn ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int PKT_BUF_SZ ; 
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 struct epic_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static void epic_init_ring(struct net_device *dev)
{
	struct epic_private *ep = netdev_priv(dev);
	int i;

	ep->tx_full = 0;
	ep->dirty_tx = ep->cur_tx = 0;
	ep->cur_rx = ep->dirty_rx = 0;
	ep->rx_buf_sz = (dev->mtu <= 1500 ? PKT_BUF_SZ : dev->mtu + 32);

	/* Initialize all Rx descriptors. */
	for (i = 0; i < RX_RING_SIZE; i++) {
		ep->rx_ring[i].rxstatus = 0;
		ep->rx_ring[i].buflength = ep->rx_buf_sz;
		ep->rx_ring[i].next = ep->rx_ring_dma +
				      (i+1)*sizeof(struct epic_rx_desc);
		ep->rx_skbuff[i] = NULL;
	}
	/* Mark the last entry as wrapping the ring. */
	ep->rx_ring[i-1].next = ep->rx_ring_dma;

	/* Fill in the Rx buffers.  Handle allocation failure gracefully. */
	for (i = 0; i < RX_RING_SIZE; i++) {
		struct sk_buff *skb = netdev_alloc_skb(dev, ep->rx_buf_sz + 2);
		ep->rx_skbuff[i] = skb;
		if (skb == NULL)
			break;
		skb_reserve(skb, 2);	/* 16 byte align the IP header. */
		ep->rx_ring[i].bufaddr = pci_map_single(ep->pci_dev,
			skb->data, ep->rx_buf_sz, PCI_DMA_FROMDEVICE);
		ep->rx_ring[i].rxstatus = DescOwn;
	}
	ep->dirty_rx = (unsigned int)(i - RX_RING_SIZE);

	/* The Tx buffer descriptor is filled in as needed, but we
	   do need to clear the ownership bit. */
	for (i = 0; i < TX_RING_SIZE; i++) {
		ep->tx_skbuff[i] = NULL;
		ep->tx_ring[i].txstatus = 0x0000;
		ep->tx_ring[i].next = ep->tx_ring_dma +
			(i+1)*sizeof(struct epic_tx_desc);
	}
	ep->tx_ring[i-1].next = ep->tx_ring_dma;
}