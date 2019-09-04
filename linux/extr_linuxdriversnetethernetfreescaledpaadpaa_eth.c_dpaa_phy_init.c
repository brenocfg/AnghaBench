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
struct phy_device {int supported; int advertising; } ;
struct net_device {struct phy_device* phydev; } ;
struct mac_device {int if_support; struct phy_device* phy_dev; int /*<<< orphan*/  phy_if; int /*<<< orphan*/  phy_node; } ;
struct dpaa_priv {struct mac_device* mac_dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int SUPPORTED_Asym_Pause ; 
 int SUPPORTED_Pause ; 
 int /*<<< orphan*/  dpaa_adjust_link ; 
 int /*<<< orphan*/  ifup ; 
 struct dpaa_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct dpaa_priv*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 struct phy_device* of_phy_connect (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpaa_phy_init(struct net_device *net_dev)
{
	struct mac_device *mac_dev;
	struct phy_device *phy_dev;
	struct dpaa_priv *priv;

	priv = netdev_priv(net_dev);
	mac_dev = priv->mac_dev;

	phy_dev = of_phy_connect(net_dev, mac_dev->phy_node,
				 &dpaa_adjust_link, 0,
				 mac_dev->phy_if);
	if (!phy_dev) {
		netif_err(priv, ifup, net_dev, "init_phy() failed\n");
		return -ENODEV;
	}

	/* Remove any features not supported by the controller */
	phy_dev->supported &= mac_dev->if_support;
	phy_dev->supported |= (SUPPORTED_Pause | SUPPORTED_Asym_Pause);
	phy_dev->advertising = phy_dev->supported;

	mac_dev->phy_dev = phy_dev;
	net_dev->phydev = phy_dev;

	return 0;
}