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
struct xgene_enet_pdata {int /*<<< orphan*/  phy_speed; int /*<<< orphan*/  phy_mode; TYPE_1__* pdev; } ;
struct phy_device {int dummy; } ;
struct net_device {int dummy; } ;
struct device_node {int dummy; } ;
struct device {scalar_t__ of_node; } ;
struct acpi_device {struct phy_device* driver_data; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseT_Half_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_100baseT_Half_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10baseT_Half_BIT ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 struct acpi_device* acpi_phy_find_device (struct device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct xgene_enet_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (scalar_t__,char*,int) ; 
 struct phy_device* of_phy_connect (struct net_device*,struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ phy_connect_direct (struct net_device*,struct phy_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_remove_link_mode (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_support_asym_pause (struct phy_device*) ; 
 int /*<<< orphan*/  xgene_enet_adjust_link ; 

int xgene_enet_phy_connect(struct net_device *ndev)
{
	struct xgene_enet_pdata *pdata = netdev_priv(ndev);
	struct device_node *np;
	struct phy_device *phy_dev;
	struct device *dev = &pdata->pdev->dev;
	int i;

	if (dev->of_node) {
		for (i = 0 ; i < 2; i++) {
			np = of_parse_phandle(dev->of_node, "phy-handle", i);
			phy_dev = of_phy_connect(ndev, np,
						 &xgene_enet_adjust_link,
						 0, pdata->phy_mode);
			of_node_put(np);
			if (phy_dev)
				break;
		}

		if (!phy_dev) {
			netdev_err(ndev, "Could not connect to PHY\n");
			return -ENODEV;
		}
	} else {
#ifdef CONFIG_ACPI
		struct acpi_device *adev = acpi_phy_find_device(dev);
		if (adev)
			phy_dev = adev->driver_data;
		else
			phy_dev = NULL;

		if (!phy_dev ||
		    phy_connect_direct(ndev, phy_dev, &xgene_enet_adjust_link,
				       pdata->phy_mode)) {
			netdev_err(ndev, "Could not connect to PHY\n");
			return  -ENODEV;
		}
#else
		return -ENODEV;
#endif
	}

	pdata->phy_speed = SPEED_UNKNOWN;
	phy_remove_link_mode(phy_dev, ETHTOOL_LINK_MODE_10baseT_Half_BIT);
	phy_remove_link_mode(phy_dev, ETHTOOL_LINK_MODE_100baseT_Half_BIT);
	phy_remove_link_mode(phy_dev, ETHTOOL_LINK_MODE_1000baseT_Half_BIT);
	phy_support_asym_pause(phy_dev);

	return 0;
}