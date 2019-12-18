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
struct axienet_local {int /*<<< orphan*/ * phy_node; scalar_t__ clk; scalar_t__ phylink; } ;

/* Variables and functions */
 int /*<<< orphan*/  axienet_mdio_teardown (struct axienet_local*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct axienet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phylink_destroy (scalar_t__) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int axienet_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct axienet_local *lp = netdev_priv(ndev);

	unregister_netdev(ndev);

	if (lp->phylink)
		phylink_destroy(lp->phylink);

	axienet_mdio_teardown(lp);

	if (lp->clk)
		clk_disable_unprepare(lp->clk);

	of_node_put(lp->phy_node);
	lp->phy_node = NULL;

	free_netdev(ndev);

	return 0;
}