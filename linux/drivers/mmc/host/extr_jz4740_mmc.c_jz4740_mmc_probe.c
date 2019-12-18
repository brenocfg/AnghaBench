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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct mmc_host {int f_max; int f_min; int ocr_avail; int max_blk_size; int max_blk_count; int max_req_size; int max_segs; int max_seg_size; int caps; int /*<<< orphan*/ * ops; } ;
struct jz4740_mmc_host {int version; int irq; int use_dma; int /*<<< orphan*/  timeout_timer; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  lock; struct platform_device* pdev; struct mmc_host* mmc; int /*<<< orphan*/  base; int /*<<< orphan*/  mem_res; int /*<<< orphan*/  clk; } ;
typedef  enum jz4740_mmc_version { ____Placeholder_jz4740_mmc_version } jz4740_mmc_version ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int JZ_MMC_CLK_RATE ; 
 int JZ_MMC_JZ4740 ; 
 int MMC_CAP_4_BIT_DATA ; 
 int MMC_VDD_32_33 ; 
 int MMC_VDD_33_34 ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int,struct jz4740_mmc_host*) ; 
 int jz4740_mmc_acquire_dma_channels (struct jz4740_mmc_host*) ; 
 int /*<<< orphan*/  jz4740_mmc_clock_disable (struct jz4740_mmc_host*) ; 
 int /*<<< orphan*/  jz4740_mmc_of_match ; 
 int /*<<< orphan*/  jz4740_mmc_ops ; 
 int /*<<< orphan*/  jz4740_mmc_release_dma_channels (struct jz4740_mmc_host*) ; 
 int /*<<< orphan*/  jz4740_mmc_reset (struct jz4740_mmc_host*) ; 
 int /*<<< orphan*/  jz4740_mmc_timeout ; 
 int /*<<< orphan*/  jz_mmc_irq ; 
 int /*<<< orphan*/  jz_mmc_irq_worker ; 
 int mmc_add_host (struct mmc_host*) ; 
 struct mmc_host* mmc_alloc_host (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 int mmc_of_parse (struct mmc_host*) ; 
 struct jz4740_mmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_regulator_get_supply (struct mmc_host*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct jz4740_mmc_host*) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jz4740_mmc_host*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jz4740_mmc_probe(struct platform_device* pdev)
{
	int ret;
	struct mmc_host *mmc;
	struct jz4740_mmc_host *host;
	const struct of_device_id *match;

	mmc = mmc_alloc_host(sizeof(struct jz4740_mmc_host), &pdev->dev);
	if (!mmc) {
		dev_err(&pdev->dev, "Failed to alloc mmc host structure\n");
		return -ENOMEM;
	}

	host = mmc_priv(mmc);

	match = of_match_device(jz4740_mmc_of_match, &pdev->dev);
	if (match) {
		host->version = (enum jz4740_mmc_version)match->data;
	} else {
		/* JZ4740 should be the only one using legacy probe */
		host->version = JZ_MMC_JZ4740;
	}

	ret = mmc_of_parse(mmc);
	if (ret) {
		if (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev,
				"could not parse device properties: %d\n", ret);
		goto err_free_host;
	}

	mmc_regulator_get_supply(mmc);

	host->irq = platform_get_irq(pdev, 0);
	if (host->irq < 0) {
		ret = host->irq;
		goto err_free_host;
	}

	host->clk = devm_clk_get(&pdev->dev, "mmc");
	if (IS_ERR(host->clk)) {
		ret = PTR_ERR(host->clk);
		dev_err(&pdev->dev, "Failed to get mmc clock\n");
		goto err_free_host;
	}

	host->mem_res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	host->base = devm_ioremap_resource(&pdev->dev, host->mem_res);
	if (IS_ERR(host->base)) {
		ret = PTR_ERR(host->base);
		dev_err(&pdev->dev, "Failed to ioremap base memory\n");
		goto err_free_host;
	}

	mmc->ops = &jz4740_mmc_ops;
	if (!mmc->f_max)
		mmc->f_max = JZ_MMC_CLK_RATE;
	mmc->f_min = mmc->f_max / 128;
	mmc->ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34;

	mmc->max_blk_size = (1 << 10) - 1;
	mmc->max_blk_count = (1 << 15) - 1;
	mmc->max_req_size = mmc->max_blk_size * mmc->max_blk_count;

	mmc->max_segs = 128;
	mmc->max_seg_size = mmc->max_req_size;

	host->mmc = mmc;
	host->pdev = pdev;
	spin_lock_init(&host->lock);
	host->irq_mask = ~0;

	jz4740_mmc_reset(host);

	ret = request_threaded_irq(host->irq, jz_mmc_irq, jz_mmc_irq_worker, 0,
			dev_name(&pdev->dev), host);
	if (ret) {
		dev_err(&pdev->dev, "Failed to request irq: %d\n", ret);
		goto err_free_host;
	}

	jz4740_mmc_clock_disable(host);
	timer_setup(&host->timeout_timer, jz4740_mmc_timeout, 0);

	ret = jz4740_mmc_acquire_dma_channels(host);
	if (ret == -EPROBE_DEFER)
		goto err_free_irq;
	host->use_dma = !ret;

	platform_set_drvdata(pdev, host);
	ret = mmc_add_host(mmc);

	if (ret) {
		dev_err(&pdev->dev, "Failed to add mmc host: %d\n", ret);
		goto err_release_dma;
	}
	dev_info(&pdev->dev, "JZ SD/MMC card driver registered\n");

	dev_info(&pdev->dev, "Using %s, %d-bit mode\n",
		 host->use_dma ? "DMA" : "PIO",
		 (mmc->caps & MMC_CAP_4_BIT_DATA) ? 4 : 1);

	return 0;

err_release_dma:
	if (host->use_dma)
		jz4740_mmc_release_dma_channels(host);
err_free_irq:
	free_irq(host->irq, host);
err_free_host:
	mmc_free_host(mmc);

	return ret;
}