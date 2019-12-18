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
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  phydev; int /*<<< orphan*/  name; } ;
struct ax_device {int running; int /*<<< orphan*/  mii_bus; int /*<<< orphan*/  irqflags; TYPE_1__* plat; } ;
struct TYPE_2__ {scalar_t__ check_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ax_ei_interrupt ; 
 int /*<<< orphan*/  ax_ei_interrupt_filtered ; 
 int ax_ei_open (struct net_device*) ; 
 int ax_mii_init (struct net_device*) ; 
 int ax_mii_probe (struct net_device*) ; 
 int /*<<< orphan*/  ax_phy_switch (struct net_device*,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  free_mdio_bitbang (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 struct ax_device* to_ax_dev (struct net_device*) ; 

__attribute__((used)) static int ax_open(struct net_device *dev)
{
	struct ax_device *ax = to_ax_dev(dev);
	int ret;

	netdev_dbg(dev, "open\n");

	ret = ax_mii_init(dev);
	if (ret)
		goto failed_mii;

	if (ax->plat->check_irq)
		ret = request_irq(dev->irq, ax_ei_interrupt_filtered,
				  ax->irqflags, dev->name, dev);
	else
		ret = request_irq(dev->irq, ax_ei_interrupt, ax->irqflags,
				  dev->name, dev);
	if (ret)
		goto failed_request_irq;

	/* turn the phy on (if turned off) */
	ax_phy_switch(dev, 1);

	ret = ax_mii_probe(dev);
	if (ret)
		goto failed_mii_probe;
	phy_start(dev->phydev);

	ret = ax_ei_open(dev);
	if (ret)
		goto failed_ax_ei_open;

	ax->running = 1;

	return 0;

 failed_ax_ei_open:
	phy_disconnect(dev->phydev);
 failed_mii_probe:
	ax_phy_switch(dev, 0);
	free_irq(dev->irq, dev);
 failed_request_irq:
	/* unregister mdiobus */
	mdiobus_unregister(ax->mii_bus);
	free_mdio_bitbang(ax->mii_bus);
 failed_mii:
	return ret;
}