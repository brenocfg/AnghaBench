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
struct net_device {int /*<<< orphan*/  phydev; } ;
struct mii_bus {int dummy; } ;
struct b44 {struct mii_bus* mii_bus; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdiobus_free (struct mii_bus*) ; 
 int /*<<< orphan*/  mdiobus_unregister (struct mii_bus*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b44_unregister_phy_one(struct b44 *bp)
{
	struct net_device *dev = bp->dev;
	struct mii_bus *mii_bus = bp->mii_bus;

	phy_disconnect(dev->phydev);
	mdiobus_unregister(mii_bus);
	mdiobus_free(mii_bus);
}