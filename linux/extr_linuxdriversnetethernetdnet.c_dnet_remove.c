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
struct platform_device {int dummy; } ;
struct net_device {int /*<<< orphan*/  irq; scalar_t__ phydev; } ;
struct dnet {int /*<<< orphan*/  mii_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 struct dnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int dnet_remove(struct platform_device *pdev)
{

	struct net_device *dev;
	struct dnet *bp;

	dev = platform_get_drvdata(pdev);

	if (dev) {
		bp = netdev_priv(dev);
		if (dev->phydev)
			phy_disconnect(dev->phydev);
		mdiobus_unregister(bp->mii_bus);
		mdiobus_free(bp->mii_bus);
		unregister_netdev(dev);
		free_irq(dev->irq, dev);
		free_netdev(dev);
	}

	return 0;
}