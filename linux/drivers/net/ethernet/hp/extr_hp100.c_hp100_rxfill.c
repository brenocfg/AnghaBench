#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int base_addr; int /*<<< orphan*/  name; } ;
struct hp100_private {scalar_t__ rxrcommit; TYPE_1__* rxrtail; } ;
struct TYPE_3__ {struct TYPE_3__* next; scalar_t__ pdl_paddr; scalar_t__* pdl; } ;
typedef  TYPE_1__ hp100_ring_t ;

/* Variables and functions */
 scalar_t__ MAX_RX_PDL ; 
 int /*<<< orphan*/  PERFORMANCE ; 
 int /*<<< orphan*/  RX_PDA ; 
 int /*<<< orphan*/  TRACE ; 
 scalar_t__ hp100_build_rx_pdl (TYPE_1__*,struct net_device*) ; 
 int /*<<< orphan*/  hp100_outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_page (int /*<<< orphan*/ ) ; 
 struct hp100_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void hp100_rxfill(struct net_device *dev)
{
	int ioaddr = dev->base_addr;

	struct hp100_private *lp = netdev_priv(dev);
	hp100_ring_t *ringptr;

#ifdef HP100_DEBUG_B
	hp100_outw(0x4208, TRACE);
	printk("hp100: %s: rxfill\n", dev->name);
#endif

	hp100_page(PERFORMANCE);

	while (lp->rxrcommit < MAX_RX_PDL) {
		/*
		   ** Attempt to get a buffer and build a Rx PDL.
		 */
		ringptr = lp->rxrtail;
		if (0 == hp100_build_rx_pdl(ringptr, dev)) {
			return;	/* None available, return */
		}

		/* Hand this PDL over to the card */
		/* Note: This needs performance page selected! */
#ifdef HP100_DEBUG_BM
		printk("hp100: %s: rxfill: Hand to card: pdl #%d @0x%x phys:0x%x, buffer: 0x%x\n",
				     dev->name, lp->rxrcommit, (u_int) ringptr->pdl,
				     (u_int) ringptr->pdl_paddr, (u_int) ringptr->pdl[3]);
#endif

		hp100_outl((u32) ringptr->pdl_paddr, RX_PDA);

		lp->rxrcommit += 1;
		lp->rxrtail = ringptr->next;
	}
}