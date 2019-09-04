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
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  phydev; } ;
struct ax_device {int /*<<< orphan*/  mii_bus; scalar_t__ running; } ;

/* Variables and functions */
 int /*<<< orphan*/  ax_ei_close (struct net_device*) ; 
 int /*<<< orphan*/  ax_phy_switch (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  free_mdio_bitbang (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ ) ; 
 struct ax_device* to_ax_dev (struct net_device*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int ax_close(struct net_device *dev)
{
	struct ax_device *ax = to_ax_dev(dev);

	netdev_dbg(dev, "close\n");

	ax->running = 0;
	wmb();

	ax_ei_close(dev);

	/* turn the phy off */
	ax_phy_switch(dev, 0);
	phy_disconnect(dev->phydev);

	free_irq(dev->irq, dev);

	mdiobus_unregister(ax->mii_bus);
	free_mdio_bitbang(ax->mii_bus);
	return 0;
}