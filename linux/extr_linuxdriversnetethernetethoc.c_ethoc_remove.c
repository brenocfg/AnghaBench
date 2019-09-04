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
struct platform_device {int dummy; } ;
struct net_device {int /*<<< orphan*/  phydev; } ;
struct ethoc {int /*<<< orphan*/  clk; scalar_t__ mdio; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mdiobus_free (scalar_t__) ; 
 int /*<<< orphan*/  mdiobus_unregister (scalar_t__) ; 
 struct ethoc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ ) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int ethoc_remove(struct platform_device *pdev)
{
	struct net_device *netdev = platform_get_drvdata(pdev);
	struct ethoc *priv = netdev_priv(netdev);

	if (netdev) {
		netif_napi_del(&priv->napi);
		phy_disconnect(netdev->phydev);

		if (priv->mdio) {
			mdiobus_unregister(priv->mdio);
			mdiobus_free(priv->mdio);
		}
		clk_disable_unprepare(priv->clk);
		unregister_netdev(netdev);
		free_netdev(netdev);
	}

	return 0;
}