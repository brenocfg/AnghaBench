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
struct hamachi_private {unsigned int dirty_rx; unsigned int dirty_tx; int rx_buf_sz; TYPE_2__* tx_ring; int /*<<< orphan*/ ** tx_skbuff; TYPE_1__* rx_ring; int /*<<< orphan*/  pci_dev; struct sk_buff** rx_skbuff; scalar_t__ cur_tx; scalar_t__ cur_rx; scalar_t__ tx_full; } ;
struct TYPE_4__ {scalar_t__ status_n_length; } ;
struct TYPE_3__ {scalar_t__ status_n_length; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int DescEndPacket ; 
 int DescEndRing ; 
 int DescIntr ; 
 int DescOwn ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int PKT_BUF_SZ ; 
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 scalar_t__ cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_leXX (int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 struct hamachi_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static void hamachi_init_ring(struct net_device *dev)
{
	struct hamachi_private *hmp = netdev_priv(dev);
	int i;

	hmp->tx_full = 0;
	hmp->cur_rx = hmp->cur_tx = 0;
	hmp->dirty_rx = hmp->dirty_tx = 0;

	/* +26 gets the maximum ethernet encapsulation, +7 & ~7 because the
	 * card needs room to do 8 byte alignment, +2 so we can reserve
	 * the first 2 bytes, and +16 gets room for the status word from the
	 * card.  -KDU
	 */
	hmp->rx_buf_sz = (dev->mtu <= 1492 ? PKT_BUF_SZ :
		(((dev->mtu+26+7) & ~7) + 16));

	/* Initialize all Rx descriptors. */
	for (i = 0; i < RX_RING_SIZE; i++) {
		hmp->rx_ring[i].status_n_length = 0;
		hmp->rx_skbuff[i] = NULL;
	}
	/* Fill in the Rx buffers.  Handle allocation failure gracefully. */
	for (i = 0; i < RX_RING_SIZE; i++) {
		struct sk_buff *skb = netdev_alloc_skb(dev, hmp->rx_buf_sz + 2);
		hmp->rx_skbuff[i] = skb;
		if (skb == NULL)
			break;
		skb_reserve(skb, 2); /* 16 byte align the IP header. */
                hmp->rx_ring[i].addr = cpu_to_leXX(pci_map_single(hmp->pci_dev,
			skb->data, hmp->rx_buf_sz, PCI_DMA_FROMDEVICE));
		/* -2 because it doesn't REALLY have that first 2 bytes -KDU */
		hmp->rx_ring[i].status_n_length = cpu_to_le32(DescOwn |
			DescEndPacket | DescIntr | (hmp->rx_buf_sz -2));
	}
	hmp->dirty_rx = (unsigned int)(i - RX_RING_SIZE);
	hmp->rx_ring[RX_RING_SIZE-1].status_n_length |= cpu_to_le32(DescEndRing);

	for (i = 0; i < TX_RING_SIZE; i++) {
		hmp->tx_skbuff[i] = NULL;
		hmp->tx_ring[i].status_n_length = 0;
	}
	/* Mark the last entry of the ring */
	hmp->tx_ring[TX_RING_SIZE-1].status_n_length |= cpu_to_le32(DescEndRing);
}