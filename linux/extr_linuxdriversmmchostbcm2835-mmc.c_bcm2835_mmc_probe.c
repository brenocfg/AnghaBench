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
struct resource {scalar_t__ start; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct mmc_host {int /*<<< orphan*/  caps; int /*<<< orphan*/ * ops; } ;
struct device_node {int dummy; } ;
struct clk {int dummy; } ;
struct bcm2835_host {scalar_t__ irq; void* dma_chan_rxtx; int /*<<< orphan*/  overclock_50; int /*<<< orphan*/  max_clk; scalar_t__ bus_addr; struct clk* ioaddr; int /*<<< orphan*/  lock; int /*<<< orphan*/  timeout; struct mmc_host* mmc; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  MMC_CAP_4_BIT_DATA ; 
 int PTR_ERR (struct clk*) ; 
 int bcm2835_mmc_add_host (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_ops ; 
 scalar_t__ be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct clk* devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct clk* devm_ioremap_resource (struct device*,struct resource*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (void*) ; 
 void* dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* dma_request_slave_channel (struct device*,char*) ; 
 struct mmc_host* mmc_alloc_host (int,struct device*) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_of_parse (struct mmc_host*) ; 
 struct bcm2835_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/ * of_get_address (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bcm2835_host*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2835_mmc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *node = dev->of_node;
	struct clk *clk;
	struct resource *iomem;
	struct bcm2835_host *host;
	struct mmc_host *mmc;
	const __be32 *addr;
	int ret;

	mmc = mmc_alloc_host(sizeof(*host), dev);
	if (!mmc)
		return -ENOMEM;

	mmc->ops = &bcm2835_ops;
	host = mmc_priv(mmc);
	host->mmc = mmc;
	host->timeout = msecs_to_jiffies(1000);
	spin_lock_init(&host->lock);

	iomem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	host->ioaddr = devm_ioremap_resource(dev, iomem);
	if (IS_ERR(host->ioaddr)) {
		ret = PTR_ERR(host->ioaddr);
		goto err;
	}

	addr = of_get_address(node, 0, NULL, NULL);
	if (!addr) {
		dev_err(dev, "could not get DMA-register address\n");
		ret = -ENODEV;
		goto err;
	}
	host->bus_addr = be32_to_cpup(addr);
	pr_debug(" - ioaddr %lx, iomem->start %lx, bus_addr %lx\n",
		 (unsigned long)host->ioaddr,
		 (unsigned long)iomem->start,
		 (unsigned long)host->bus_addr);

#ifndef FORCE_PIO
	if (node) {
		host->dma_chan_rxtx = dma_request_slave_channel(dev, "rx-tx");
		if (!host->dma_chan_rxtx)
			host->dma_chan_rxtx =
				dma_request_slave_channel(dev, "tx");
		if (!host->dma_chan_rxtx)
			host->dma_chan_rxtx =
				dma_request_slave_channel(dev, "rx");
	} else {
		dma_cap_mask_t mask;

		dma_cap_zero(mask);
		/* we don't care about the channel, any would work */
		dma_cap_set(DMA_SLAVE, mask);
		host->dma_chan_rxtx = dma_request_channel(mask, NULL, NULL);
	}
#endif
	clk = devm_clk_get(dev, NULL);
	if (IS_ERR(clk)) {
		ret = PTR_ERR(clk);
		if (ret == -EPROBE_DEFER)
			dev_info(dev, "could not get clk, deferring probe\n");
		else
			dev_err(dev, "could not get clk\n");
		goto err;
	}

	host->max_clk = clk_get_rate(clk);

	host->irq = platform_get_irq(pdev, 0);
	if (host->irq <= 0) {
		dev_err(dev, "get IRQ failed\n");
		ret = -EINVAL;
		goto err;
	}

	if (node) {
		mmc_of_parse(mmc);

		/* Read any custom properties */
		of_property_read_u32(node,
				     "brcm,overclock-50",
				     &host->overclock_50);
	} else {
		mmc->caps |= MMC_CAP_4_BIT_DATA;
	}

	ret = bcm2835_mmc_add_host(host);
	if (ret)
		goto err;

	platform_set_drvdata(pdev, host);

	return 0;
err:
	if (host->dma_chan_rxtx)
		dma_release_channel(host->dma_chan_rxtx);
	mmc_free_host(mmc);

	return ret;
}