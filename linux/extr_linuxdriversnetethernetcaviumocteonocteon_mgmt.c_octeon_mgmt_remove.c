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
struct octeon_mgmt {int /*<<< orphan*/  phy_np; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct octeon_mgmt* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int octeon_mgmt_remove(struct platform_device *pdev)
{
	struct net_device *netdev = platform_get_drvdata(pdev);
	struct octeon_mgmt *p = netdev_priv(netdev);

	unregister_netdev(netdev);
	of_node_put(p->phy_np);
	free_netdev(netdev);
	return 0;
}