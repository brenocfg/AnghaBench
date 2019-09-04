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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;
struct ks8842_adapter {int /*<<< orphan*/  hw_addr; int /*<<< orphan*/  tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct ks8842_adapter* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int ks8842_remove(struct platform_device *pdev)
{
	struct net_device *netdev = platform_get_drvdata(pdev);
	struct ks8842_adapter *adapter = netdev_priv(netdev);
	struct resource *iomem = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	unregister_netdev(netdev);
	tasklet_kill(&adapter->tasklet);
	iounmap(adapter->hw_addr);
	free_netdev(netdev);
	release_mem_region(iomem->start, resource_size(iomem));
	return 0;
}