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
struct net_device {int base_addr; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;
struct hp100_private {scalar_t__ lan_type; int /*<<< orphan*/  hub_status; } ;

/* Variables and functions */
 scalar_t__ HP100_LAN_100 ; 
 int /*<<< orphan*/  IRQ_MASK ; 
 int /*<<< orphan*/  OPTION_LSW ; 
 int /*<<< orphan*/  PERFORMANCE ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  hp100_inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_login_to_vg_hub (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_stop_interface (struct net_device*) ; 
 struct hp100_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int hp100_close(struct net_device *dev)
{
	int ioaddr = dev->base_addr;
	struct hp100_private *lp = netdev_priv(dev);

#ifdef HP100_DEBUG_B
	hp100_outw(0x4205, TRACE);
	printk("hp100: %s: close\n", dev->name);
#endif

	hp100_page(PERFORMANCE);
	hp100_outw(0xfefe, IRQ_MASK);	/* mask off all IRQs */

	hp100_stop_interface(dev);

	if (lp->lan_type == HP100_LAN_100)
		lp->hub_status = hp100_login_to_vg_hub(dev, 0);

	netif_stop_queue(dev);

	free_irq(dev->irq, dev);

#ifdef HP100_DEBUG
	printk("hp100: %s: close LSW = 0x%x\n", dev->name,
	       hp100_inw(OPTION_LSW));
#endif

	return 0;
}