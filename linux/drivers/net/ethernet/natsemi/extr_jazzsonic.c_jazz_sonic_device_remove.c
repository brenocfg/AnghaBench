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
struct sonic_local {int /*<<< orphan*/  descriptors_laddr; int /*<<< orphan*/  descriptors; int /*<<< orphan*/  dma_bitmode; int /*<<< orphan*/  device; } ;
struct platform_device {int dummy; } ;
struct net_device {int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int SIZEOF_SONIC_DESC ; 
 int SONIC_BUS_SCALE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SONIC_MEM_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct sonic_local* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int jazz_sonic_device_remove(struct platform_device *pdev)
{
	struct net_device *dev = platform_get_drvdata(pdev);
	struct sonic_local* lp = netdev_priv(dev);

	unregister_netdev(dev);
	dma_free_coherent(lp->device, SIZEOF_SONIC_DESC * SONIC_BUS_SCALE(lp->dma_bitmode),
	                  lp->descriptors, lp->descriptors_laddr);
	release_mem_region(dev->base_addr, SONIC_MEM_SIZE);
	free_netdev(dev);

	return 0;
}