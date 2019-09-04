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
struct ucc_geth_private {TYPE_2__* ug_info; } ;
struct TYPE_3__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct net_device {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  phy_node; int /*<<< orphan*/  tbi_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct ucc_geth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_phy_deregister_fixed_link (struct device_node*) ; 
 scalar_t__ of_phy_is_fixed_link (struct device_node*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  ucc_geth_memclean (struct ucc_geth_private*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int ucc_geth_remove(struct platform_device* ofdev)
{
	struct net_device *dev = platform_get_drvdata(ofdev);
	struct ucc_geth_private *ugeth = netdev_priv(dev);
	struct device_node *np = ofdev->dev.of_node;

	unregister_netdev(dev);
	free_netdev(dev);
	ucc_geth_memclean(ugeth);
	if (of_phy_is_fixed_link(np))
		of_phy_deregister_fixed_link(np);
	of_node_put(ugeth->ug_info->tbi_node);
	of_node_put(ugeth->ug_info->phy_node);

	return 0;
}