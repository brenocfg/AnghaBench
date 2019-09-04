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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct netdev_private {int cur_rx; int dirty_rx; int rx_buf_sz; TYPE_3__* rx_ring; struct sk_buff** rx_skbuff; TYPE_1__* pci_dev; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {scalar_t__ status; TYPE_2__* frag; } ;
struct TYPE_5__ {void* length; void* addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int LastFrag ; 
 int RX_RING_SIZE ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,void*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static void refill_rx (struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	int entry;
	int cnt = 0;

	/* Refill the Rx ring buffers. */
	for (;(np->cur_rx - np->dirty_rx + RX_RING_SIZE) % RX_RING_SIZE > 0;
		np->dirty_rx = (np->dirty_rx + 1) % RX_RING_SIZE) {
		struct sk_buff *skb;
		entry = np->dirty_rx % RX_RING_SIZE;
		if (np->rx_skbuff[entry] == NULL) {
			skb = netdev_alloc_skb(dev, np->rx_buf_sz + 2);
			np->rx_skbuff[entry] = skb;
			if (skb == NULL)
				break;		/* Better luck next round. */
			skb_reserve(skb, 2);	/* Align IP on 16 byte boundaries */
			np->rx_ring[entry].frag[0].addr = cpu_to_le32(
				dma_map_single(&np->pci_dev->dev, skb->data,
					np->rx_buf_sz, DMA_FROM_DEVICE));
			if (dma_mapping_error(&np->pci_dev->dev,
				    np->rx_ring[entry].frag[0].addr)) {
			    dev_kfree_skb_irq(skb);
			    np->rx_skbuff[entry] = NULL;
			    break;
			}
		}
		/* Perhaps we need not reset this field. */
		np->rx_ring[entry].frag[0].length =
			cpu_to_le32(np->rx_buf_sz | LastFrag);
		np->rx_ring[entry].status = 0;
		cnt++;
	}
}