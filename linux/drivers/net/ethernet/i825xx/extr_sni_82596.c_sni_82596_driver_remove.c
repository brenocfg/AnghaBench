#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct i596_private {int /*<<< orphan*/  mpu_port; int /*<<< orphan*/  ca; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIB82596_DMA_ATTR ; 
 int /*<<< orphan*/  dma_free_attrs (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct i596_private* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int sni_82596_driver_remove(struct platform_device *pdev)
{
	struct net_device *dev = platform_get_drvdata(pdev);
	struct i596_private *lp = netdev_priv(dev);

	unregister_netdev(dev);
	dma_free_attrs(dev->dev.parent, sizeof(struct i596_private), lp->dma,
		       lp->dma_addr, LIB82596_DMA_ATTR);
	iounmap(lp->ca);
	iounmap(lp->mpu_port);
	free_netdev (dev);
	return 0;
}