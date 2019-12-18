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
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct de_private {unsigned int tx_head; int /*<<< orphan*/  lock; TYPE_1__* tx_skb; int /*<<< orphan*/  pdev; struct de_desc* tx_ring; } ;
struct de_desc {void* opts1; void* addr1; void* opts2; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {int mapping; struct sk_buff* skb; } ;

/* Variables and functions */
 int DE_TX_RING_SIZE ; 
 int DescOwn ; 
 int FirstFrag ; 
 int LastFrag ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 unsigned int NEXT_TX (unsigned int) ; 
 int /*<<< orphan*/  NormalTxPoll ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int RingEnd ; 
 unsigned int TX_BUFFS_AVAIL (struct de_private*) ; 
 int /*<<< orphan*/  TxPoll ; 
 int TxSwInt ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dw32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct de_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct de_private*,int /*<<< orphan*/ ,struct net_device*,char*,unsigned int,int) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_queued ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static netdev_tx_t de_start_xmit (struct sk_buff *skb,
					struct net_device *dev)
{
	struct de_private *de = netdev_priv(dev);
	unsigned int entry, tx_free;
	u32 mapping, len, flags = FirstFrag | LastFrag;
	struct de_desc *txd;

	spin_lock_irq(&de->lock);

	tx_free = TX_BUFFS_AVAIL(de);
	if (tx_free == 0) {
		netif_stop_queue(dev);
		spin_unlock_irq(&de->lock);
		return NETDEV_TX_BUSY;
	}
	tx_free--;

	entry = de->tx_head;

	txd = &de->tx_ring[entry];

	len = skb->len;
	mapping = pci_map_single(de->pdev, skb->data, len, PCI_DMA_TODEVICE);
	if (entry == (DE_TX_RING_SIZE - 1))
		flags |= RingEnd;
	if (!tx_free || (tx_free == (DE_TX_RING_SIZE / 2)))
		flags |= TxSwInt;
	flags |= len;
	txd->opts2 = cpu_to_le32(flags);
	txd->addr1 = cpu_to_le32(mapping);

	de->tx_skb[entry].skb = skb;
	de->tx_skb[entry].mapping = mapping;
	wmb();

	txd->opts1 = cpu_to_le32(DescOwn);
	wmb();

	de->tx_head = NEXT_TX(entry);
	netif_dbg(de, tx_queued, dev, "tx queued, slot %d, skblen %d\n",
		  entry, skb->len);

	if (tx_free == 0)
		netif_stop_queue(dev);

	spin_unlock_irq(&de->lock);

	/* Trigger an immediate transmit demand. */
	dw32(TxPoll, NormalTxPoll);

	return NETDEV_TX_OK;
}