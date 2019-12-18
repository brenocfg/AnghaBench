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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct net_device {int dummy; } ;
struct hip04_priv {int /*<<< orphan*/  tx_timeout_task; int /*<<< orphan*/  phy_node; scalar_t__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  hip04_free_ring (struct net_device*,struct device*) ; 
 struct hip04_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int hip04_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct hip04_priv *priv = netdev_priv(ndev);
	struct device *d = &pdev->dev;

	if (priv->phy)
		phy_disconnect(priv->phy);

	hip04_free_ring(ndev, d);
	unregister_netdev(ndev);
	of_node_put(priv->phy_node);
	cancel_work_sync(&priv->tx_timeout_task);
	free_netdev(ndev);

	return 0;
}