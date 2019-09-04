#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct net_device {int dummy; } ;
struct device_node {int dummy; } ;
struct bcm_sysport_priv {int /*<<< orphan*/  dsa_notifier; } ;

/* Variables and functions */
 struct net_device* dev_get_drvdata (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct bcm_sysport_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  of_phy_deregister_fixed_link (struct device_node*) ; 
 scalar_t__ of_phy_is_fixed_link (struct device_node*) ; 
 int /*<<< orphan*/  unregister_dsa_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int bcm_sysport_remove(struct platform_device *pdev)
{
	struct net_device *dev = dev_get_drvdata(&pdev->dev);
	struct bcm_sysport_priv *priv = netdev_priv(dev);
	struct device_node *dn = pdev->dev.of_node;

	/* Not much to do, ndo_close has been called
	 * and we use managed allocations
	 */
	unregister_dsa_notifier(&priv->dsa_notifier);
	unregister_netdev(dev);
	if (of_phy_is_fixed_link(dn))
		of_phy_deregister_fixed_link(dn);
	free_netdev(dev);
	dev_set_drvdata(&pdev->dev, NULL);

	return 0;
}