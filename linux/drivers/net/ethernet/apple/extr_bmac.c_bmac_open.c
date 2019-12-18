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
struct net_device {int /*<<< orphan*/  irq; } ;
struct bmac_data {int opened; } ;

/* Variables and functions */
 int /*<<< orphan*/  bmac_reset_and_enable (struct net_device*) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct bmac_data* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bmac_open(struct net_device *dev)
{
	struct bmac_data *bp = netdev_priv(dev);
	/* XXDEBUG(("bmac: enter open\n")); */
	/* reset the chip */
	bp->opened = 1;
	bmac_reset_and_enable(dev);
	enable_irq(dev->irq);
	return 0;
}