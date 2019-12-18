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
struct el3_private {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL3WINDOW (int /*<<< orphan*/ ) ; 
 scalar_t__ EL3_EISA ; 
 scalar_t__ WN0_IRQ ; 
 int el3_debug ; 
 int /*<<< orphan*/  el3_down (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct el3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
el3_close(struct net_device *dev)
{
	int ioaddr = dev->base_addr;
	struct el3_private *lp = netdev_priv(dev);

	if (el3_debug > 2)
		pr_debug("%s: Shutting down ethercard.\n", dev->name);

	el3_down(dev);

	free_irq(dev->irq, dev);
	/* Switching back to window 0 disables the IRQ. */
	EL3WINDOW(0);
	if (lp->type != EL3_EISA) {
		/* But we explicitly zero the IRQ line select anyway. Don't do
		 * it on EISA cards, it prevents the module from getting an
		 * IRQ after unload+reload... */
		outw(0x0f00, ioaddr + WN0_IRQ);
	}

	return 0;
}