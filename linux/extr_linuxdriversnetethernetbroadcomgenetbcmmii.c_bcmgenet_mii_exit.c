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
struct net_device {int dummy; } ;
struct device_node {int dummy; } ;
struct bcmgenet_priv {int /*<<< orphan*/  mii_pdev; int /*<<< orphan*/  phy_dn; TYPE_2__* pdev; } ;
struct TYPE_3__ {struct device_node* of_node; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 struct bcmgenet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_phy_deregister_fixed_link (struct device_node*) ; 
 scalar_t__ of_phy_is_fixed_link (struct device_node*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

void bcmgenet_mii_exit(struct net_device *dev)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);
	struct device_node *dn = priv->pdev->dev.of_node;

	if (of_phy_is_fixed_link(dn))
		of_phy_deregister_fixed_link(dn);
	of_node_put(priv->phy_dn);
	platform_device_unregister(priv->mii_pdev);
}