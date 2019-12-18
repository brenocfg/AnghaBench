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
struct phy_device {int dummy; } ;
struct net_device {int dummy; } ;
struct ltq_etop_priv {TYPE_1__* pldata; int /*<<< orphan*/  mii_bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  mii_mode; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int PTR_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  ltq_etop_mdio_link ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct ltq_etop_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_attached_info (struct phy_device*) ; 
 struct phy_device* phy_connect (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct phy_device* phy_find_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_set_max_speed (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydev_name (struct phy_device*) ; 

__attribute__((used)) static int
ltq_etop_mdio_probe(struct net_device *dev)
{
	struct ltq_etop_priv *priv = netdev_priv(dev);
	struct phy_device *phydev;

	phydev = phy_find_first(priv->mii_bus);

	if (!phydev) {
		netdev_err(dev, "no PHY found\n");
		return -ENODEV;
	}

	phydev = phy_connect(dev, phydev_name(phydev),
			     &ltq_etop_mdio_link, priv->pldata->mii_mode);

	if (IS_ERR(phydev)) {
		netdev_err(dev, "Could not attach to PHY\n");
		return PTR_ERR(phydev);
	}

	phy_set_max_speed(phydev, SPEED_100);

	phy_attached_info(phydev);

	return 0;
}