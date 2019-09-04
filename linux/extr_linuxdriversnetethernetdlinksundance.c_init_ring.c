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
struct netdev_private {unsigned int dirty_rx; unsigned int dirty_tx; int rx_buf_sz; int rx_ring_dma; TYPE_4__* tx_ring; int /*<<< orphan*/ ** tx_skbuff; TYPE_3__* rx_ring; struct sk_buff** rx_skbuff; TYPE_1__* pci_dev; scalar_t__ cur_task; scalar_t__ cur_tx; scalar_t__ cur_rx; } ;
struct net_device {int mtu; } ;
struct TYPE_8__ {scalar_t__ status; } ;
struct TYPE_7__ {TYPE_2__* frag; scalar_t__ status; void* next_desc; } ;
struct TYPE_6__ {void* length; void* addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int LastFrag ; 
 int PKT_BUF_SZ ; 
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,void*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static void init_ring(struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	int i;

	np->cur_rx = np->cur_tx = 0;
	np->dirty_rx = np->dirty_tx = 0;
	np->cur_task = 0;

	np->rx_buf_sz = (dev->mtu <= 1520 ? PKT_BUF_SZ : dev->mtu + 16);

	/* Initialize all Rx descriptors. */
	for (i = 0; i < RX_RING_SIZE; i++) {
		np->rx_ring[i].next_desc = cpu_to_le32(np->rx_ring_dma +
			((i+1)%RX_RING_SIZE)*sizeof(*np->rx_ring));
		np->rx_ring[i].status = 0;
		np->rx_ring[i].frag[0].length = 0;
		np->rx_skbuff[i] = NULL;
	}

	/* Fill in the Rx buffers.  Handle allocation failure gracefully. */
	for (i = 0; i < RX_RING_SIZE; i++) {
		struct sk_buff *skb =
			netdev_alloc_skb(dev, np->rx_buf_sz + 2);
		np->rx_skbuff[i] = skb;
		if (skb == NULL)
			break;
		skb_reserve(skb, 2);	/* 16 byte align the IP header. */
		np->rx_ring[i].frag[0].addr = cpu_to_le32(
			dma_map_single(&np->pci_dev->dev, skb->data,
				np->rx_buf_sz, DMA_FROM_DEVICE));
		if (dma_mapping_error(&np->pci_dev->dev,
					np->rx_ring[i].frag[0].addr)) {
			dev_kfree_skb(skb);
			np->rx_skbuff[i] = NULL;
			break;
		}
		np->rx_ring[i].frag[0].length = cpu_to_le32(np->rx_buf_sz | LastFrag);
	}
	np->dirty_rx = (unsigned int)(i - RX_RING_SIZE);

	for (i = 0; i < TX_RING_SIZE; i++) {
		np->tx_skbuff[i] = NULL;
		np->tx_ring[i].status = 0;
	}
}