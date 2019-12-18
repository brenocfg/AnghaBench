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
struct tlan_priv {int rx_tail; struct tlan_list* rx_list; int /*<<< orphan*/  pci_dev; scalar_t__ rx_list_dma; scalar_t__ rx_head; struct tlan_list* tx_list; scalar_t__ tx_tail; scalar_t__ tx_head; } ;
struct tlan_list {int frame_size; scalar_t__ forward; TYPE_1__* buffer; int /*<<< orphan*/  c_stat; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {int count; scalar_t__ address; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  TLAN_CSTAT_READY ; 
 int /*<<< orphan*/  TLAN_CSTAT_UNUSED ; 
 int TLAN_LAST_BUFFER ; 
 int TLAN_MAX_FRAME_SIZE ; 
 int TLAN_NUM_RX_LISTS ; 
 int TLAN_NUM_TX_LISTS ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,int) ; 
 struct tlan_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlan_store_skb (struct tlan_list*,struct sk_buff*) ; 

__attribute__((used)) static void tlan_reset_lists(struct net_device *dev)
{
	struct tlan_priv *priv = netdev_priv(dev);
	int		i;
	struct tlan_list	*list;
	dma_addr_t	list_phys;
	struct sk_buff	*skb;

	priv->tx_head = 0;
	priv->tx_tail = 0;
	for (i = 0; i < TLAN_NUM_TX_LISTS; i++) {
		list = priv->tx_list + i;
		list->c_stat = TLAN_CSTAT_UNUSED;
		list->buffer[0].address = 0;
		list->buffer[2].count = 0;
		list->buffer[2].address = 0;
		list->buffer[8].address = 0;
		list->buffer[9].address = 0;
	}

	priv->rx_head = 0;
	priv->rx_tail = TLAN_NUM_RX_LISTS - 1;
	for (i = 0; i < TLAN_NUM_RX_LISTS; i++) {
		list = priv->rx_list + i;
		list_phys = priv->rx_list_dma + sizeof(struct tlan_list)*i;
		list->c_stat = TLAN_CSTAT_READY;
		list->frame_size = TLAN_MAX_FRAME_SIZE;
		list->buffer[0].count = TLAN_MAX_FRAME_SIZE | TLAN_LAST_BUFFER;
		skb = netdev_alloc_skb_ip_align(dev, TLAN_MAX_FRAME_SIZE + 5);
		if (!skb)
			break;

		list->buffer[0].address = pci_map_single(priv->pci_dev,
							 skb->data,
							 TLAN_MAX_FRAME_SIZE,
							 PCI_DMA_FROMDEVICE);
		tlan_store_skb(list, skb);
		list->buffer[1].count = 0;
		list->buffer[1].address = 0;
		list->forward = list_phys + sizeof(struct tlan_list);
	}

	/* in case ran out of memory early, clear bits */
	while (i < TLAN_NUM_RX_LISTS) {
		tlan_store_skb(priv->rx_list + i, NULL);
		++i;
	}
	list->forward = 0;

}