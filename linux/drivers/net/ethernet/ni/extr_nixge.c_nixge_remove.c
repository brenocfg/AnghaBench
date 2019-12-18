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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct nixge_priv {scalar_t__ mii_bus; int /*<<< orphan*/  phy_node; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mdiobus_unregister (scalar_t__) ; 
 struct nixge_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_phy_deregister_fixed_link (int /*<<< orphan*/ ) ; 
 scalar_t__ of_phy_is_fixed_link (int /*<<< orphan*/ ) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int nixge_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct nixge_priv *priv = netdev_priv(ndev);

	unregister_netdev(ndev);

	if (of_phy_is_fixed_link(pdev->dev.of_node))
		of_phy_deregister_fixed_link(pdev->dev.of_node);
	of_node_put(priv->phy_node);

	if (priv->mii_bus)
		mdiobus_unregister(priv->mii_bus);

	free_netdev(ndev);

	return 0;
}