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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct tlan_priv {int tx_tail; int tx_in_progress; int /*<<< orphan*/  lock; struct tlan_list* tx_list; int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  tx_busy_count; int /*<<< orphan*/  tx_head; void* tx_list_dma; int /*<<< orphan*/  phy_online; } ;
struct tlan_list {scalar_t__ c_stat; void* forward; TYPE_1__* buffer; scalar_t__ frame_size; } ;
struct sk_buff {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct net_device {int name; scalar_t__ base_addr; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  void* dma_addr_t ;
struct TYPE_2__ {int count; scalar_t__ address; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIRC_INC (int,int) ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 scalar_t__ TLAN_CH_PARM ; 
 scalar_t__ TLAN_CSTAT_READY ; 
 scalar_t__ TLAN_CSTAT_UNUSED ; 
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  TLAN_DEBUG_TX ; 
 void* TLAN_HC_GO ; 
 scalar_t__ TLAN_HOST_CMD ; 
 int TLAN_LAST_BUFFER ; 
 scalar_t__ TLAN_MIN_FRAME_SIZE ; 
 int TLAN_NUM_TX_LISTS ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 unsigned int max (int /*<<< orphan*/ ,unsigned int) ; 
 struct tlan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outl (void*,scalar_t__) ; 
 scalar_t__ pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_padto (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tlan_store_skb (struct tlan_list*,struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t tlan_start_tx(struct sk_buff *skb, struct net_device *dev)
{
	struct tlan_priv *priv = netdev_priv(dev);
	dma_addr_t	tail_list_phys;
	struct tlan_list	*tail_list;
	unsigned long	flags;
	unsigned int    txlen;

	if (!priv->phy_online) {
		TLAN_DBG(TLAN_DEBUG_TX, "TRANSMIT:  %s PHY is not ready\n",
			 dev->name);
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	if (skb_padto(skb, TLAN_MIN_FRAME_SIZE))
		return NETDEV_TX_OK;
	txlen = max(skb->len, (unsigned int)TLAN_MIN_FRAME_SIZE);

	tail_list = priv->tx_list + priv->tx_tail;
	tail_list_phys =
		priv->tx_list_dma + sizeof(struct tlan_list)*priv->tx_tail;

	if (tail_list->c_stat != TLAN_CSTAT_UNUSED) {
		TLAN_DBG(TLAN_DEBUG_TX,
			 "TRANSMIT:  %s is busy (Head=%d Tail=%d)\n",
			 dev->name, priv->tx_head, priv->tx_tail);
		netif_stop_queue(dev);
		priv->tx_busy_count++;
		return NETDEV_TX_BUSY;
	}

	tail_list->forward = 0;

	tail_list->buffer[0].address = pci_map_single(priv->pci_dev,
						      skb->data, txlen,
						      PCI_DMA_TODEVICE);
	tlan_store_skb(tail_list, skb);

	tail_list->frame_size = (u16) txlen;
	tail_list->buffer[0].count = TLAN_LAST_BUFFER | (u32) txlen;
	tail_list->buffer[1].count = 0;
	tail_list->buffer[1].address = 0;

	spin_lock_irqsave(&priv->lock, flags);
	tail_list->c_stat = TLAN_CSTAT_READY;
	if (!priv->tx_in_progress) {
		priv->tx_in_progress = 1;
		TLAN_DBG(TLAN_DEBUG_TX,
			 "TRANSMIT:  Starting TX on buffer %d\n",
			 priv->tx_tail);
		outl(tail_list_phys, dev->base_addr + TLAN_CH_PARM);
		outl(TLAN_HC_GO, dev->base_addr + TLAN_HOST_CMD);
	} else {
		TLAN_DBG(TLAN_DEBUG_TX,
			 "TRANSMIT:  Adding buffer %d to TX channel\n",
			 priv->tx_tail);
		if (priv->tx_tail == 0) {
			(priv->tx_list + (TLAN_NUM_TX_LISTS - 1))->forward
				= tail_list_phys;
		} else {
			(priv->tx_list + (priv->tx_tail - 1))->forward
				= tail_list_phys;
		}
	}
	spin_unlock_irqrestore(&priv->lock, flags);

	CIRC_INC(priv->tx_tail, TLAN_NUM_TX_LISTS);

	return NETDEV_TX_OK;

}