#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {int base_addr; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;
struct hp100_private {scalar_t__ bus; int /*<<< orphan*/  hash_bytes; int /*<<< orphan*/  mac2_mode; int /*<<< orphan*/  mac1_mode; int /*<<< orphan*/  lan_type; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ HP100_BUS_EISA ; 
 scalar_t__ HP100_BUS_PCI ; 
 int /*<<< orphan*/  HP100_MAC1MODE3 ; 
 int /*<<< orphan*/  HP100_MAC2MODE3 ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  hp100_hwinit (struct net_device*) ; 
 int /*<<< orphan*/  hp100_interrupt ; 
 int /*<<< orphan*/  hp100_outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_sense_lan (struct net_device*) ; 
 int /*<<< orphan*/  hp100_start_interface (struct net_device*) ; 
 int /*<<< orphan*/  hp100_stop_interface (struct net_device*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 struct hp100_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int hp100_open(struct net_device *dev)
{
	struct hp100_private *lp = netdev_priv(dev);
#ifdef HP100_DEBUG_B
	int ioaddr = dev->base_addr;
#endif

#ifdef HP100_DEBUG_B
	hp100_outw(0x4204, TRACE);
	printk("hp100: %s: open\n", dev->name);
#endif

	/* New: if bus is PCI or EISA, interrupts might be shared interrupts */
	if (request_irq(dev->irq, hp100_interrupt,
			lp->bus == HP100_BUS_PCI || lp->bus ==
			HP100_BUS_EISA ? IRQF_SHARED : 0,
			dev->name, dev)) {
		printk("hp100: %s: unable to get IRQ %d\n", dev->name, dev->irq);
		return -EAGAIN;
	}

	netif_trans_update(dev); /* prevent tx timeout */
	netif_start_queue(dev);

	lp->lan_type = hp100_sense_lan(dev);
	lp->mac1_mode = HP100_MAC1MODE3;
	lp->mac2_mode = HP100_MAC2MODE3;
	memset(&lp->hash_bytes, 0x00, 8);

	hp100_stop_interface(dev);

	hp100_hwinit(dev);

	hp100_start_interface(dev);	/* sets mac modes, enables interrupts */

	return 0;
}