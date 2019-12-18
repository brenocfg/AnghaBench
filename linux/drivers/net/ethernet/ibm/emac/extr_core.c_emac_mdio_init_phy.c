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
struct net_device {int dummy; } ;
struct mii_phy {struct net_device* dev; } ;
struct emac_instance {int /*<<< orphan*/  phy_dev; } ;

/* Variables and functions */
 struct emac_instance* netdev_priv (struct net_device*) ; 
 int phy_init_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emac_mdio_init_phy(struct mii_phy *phy)
{
	struct net_device *ndev = phy->dev;
	struct emac_instance *dev = netdev_priv(ndev);

	phy_start(dev->phy_dev);
	return phy_init_hw(dev->phy_dev);
}