#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct w90p910_ether {scalar_t__ txirq; scalar_t__ rxirq; TYPE_1__* res; int /*<<< orphan*/ * reg; void* clk; void* rmiiclk; struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 struct net_device* alloc_etherdev (int) ; 
 void* clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_put (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/ * ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 struct w90p910_ether* netdev_priv (struct net_device*) ; 
 void* platform_get_irq (struct platform_device*,int) ; 
 TYPE_1__* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 
 int /*<<< orphan*/  w90p910_ether_setup (struct net_device*) ; 

__attribute__((used)) static int w90p910_ether_probe(struct platform_device *pdev)
{
	struct w90p910_ether *ether;
	struct net_device *dev;
	int error;

	dev = alloc_etherdev(sizeof(struct w90p910_ether));
	if (!dev)
		return -ENOMEM;

	ether = netdev_priv(dev);

	ether->res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (ether->res == NULL) {
		dev_err(&pdev->dev, "failed to get I/O memory\n");
		error = -ENXIO;
		goto failed_free;
	}

	if (!request_mem_region(ether->res->start,
				resource_size(ether->res), pdev->name)) {
		dev_err(&pdev->dev, "failed to request I/O memory\n");
		error = -EBUSY;
		goto failed_free;
	}

	ether->reg = ioremap(ether->res->start, resource_size(ether->res));
	if (ether->reg == NULL) {
		dev_err(&pdev->dev, "failed to remap I/O memory\n");
		error = -ENXIO;
		goto failed_free_mem;
	}

	ether->txirq = platform_get_irq(pdev, 0);
	if (ether->txirq < 0) {
		dev_err(&pdev->dev, "failed to get ether tx irq\n");
		error = -ENXIO;
		goto failed_free_io;
	}

	ether->rxirq = platform_get_irq(pdev, 1);
	if (ether->rxirq < 0) {
		dev_err(&pdev->dev, "failed to get ether rx irq\n");
		error = -ENXIO;
		goto failed_free_io;
	}

	platform_set_drvdata(pdev, dev);

	ether->clk = clk_get(&pdev->dev, NULL);
	if (IS_ERR(ether->clk)) {
		dev_err(&pdev->dev, "failed to get ether clock\n");
		error = PTR_ERR(ether->clk);
		goto failed_free_io;
	}

	ether->rmiiclk = clk_get(&pdev->dev, "RMII");
	if (IS_ERR(ether->rmiiclk)) {
		dev_err(&pdev->dev, "failed to get ether clock\n");
		error = PTR_ERR(ether->rmiiclk);
		goto failed_put_clk;
	}

	ether->pdev = pdev;

	w90p910_ether_setup(dev);

	error = register_netdev(dev);
	if (error != 0) {
		dev_err(&pdev->dev, "Register EMC w90p910 FAILED\n");
		error = -ENODEV;
		goto failed_put_rmiiclk;
	}

	return 0;
failed_put_rmiiclk:
	clk_put(ether->rmiiclk);
failed_put_clk:
	clk_put(ether->clk);
failed_free_io:
	iounmap(ether->reg);
failed_free_mem:
	release_mem_region(ether->res->start, resource_size(ether->res));
failed_free:
	free_netdev(dev);
	return error;
}