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
struct smsc9420_pdata {int last_duplex; int last_carrier; int /*<<< orphan*/  mii_bus; } ;
struct phy_device {int dummy; } ;
struct net_device {int /*<<< orphan*/  phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_MII ; 
 int PTR_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  SPEED_100 ; 
 struct phy_device* mdiobus_get_phy (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct smsc9420_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_attached_info (struct phy_device*) ; 
 struct phy_device* phy_connect (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_set_max_speed (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_support_asym_pause (struct phy_device*) ; 
 int /*<<< orphan*/  phydev_name (struct phy_device*) ; 
 int /*<<< orphan*/  smsc9420_phy_adjust_link ; 

__attribute__((used)) static int smsc9420_mii_probe(struct net_device *dev)
{
	struct smsc9420_pdata *pd = netdev_priv(dev);
	struct phy_device *phydev = NULL;

	BUG_ON(dev->phydev);

	/* Device only supports internal PHY at address 1 */
	phydev = mdiobus_get_phy(pd->mii_bus, 1);
	if (!phydev) {
		netdev_err(dev, "no PHY found at address 1\n");
		return -ENODEV;
	}

	phydev = phy_connect(dev, phydev_name(phydev),
			     smsc9420_phy_adjust_link, PHY_INTERFACE_MODE_MII);

	if (IS_ERR(phydev)) {
		netdev_err(dev, "Could not attach to PHY\n");
		return PTR_ERR(phydev);
	}

	phy_set_max_speed(phydev, SPEED_100);

	/* mask with MAC supported features */
	phy_support_asym_pause(phydev);

	phy_attached_info(phydev);

	pd->last_duplex = -1;
	pd->last_carrier = -1;

	return 0;
}