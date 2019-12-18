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
struct ag71xx {int /*<<< orphan*/  clk_eth; } ;

/* Variables and functions */
 int /*<<< orphan*/  ag71xx_mdio_remove (struct ag71xx*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct ag71xx* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int ag71xx_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct ag71xx *ag;

	if (!ndev)
		return 0;

	ag = netdev_priv(ndev);
	unregister_netdev(ndev);
	ag71xx_mdio_remove(ag);
	clk_disable_unprepare(ag->clk_eth);
	platform_set_drvdata(pdev, NULL);

	return 0;
}