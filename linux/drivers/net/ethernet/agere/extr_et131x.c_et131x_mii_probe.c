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
struct phy_device {int /*<<< orphan*/  autoneg; } ;
struct net_device {int dummy; } ;
struct et131x_adapter {TYPE_1__* pdev; int /*<<< orphan*/  mii_bus; } ;
struct TYPE_2__ {scalar_t__ device; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int ENODEV ; 
 scalar_t__ ET131X_PCI_DEVICE_ID_FAST ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_MII ; 
 int PTR_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  et131x_adjust_link ; 
 struct et131x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_attached_info (struct phy_device*) ; 
 struct phy_device* phy_connect (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct phy_device* phy_find_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_set_max_speed (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydev_name (struct phy_device*) ; 

__attribute__((used)) static int et131x_mii_probe(struct net_device *netdev)
{
	struct et131x_adapter *adapter = netdev_priv(netdev);
	struct  phy_device *phydev = NULL;

	phydev = phy_find_first(adapter->mii_bus);
	if (!phydev) {
		dev_err(&adapter->pdev->dev, "no PHY found\n");
		return -ENODEV;
	}

	phydev = phy_connect(netdev, phydev_name(phydev),
			     &et131x_adjust_link, PHY_INTERFACE_MODE_MII);

	if (IS_ERR(phydev)) {
		dev_err(&adapter->pdev->dev, "Could not attach to PHY\n");
		return PTR_ERR(phydev);
	}

	phy_set_max_speed(phydev, SPEED_100);

	if (adapter->pdev->device != ET131X_PCI_DEVICE_ID_FAST)
		phy_set_max_speed(phydev, SPEED_1000);

	phydev->autoneg = AUTONEG_ENABLE;

	phy_attached_info(phydev);

	return 0;
}