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
struct phy_device {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct ethoc {int phy_id; int old_duplex; int old_link; int /*<<< orphan*/  mdio; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_GMII ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ethoc_mdio_poll ; 
 struct phy_device* mdiobus_get_phy (int /*<<< orphan*/ ,int) ; 
 struct ethoc* netdev_priv (struct net_device*) ; 
 int phy_connect_direct (struct net_device*,struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct phy_device* phy_find_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_set_max_speed (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ethoc_mdio_probe(struct net_device *dev)
{
	struct ethoc *priv = netdev_priv(dev);
	struct phy_device *phy;
	int err;

	if (priv->phy_id != -1)
		phy = mdiobus_get_phy(priv->mdio, priv->phy_id);
	else
		phy = phy_find_first(priv->mdio);

	if (!phy) {
		dev_err(&dev->dev, "no PHY found\n");
		return -ENXIO;
	}

	priv->old_duplex = -1;
	priv->old_link = -1;

	err = phy_connect_direct(dev, phy, ethoc_mdio_poll,
				 PHY_INTERFACE_MODE_GMII);
	if (err) {
		dev_err(&dev->dev, "could not attach to PHY\n");
		return err;
	}

	phy_set_max_speed(phy, SPEED_100);

	return 0;
}