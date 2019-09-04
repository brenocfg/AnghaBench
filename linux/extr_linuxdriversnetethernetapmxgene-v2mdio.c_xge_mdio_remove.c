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
struct xge_pdata {struct mii_bus* mdio_bus; } ;
struct net_device {scalar_t__ phydev; } ;
struct mii_bus {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ MDIOBUS_REGISTERED ; 
 int /*<<< orphan*/  mdiobus_free (struct mii_bus*) ; 
 int /*<<< orphan*/  mdiobus_unregister (struct mii_bus*) ; 
 struct xge_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 

void xge_mdio_remove(struct net_device *ndev)
{
	struct xge_pdata *pdata = netdev_priv(ndev);
	struct mii_bus *mdio_bus = pdata->mdio_bus;

	if (ndev->phydev)
		phy_disconnect(ndev->phydev);

	if (mdio_bus->state == MDIOBUS_REGISTERED)
		mdiobus_unregister(mdio_bus);

	mdiobus_free(mdio_bus);
}