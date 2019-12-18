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
struct r6040_private {int old_duplex; scalar_t__ old_link; TYPE_1__* pdev; int /*<<< orphan*/  mii_bus; } ;
struct phy_device {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_MII ; 
 int PTR_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct r6040_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_attached_info (struct phy_device*) ; 
 struct phy_device* phy_connect (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct phy_device* phy_find_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_set_max_speed (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydev_name (struct phy_device*) ; 
 int /*<<< orphan*/  r6040_adjust_link ; 

__attribute__((used)) static int r6040_mii_probe(struct net_device *dev)
{
	struct r6040_private *lp = netdev_priv(dev);
	struct phy_device *phydev = NULL;

	phydev = phy_find_first(lp->mii_bus);
	if (!phydev) {
		dev_err(&lp->pdev->dev, "no PHY found\n");
		return -ENODEV;
	}

	phydev = phy_connect(dev, phydev_name(phydev), &r6040_adjust_link,
			     PHY_INTERFACE_MODE_MII);

	if (IS_ERR(phydev)) {
		dev_err(&lp->pdev->dev, "could not attach to PHY\n");
		return PTR_ERR(phydev);
	}

	phy_set_max_speed(phydev, SPEED_100);

	lp->old_link = 0;
	lp->old_duplex = -1;

	phy_attached_info(phydev);

	return 0;
}