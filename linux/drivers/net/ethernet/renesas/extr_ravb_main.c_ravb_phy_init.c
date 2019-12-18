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
struct ravb_private {int /*<<< orphan*/  phy_interface; scalar_t__ speed; scalar_t__ link; } ;
struct phy_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* parent; } ;
struct net_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {struct device_node* of_node; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseT_Half_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_100baseT_Half_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10baseT_Half_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Asym_Pause_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Pause_BIT ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 struct device_node* of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct phy_device* of_phy_connect (struct net_device*,struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_phy_deregister_fixed_link (struct device_node*) ; 
 scalar_t__ of_phy_is_fixed_link (struct device_node*) ; 
 int of_phy_register_fixed_link (struct device_node*) ; 
 int /*<<< orphan*/  phy_attached_info (struct phy_device*) ; 
 int /*<<< orphan*/  phy_disconnect (struct phy_device*) ; 
 int /*<<< orphan*/  phy_remove_link_mode (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_set_max_speed (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a7795es10 ; 
 int /*<<< orphan*/  ravb_adjust_link ; 
 scalar_t__ soc_device_match (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ravb_phy_init(struct net_device *ndev)
{
	struct device_node *np = ndev->dev.parent->of_node;
	struct ravb_private *priv = netdev_priv(ndev);
	struct phy_device *phydev;
	struct device_node *pn;
	int err;

	priv->link = 0;
	priv->speed = 0;

	/* Try connecting to PHY */
	pn = of_parse_phandle(np, "phy-handle", 0);
	if (!pn) {
		/* In the case of a fixed PHY, the DT node associated
		 * to the PHY is the Ethernet MAC DT node.
		 */
		if (of_phy_is_fixed_link(np)) {
			err = of_phy_register_fixed_link(np);
			if (err)
				return err;
		}
		pn = of_node_get(np);
	}
	phydev = of_phy_connect(ndev, pn, ravb_adjust_link, 0,
				priv->phy_interface);
	of_node_put(pn);
	if (!phydev) {
		netdev_err(ndev, "failed to connect PHY\n");
		err = -ENOENT;
		goto err_deregister_fixed_link;
	}

	/* This driver only support 10/100Mbit speeds on R-Car H3 ES1.0
	 * at this time.
	 */
	if (soc_device_match(r8a7795es10)) {
		err = phy_set_max_speed(phydev, SPEED_100);
		if (err) {
			netdev_err(ndev, "failed to limit PHY to 100Mbit/s\n");
			goto err_phy_disconnect;
		}

		netdev_info(ndev, "limited PHY to 100Mbit/s\n");
	}

	/* 10BASE, Pause and Asym Pause is not supported */
	phy_remove_link_mode(phydev, ETHTOOL_LINK_MODE_10baseT_Half_BIT);
	phy_remove_link_mode(phydev, ETHTOOL_LINK_MODE_10baseT_Full_BIT);
	phy_remove_link_mode(phydev, ETHTOOL_LINK_MODE_Pause_BIT);
	phy_remove_link_mode(phydev, ETHTOOL_LINK_MODE_Asym_Pause_BIT);

	/* Half Duplex is not supported */
	phy_remove_link_mode(phydev, ETHTOOL_LINK_MODE_1000baseT_Half_BIT);
	phy_remove_link_mode(phydev, ETHTOOL_LINK_MODE_100baseT_Half_BIT);

	phy_attached_info(phydev);

	return 0;

err_phy_disconnect:
	phy_disconnect(phydev);
err_deregister_fixed_link:
	if (of_phy_is_fixed_link(np))
		of_phy_deregister_fixed_link(np);

	return err;
}