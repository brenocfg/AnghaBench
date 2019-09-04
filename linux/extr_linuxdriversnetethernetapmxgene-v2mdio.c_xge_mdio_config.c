#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  phy_mode; } ;
struct xge_pdata {int /*<<< orphan*/  phy_speed; TYPE_2__ resources; struct mii_bus* mdio_bus; TYPE_1__* pdev; } ;
struct phy_device {int supported; int advertising; } ;
struct net_device {int dummy; } ;
struct mii_bus {char* name; int phy_mask; int /*<<< orphan*/  id; struct device* parent; struct xge_pdata* priv; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int PTR_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int SUPPORTED_1000baseT_Half ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_AUI ; 
 int SUPPORTED_BNC ; 
 int SUPPORTED_FIBRE ; 
 int SUPPORTED_MII ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 char* dev_name (struct device*) ; 
 struct mii_bus* mdiobus_alloc () ; 
 int mdiobus_register (struct mii_bus*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct xge_pdata* netdev_priv (struct net_device*) ; 
 struct phy_device* phy_connect (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct phy_device* phy_find_first (struct mii_bus*) ; 
 int /*<<< orphan*/  phydev_name (struct phy_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  xge_adjust_link ; 
 int /*<<< orphan*/  xge_mdio_read ; 
 int /*<<< orphan*/  xge_mdio_remove (struct net_device*) ; 
 int /*<<< orphan*/  xge_mdio_write ; 

int xge_mdio_config(struct net_device *ndev)
{
	struct xge_pdata *pdata = netdev_priv(ndev);
	struct device *dev = &pdata->pdev->dev;
	struct mii_bus *mdio_bus;
	struct phy_device *phydev;
	int ret;

	mdio_bus = mdiobus_alloc();
	if (!mdio_bus)
		return -ENOMEM;

	mdio_bus->name = "APM X-Gene Ethernet (v2) MDIO Bus";
	mdio_bus->read = xge_mdio_read;
	mdio_bus->write = xge_mdio_write;
	mdio_bus->priv = pdata;
	mdio_bus->parent = dev;
	snprintf(mdio_bus->id, MII_BUS_ID_SIZE, "%s-mii", dev_name(dev));
	pdata->mdio_bus = mdio_bus;

	mdio_bus->phy_mask = 0x1;
	ret = mdiobus_register(mdio_bus);
	if (ret)
		goto err;

	phydev = phy_find_first(mdio_bus);
	if (!phydev) {
		dev_err(dev, "no PHY found\n");
		ret = -ENODEV;
		goto err;
	}
	phydev = phy_connect(ndev, phydev_name(phydev),
			     &xge_adjust_link,
			     pdata->resources.phy_mode);

	if (IS_ERR(phydev)) {
		netdev_err(ndev, "Could not attach to PHY\n");
		ret = PTR_ERR(phydev);
		goto err;
	}

	phydev->supported &= ~(SUPPORTED_10baseT_Half |
			       SUPPORTED_10baseT_Full |
			       SUPPORTED_100baseT_Half |
			       SUPPORTED_100baseT_Full |
			       SUPPORTED_1000baseT_Half |
			       SUPPORTED_AUI |
			       SUPPORTED_MII |
			       SUPPORTED_FIBRE |
			       SUPPORTED_BNC);
	phydev->advertising = phydev->supported;
	pdata->phy_speed = SPEED_UNKNOWN;

	return 0;
err:
	xge_mdio_remove(ndev);

	return ret;
}