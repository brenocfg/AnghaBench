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
struct bcm_enet_priv {int /*<<< orphan*/  mac_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int bcm_enetsw_remove(struct platform_device *pdev)
{
	struct bcm_enet_priv *priv;
	struct net_device *dev;

	/* stop netdevice */
	dev = platform_get_drvdata(pdev);
	priv = netdev_priv(dev);
	unregister_netdev(dev);

	clk_disable_unprepare(priv->mac_clk);

	free_netdev(dev);
	return 0;
}