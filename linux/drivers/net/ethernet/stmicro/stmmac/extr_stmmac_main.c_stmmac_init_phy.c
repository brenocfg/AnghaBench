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
struct stmmac_priv {int /*<<< orphan*/  phylink; int /*<<< orphan*/  dev; int /*<<< orphan*/  mii; TYPE_1__* plat; } ;
struct phy_device {int dummy; } ;
struct net_device {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int phy_addr; struct device_node* phylink_node; } ;

/* Variables and functions */
 int ENODEV ; 
 struct phy_device* mdiobus_get_phy (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int phylink_connect_phy (int /*<<< orphan*/ ,struct phy_device*) ; 
 int phylink_of_phy_connect (int /*<<< orphan*/ ,struct device_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmmac_init_phy(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	struct device_node *node;
	int ret;

	node = priv->plat->phylink_node;

	if (node)
		ret = phylink_of_phy_connect(priv->phylink, node, 0);

	/* Some DT bindings do not set-up the PHY handle. Let's try to
	 * manually parse it
	 */
	if (!node || ret) {
		int addr = priv->plat->phy_addr;
		struct phy_device *phydev;

		phydev = mdiobus_get_phy(priv->mii, addr);
		if (!phydev) {
			netdev_err(priv->dev, "no phy at addr %d\n", addr);
			return -ENODEV;
		}

		ret = phylink_connect_phy(priv->phylink, phydev);
	}

	return ret;
}