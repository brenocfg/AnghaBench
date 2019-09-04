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
struct xge_pdata {struct net_device* ndev; } ;
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 struct xge_pdata* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  xge_mdio_remove (struct net_device*) ; 

__attribute__((used)) static int xge_remove(struct platform_device *pdev)
{
	struct xge_pdata *pdata;
	struct net_device *ndev;

	pdata = platform_get_drvdata(pdev);
	ndev = pdata->ndev;

	rtnl_lock();
	if (netif_running(ndev))
		dev_close(ndev);
	rtnl_unlock();

	xge_mdio_remove(ndev);
	unregister_netdev(ndev);
	free_netdev(ndev);

	return 0;
}