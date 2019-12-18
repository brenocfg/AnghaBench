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
typedef  int u32 ;
struct net_local {int /*<<< orphan*/ * phy_dev; TYPE_1__* ndev; scalar_t__ phy_node; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ADVERTISE_ALL ; 
 int ADVERTISE_CSMA ; 
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int ENODEV ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_MII ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/ * of_phy_connect (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ *) ; 
 int phy_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_set_max_speed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  xemaclite_adjust_link ; 
 int /*<<< orphan*/  xemaclite_disable_interrupts (struct net_local*) ; 
 int /*<<< orphan*/  xemaclite_enable_interrupts (struct net_local*) ; 
 int /*<<< orphan*/  xemaclite_interrupt ; 
 int /*<<< orphan*/  xemaclite_update_address (struct net_local*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xemaclite_open(struct net_device *dev)
{
	struct net_local *lp = netdev_priv(dev);
	int retval;

	/* Just to be safe, stop the device first */
	xemaclite_disable_interrupts(lp);

	if (lp->phy_node) {
		u32 bmcr;

		lp->phy_dev = of_phy_connect(lp->ndev, lp->phy_node,
					     xemaclite_adjust_link, 0,
					     PHY_INTERFACE_MODE_MII);
		if (!lp->phy_dev) {
			dev_err(&lp->ndev->dev, "of_phy_connect() failed\n");
			return -ENODEV;
		}

		/* EmacLite doesn't support giga-bit speeds */
		phy_set_max_speed(lp->phy_dev, SPEED_100);

		/* Don't advertise 1000BASE-T Full/Half duplex speeds */
		phy_write(lp->phy_dev, MII_CTRL1000, 0);

		/* Advertise only 10 and 100mbps full/half duplex speeds */
		phy_write(lp->phy_dev, MII_ADVERTISE, ADVERTISE_ALL |
			  ADVERTISE_CSMA);

		/* Restart auto negotiation */
		bmcr = phy_read(lp->phy_dev, MII_BMCR);
		bmcr |= (BMCR_ANENABLE | BMCR_ANRESTART);
		phy_write(lp->phy_dev, MII_BMCR, bmcr);

		phy_start(lp->phy_dev);
	}

	/* Set the MAC address each time opened */
	xemaclite_update_address(lp, dev->dev_addr);

	/* Grab the IRQ */
	retval = request_irq(dev->irq, xemaclite_interrupt, 0, dev->name, dev);
	if (retval) {
		dev_err(&lp->ndev->dev, "Could not allocate interrupt %d\n",
			dev->irq);
		if (lp->phy_dev)
			phy_disconnect(lp->phy_dev);
		lp->phy_dev = NULL;

		return retval;
	}

	/* Enable Interrupts */
	xemaclite_enable_interrupts(lp);

	/* We're ready to go */
	netif_start_queue(dev);

	return 0;
}