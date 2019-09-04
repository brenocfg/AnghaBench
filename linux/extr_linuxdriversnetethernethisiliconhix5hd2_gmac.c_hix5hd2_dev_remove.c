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
struct net_device {int dummy; } ;
struct hix5hd2_priv {int /*<<< orphan*/  tx_timeout_task; int /*<<< orphan*/  phy_node; int /*<<< orphan*/  hw_cap; int /*<<< orphan*/  bus; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 scalar_t__ HAS_CAP_TSO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  hix5hd2_destroy_hw_desc_queue (struct hix5hd2_priv*) ; 
 int /*<<< orphan*/  hix5hd2_destroy_sg_desc_queue (struct hix5hd2_priv*) ; 
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 struct hix5hd2_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int hix5hd2_dev_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct hix5hd2_priv *priv = netdev_priv(ndev);

	netif_napi_del(&priv->napi);
	unregister_netdev(ndev);
	mdiobus_unregister(priv->bus);
	mdiobus_free(priv->bus);

	if (HAS_CAP_TSO(priv->hw_cap))
		hix5hd2_destroy_sg_desc_queue(priv);
	hix5hd2_destroy_hw_desc_queue(priv);
	of_node_put(priv->phy_node);
	cancel_work_sync(&priv->tx_timeout_task);
	free_netdev(ndev);

	return 0;
}