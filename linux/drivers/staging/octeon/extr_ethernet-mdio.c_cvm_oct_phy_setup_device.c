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
struct octeon_ethernet {scalar_t__ last_link; int /*<<< orphan*/  phy_mode; int /*<<< orphan*/  of_node; } ;
struct net_device {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  cvm_oct_adjust_link ; 
 struct octeon_ethernet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 struct device_node* of_node_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct phy_device* of_phy_connect (struct net_device*,struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ of_phy_is_fixed_link (int /*<<< orphan*/ ) ; 
 int of_phy_register_fixed_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start (struct phy_device*) ; 

int cvm_oct_phy_setup_device(struct net_device *dev)
{
	struct octeon_ethernet *priv = netdev_priv(dev);
	struct device_node *phy_node;
	struct phy_device *phydev = NULL;

	if (!priv->of_node)
		goto no_phy;

	phy_node = of_parse_phandle(priv->of_node, "phy-handle", 0);
	if (!phy_node && of_phy_is_fixed_link(priv->of_node)) {
		int rc;

		rc = of_phy_register_fixed_link(priv->of_node);
		if (rc)
			return rc;

		phy_node = of_node_get(priv->of_node);
	}
	if (!phy_node)
		goto no_phy;

	phydev = of_phy_connect(dev, phy_node, cvm_oct_adjust_link, 0,
				priv->phy_mode);
	of_node_put(phy_node);

	if (!phydev)
		return -ENODEV;

	priv->last_link = 0;
	phy_start(phydev);

	return 0;
no_phy:
	/* If there is no phy, assume a direct MAC connection and that
	 * the link is up.
	 */
	netif_carrier_on(dev);
	return 0;
}