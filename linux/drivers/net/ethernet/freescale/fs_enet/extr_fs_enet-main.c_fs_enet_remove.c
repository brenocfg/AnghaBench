#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct net_device {int dummy; } ;
struct fs_enet_private {TYPE_1__* fpi; int /*<<< orphan*/  dev; TYPE_3__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* cleanup_data ) (struct net_device*) ;int /*<<< orphan*/  (* free_bd ) (struct net_device*) ;} ;
struct TYPE_4__ {scalar_t__ clk_per; int /*<<< orphan*/  phy_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct fs_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_phy_deregister_fixed_link (int /*<<< orphan*/ ) ; 
 scalar_t__ of_phy_is_fixed_link (int /*<<< orphan*/ ) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int fs_enet_remove(struct platform_device *ofdev)
{
	struct net_device *ndev = platform_get_drvdata(ofdev);
	struct fs_enet_private *fep = netdev_priv(ndev);

	unregister_netdev(ndev);

	fep->ops->free_bd(ndev);
	fep->ops->cleanup_data(ndev);
	dev_set_drvdata(fep->dev, NULL);
	of_node_put(fep->fpi->phy_node);
	if (fep->fpi->clk_per)
		clk_disable_unprepare(fep->fpi->clk_per);
	if (of_phy_is_fixed_link(ofdev->dev.of_node))
		of_phy_deregister_fixed_link(ofdev->dev.of_node);
	free_netdev(ndev);
	return 0;
}