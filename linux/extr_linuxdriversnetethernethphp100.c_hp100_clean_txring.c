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
struct net_device {int base_addr; } ;
struct hp100_private {int txrcommit; TYPE_1__* txrhead; int /*<<< orphan*/  pci_dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {struct TYPE_2__* next; int /*<<< orphan*/ * skb; scalar_t__* pdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  TX_PDL ; 
 int /*<<< orphan*/  dev_consume_skb_any (int /*<<< orphan*/ *) ; 
 int hp100_inb (int /*<<< orphan*/ ) ; 
 struct hp100_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hp100_clean_txring(struct net_device *dev)
{
	struct hp100_private *lp = netdev_priv(dev);
	int ioaddr = dev->base_addr;
	int donecount;

#ifdef HP100_DEBUG_B
	hp100_outw(0x4211, TRACE);
	printk("hp100: %s: clean txring\n", dev->name);
#endif

	/* How many PDLs have been transmitted? */
	donecount = (lp->txrcommit) - hp100_inb(TX_PDL);

#ifdef HP100_DEBUG
	if (donecount > MAX_TX_PDL)
		printk("hp100: %s: Warning: More PDLs transmitted than committed to card???\n", dev->name);
#endif

	for (; 0 != donecount; donecount--) {
#ifdef HP100_DEBUG_BM
		printk("hp100: %s: Free skb: data @0x%.8x txrcommit=0x%x TXPDL=0x%x, done=0x%x\n",
				dev->name, (u_int) lp->txrhead->skb->data,
				lp->txrcommit, hp100_inb(TX_PDL), donecount);
#endif
		/* Conversion to new PCI API : NOP */
		pci_unmap_single(lp->pci_dev, (dma_addr_t) lp->txrhead->pdl[1], lp->txrhead->pdl[2], PCI_DMA_TODEVICE);
		dev_consume_skb_any(lp->txrhead->skb);
		lp->txrhead->skb = NULL;
		lp->txrhead = lp->txrhead->next;
		lp->txrcommit--;
	}
}