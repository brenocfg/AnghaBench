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
struct smc_local {int /*<<< orphan*/  base; scalar_t__ dma_chan; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;
struct net_device {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  SMC_IO_EXTENT ; 
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct smc_local* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_release_attrib (struct platform_device*,struct net_device*) ; 
 int /*<<< orphan*/  smc_release_datacs (struct platform_device*,struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int smc_drv_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct smc_local *lp = netdev_priv(ndev);
	struct resource *res;

	unregister_netdev(ndev);

	free_irq(ndev->irq, ndev);

#ifdef CONFIG_ARCH_PXA
	if (lp->dma_chan)
		dma_release_channel(lp->dma_chan);
#endif
	iounmap(lp->base);

	smc_release_datacs(pdev,ndev);
	smc_release_attrib(pdev,ndev);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "smc91x-regs");
	if (!res)
		res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, SMC_IO_EXTENT);

	free_netdev(ndev);

	return 0;
}