#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct net_device {int base_addr; int /*<<< orphan*/  name; } ;
struct hp100_private {TYPE_1__* txring; TYPE_1__* txrtail; TYPE_1__* txrhead; scalar_t__ txrcommit; TYPE_1__* rxring; TYPE_1__* rxrtail; TYPE_1__* rxrhead; scalar_t__ rxrcommit; int /*<<< orphan*/ * page_vaddr_algn; } ;
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ hp100_ring_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_RINGSIZE ; 
 int MAX_RX_PDL ; 
 int MAX_TX_PDL ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  hp100_init_rxpdl (struct net_device*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hp100_init_txpdl (struct net_device*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hp100_outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hp100_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hp100_init_pdls(struct net_device *dev)
{
	struct hp100_private *lp = netdev_priv(dev);
	hp100_ring_t *ringptr;
	u_int *pageptr;		/* Warning : increment by 4 - Jean II */
	int i;

#ifdef HP100_DEBUG_B
	int ioaddr = dev->base_addr;
#endif

#ifdef HP100_DEBUG_B
	hp100_outw(0x4206, TRACE);
	printk("hp100: %s: init pdls\n", dev->name);
#endif

	if (!lp->page_vaddr_algn)
		printk("hp100: %s: Warning: lp->page_vaddr_algn not initialised!\n", dev->name);
	else {
		/* pageptr shall point into the DMA accessible memory region  */
		/* we use this pointer to status the upper limit of allocated */
		/* memory in the allocated page. */
		/* note: align the pointers to the pci cache line size */
		memset(lp->page_vaddr_algn, 0, MAX_RINGSIZE);	/* Zero  Rx/Tx ring page */
		pageptr = lp->page_vaddr_algn;

		lp->rxrcommit = 0;
		ringptr = lp->rxrhead = lp->rxrtail = &(lp->rxring[0]);

		/* Initialise Rx Ring */
		for (i = MAX_RX_PDL - 1; i >= 0; i--) {
			lp->rxring[i].next = ringptr;
			ringptr = &(lp->rxring[i]);
			pageptr += hp100_init_rxpdl(dev, ringptr, pageptr);
		}

		/* Initialise Tx Ring */
		lp->txrcommit = 0;
		ringptr = lp->txrhead = lp->txrtail = &(lp->txring[0]);
		for (i = MAX_TX_PDL - 1; i >= 0; i--) {
			lp->txring[i].next = ringptr;
			ringptr = &(lp->txring[i]);
			pageptr += hp100_init_txpdl(dev, ringptr, pageptr);
		}
	}
}