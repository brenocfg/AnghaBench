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
struct net_device {scalar_t__ phydev; } ;
struct mv643xx_eth_private {struct net_device* dev; int /*<<< orphan*/  clk; int /*<<< orphan*/  tx_timeout_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 
 struct mv643xx_eth_private* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int mv643xx_eth_remove(struct platform_device *pdev)
{
	struct mv643xx_eth_private *mp = platform_get_drvdata(pdev);
	struct net_device *dev = mp->dev;

	unregister_netdev(mp->dev);
	if (dev->phydev)
		phy_disconnect(dev->phydev);
	cancel_work_sync(&mp->tx_timeout_task);

	if (!IS_ERR(mp->clk))
		clk_disable_unprepare(mp->clk);

	free_netdev(mp->dev);

	return 0;
}