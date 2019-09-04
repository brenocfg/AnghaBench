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
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct netdev_private {int free_tx_count; int /*<<< orphan*/  lock; scalar_t__ mem; int /*<<< orphan*/  really_tx_count; TYPE_1__* cur_tx_copy; TYPE_2__* pci_dev; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {int device; } ;
struct TYPE_3__ {int control; struct TYPE_3__* next_desc_logical; int /*<<< orphan*/  status; int /*<<< orphan*/  buffer; struct sk_buff* skbuff; } ;

/* Variables and functions */
 int CRCEnable ; 
 int ETIControl ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int PADEnable ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int PKTSShift ; 
 int RetryTxLC ; 
 int TBSShift ; 
 int TXFD ; 
 int TXIC ; 
 int TXLD ; 
 int /*<<< orphan*/  TXOWN ; 
 scalar_t__ TXPDR ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pci_map_single (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static netdev_tx_t start_tx(struct sk_buff *skb, struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	unsigned long flags;

	spin_lock_irqsave(&np->lock, flags);

	np->cur_tx_copy->skbuff = skb;

#define one_buffer
#define BPT 1022
#if defined(one_buffer)
	np->cur_tx_copy->buffer = pci_map_single(np->pci_dev, skb->data,
		skb->len, PCI_DMA_TODEVICE);
	np->cur_tx_copy->control = TXIC | TXLD | TXFD | CRCEnable | PADEnable;
	np->cur_tx_copy->control |= (skb->len << PKTSShift);	/* pkt size */
	np->cur_tx_copy->control |= (skb->len << TBSShift);	/* buffer size */
// 89/12/29 add,
	if (np->pci_dev->device == 0x891)
		np->cur_tx_copy->control |= ETIControl | RetryTxLC;
	np->cur_tx_copy->status = TXOWN;
	np->cur_tx_copy = np->cur_tx_copy->next_desc_logical;
	--np->free_tx_count;
#elif defined(two_buffer)
	if (skb->len > BPT) {
		struct fealnx_desc *next;

		/* for the first descriptor */
		np->cur_tx_copy->buffer = pci_map_single(np->pci_dev, skb->data,
			BPT, PCI_DMA_TODEVICE);
		np->cur_tx_copy->control = TXIC | TXFD | CRCEnable | PADEnable;
		np->cur_tx_copy->control |= (skb->len << PKTSShift);	/* pkt size */
		np->cur_tx_copy->control |= (BPT << TBSShift);	/* buffer size */

		/* for the last descriptor */
		next = np->cur_tx_copy->next_desc_logical;
		next->skbuff = skb;
		next->control = TXIC | TXLD | CRCEnable | PADEnable;
		next->control |= (skb->len << PKTSShift);	/* pkt size */
		next->control |= ((skb->len - BPT) << TBSShift);	/* buf size */
// 89/12/29 add,
		if (np->pci_dev->device == 0x891)
			np->cur_tx_copy->control |= ETIControl | RetryTxLC;
		next->buffer = pci_map_single(ep->pci_dev, skb->data + BPT,
                                skb->len - BPT, PCI_DMA_TODEVICE);

		next->status = TXOWN;
		np->cur_tx_copy->status = TXOWN;

		np->cur_tx_copy = next->next_desc_logical;
		np->free_tx_count -= 2;
	} else {
		np->cur_tx_copy->buffer = pci_map_single(np->pci_dev, skb->data,
			skb->len, PCI_DMA_TODEVICE);
		np->cur_tx_copy->control = TXIC | TXLD | TXFD | CRCEnable | PADEnable;
		np->cur_tx_copy->control |= (skb->len << PKTSShift);	/* pkt size */
		np->cur_tx_copy->control |= (skb->len << TBSShift);	/* buffer size */
// 89/12/29 add,
		if (np->pci_dev->device == 0x891)
			np->cur_tx_copy->control |= ETIControl | RetryTxLC;
		np->cur_tx_copy->status = TXOWN;
		np->cur_tx_copy = np->cur_tx_copy->next_desc_logical;
		--np->free_tx_count;
	}
#endif

	if (np->free_tx_count < 2)
		netif_stop_queue(dev);
	++np->really_tx_count;
	iowrite32(0, np->mem + TXPDR);

	spin_unlock_irqrestore(&np->lock, flags);
	return NETDEV_TX_OK;
}