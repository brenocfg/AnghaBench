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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct netdev_private {scalar_t__ really_rx_count; TYPE_1__* lack_rxbuf; int /*<<< orphan*/  rx_buf_sz; int /*<<< orphan*/  pci_dev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  buffer; struct sk_buff* skbuff; struct TYPE_2__* next_desc_logical; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  RXOWN ; 
 scalar_t__ RX_RING_SIZE ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void allocate_rx_buffers(struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);

	/*  allocate skb for rx buffers */
	while (np->really_rx_count != RX_RING_SIZE) {
		struct sk_buff *skb;

		skb = netdev_alloc_skb(dev, np->rx_buf_sz);
		if (skb == NULL)
			break;	/* Better luck next round. */

		while (np->lack_rxbuf->skbuff)
			np->lack_rxbuf = np->lack_rxbuf->next_desc_logical;

		np->lack_rxbuf->skbuff = skb;
		np->lack_rxbuf->buffer = pci_map_single(np->pci_dev, skb->data,
			np->rx_buf_sz, PCI_DMA_FROMDEVICE);
		np->lack_rxbuf->status = RXOWN;
		++np->really_rx_count;
	}
}