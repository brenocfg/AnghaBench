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
struct platform_device_id {int /*<<< orphan*/  driver_data; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  id_entry; int /*<<< orphan*/  name; } ;
struct of_device_id {int /*<<< orphan*/  data; } ;
struct mmc_host {int caps; int ocr_avail; int max_segs; int max_seg_size; int max_blk_size; int max_blk_count; int max_req_size; int /*<<< orphan*/ * ops; } ;
struct mmc_davinci_host {scalar_t__ nr_sg; int mmc_irq; int sdio_irq; int /*<<< orphan*/  clk; scalar_t__ use_dma; struct mmc_host* mmc; int /*<<< orphan*/  version; int /*<<< orphan*/  mmc_input_clk; int /*<<< orphan*/  base; struct resource* mem_res; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX_CCNT ; 
 scalar_t__ MAX_NR_SG ; 
 int MMC_CAP_4_BIT_DATA ; 
 int MMC_CAP_SDIO_IRQ ; 
 int MMC_CAP_WAIT_WHILE_BUSY ; 
 int MMC_VDD_32_33 ; 
 int MMC_VDD_33_34 ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int davinci_acquire_dma_channels (struct mmc_davinci_host*) ; 
 int /*<<< orphan*/  davinci_mmc_dt_ids ; 
 int /*<<< orphan*/  davinci_release_dma_channels (struct mmc_davinci_host*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mmc_davinci_host*) ; 
 struct resource* devm_request_mem_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_mmcsd_host (struct mmc_davinci_host*) ; 
 int mmc_add_host (struct mmc_host*) ; 
 struct mmc_host* mmc_alloc_host (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_davinci_cpufreq_deregister (struct mmc_davinci_host*) ; 
 int mmc_davinci_cpufreq_register (struct mmc_davinci_host*) ; 
 int /*<<< orphan*/  mmc_davinci_irq ; 
 int /*<<< orphan*/  mmc_davinci_ops ; 
 int mmc_davinci_parse_pdata (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_davinci_sdio_irq ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int mmc_of_parse (struct mmc_host*) ; 
 struct mmc_davinci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct platform_device_id* platform_get_device_id (struct platform_device*) ; 
 void* platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mmc_davinci_host*) ; 
 int /*<<< orphan*/  rename_region (struct resource*,int /*<<< orphan*/ ) ; 
 size_t resource_size (struct resource*) ; 
 int rw_threshold ; 
 scalar_t__ use_dma ; 

__attribute__((used)) static int davinci_mmcsd_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	struct mmc_davinci_host *host = NULL;
	struct mmc_host *mmc = NULL;
	struct resource *r, *mem = NULL;
	int ret, irq;
	size_t mem_size;
	const struct platform_device_id *id_entry;

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!r)
		return -ENODEV;
	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	mem_size = resource_size(r);
	mem = devm_request_mem_region(&pdev->dev, r->start, mem_size,
				      pdev->name);
	if (!mem)
		return -EBUSY;

	mmc = mmc_alloc_host(sizeof(struct mmc_davinci_host), &pdev->dev);
	if (!mmc)
		return -ENOMEM;

	host = mmc_priv(mmc);
	host->mmc = mmc;	/* Important */

	host->mem_res = mem;
	host->base = devm_ioremap(&pdev->dev, mem->start, mem_size);
	if (!host->base) {
		ret = -ENOMEM;
		goto ioremap_fail;
	}

	host->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(host->clk)) {
		ret = PTR_ERR(host->clk);
		goto clk_get_fail;
	}
	ret = clk_prepare_enable(host->clk);
	if (ret)
		goto clk_prepare_enable_fail;

	host->mmc_input_clk = clk_get_rate(host->clk);

	match = of_match_device(davinci_mmc_dt_ids, &pdev->dev);
	if (match) {
		pdev->id_entry = match->data;
		ret = mmc_of_parse(mmc);
		if (ret) {
			if (ret != -EPROBE_DEFER)
				dev_err(&pdev->dev,
					"could not parse of data: %d\n", ret);
			goto parse_fail;
		}
	} else {
		ret = mmc_davinci_parse_pdata(mmc);
		if (ret) {
			dev_err(&pdev->dev,
				"could not parse platform data: %d\n", ret);
			goto parse_fail;
	}	}

	if (host->nr_sg > MAX_NR_SG || !host->nr_sg)
		host->nr_sg = MAX_NR_SG;

	init_mmcsd_host(host);

	host->use_dma = use_dma;
	host->mmc_irq = irq;
	host->sdio_irq = platform_get_irq(pdev, 1);

	if (host->use_dma) {
		ret = davinci_acquire_dma_channels(host);
		if (ret == -EPROBE_DEFER)
			goto dma_probe_defer;
		else if (ret)
			host->use_dma = 0;
	}

	mmc->caps |= MMC_CAP_WAIT_WHILE_BUSY;

	id_entry = platform_get_device_id(pdev);
	if (id_entry)
		host->version = id_entry->driver_data;

	mmc->ops = &mmc_davinci_ops;
	mmc->ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34;

	/* With no iommu coalescing pages, each phys_seg is a hw_seg.
	 * Each hw_seg uses one EDMA parameter RAM slot, always one
	 * channel and then usually some linked slots.
	 */
	mmc->max_segs		= MAX_NR_SG;

	/* EDMA limit per hw segment (one or two MBytes) */
	mmc->max_seg_size	= MAX_CCNT * rw_threshold;

	/* MMC/SD controller limits for multiblock requests */
	mmc->max_blk_size	= 4095;  /* BLEN is 12 bits */
	mmc->max_blk_count	= 65535; /* NBLK is 16 bits */
	mmc->max_req_size	= mmc->max_blk_size * mmc->max_blk_count;

	dev_dbg(mmc_dev(host->mmc), "max_segs=%d\n", mmc->max_segs);
	dev_dbg(mmc_dev(host->mmc), "max_blk_size=%d\n", mmc->max_blk_size);
	dev_dbg(mmc_dev(host->mmc), "max_req_size=%d\n", mmc->max_req_size);
	dev_dbg(mmc_dev(host->mmc), "max_seg_size=%d\n", mmc->max_seg_size);

	platform_set_drvdata(pdev, host);

	ret = mmc_davinci_cpufreq_register(host);
	if (ret) {
		dev_err(&pdev->dev, "failed to register cpufreq\n");
		goto cpu_freq_fail;
	}

	ret = mmc_add_host(mmc);
	if (ret < 0)
		goto mmc_add_host_fail;

	ret = devm_request_irq(&pdev->dev, irq, mmc_davinci_irq, 0,
			       mmc_hostname(mmc), host);
	if (ret)
		goto request_irq_fail;

	if (host->sdio_irq >= 0) {
		ret = devm_request_irq(&pdev->dev, host->sdio_irq,
				       mmc_davinci_sdio_irq, 0,
				       mmc_hostname(mmc), host);
		if (!ret)
			mmc->caps |= MMC_CAP_SDIO_IRQ;
	}

	rename_region(mem, mmc_hostname(mmc));

	dev_info(mmc_dev(host->mmc), "Using %s, %d-bit mode\n",
		host->use_dma ? "DMA" : "PIO",
		(mmc->caps & MMC_CAP_4_BIT_DATA) ? 4 : 1);

	return 0;

request_irq_fail:
	mmc_remove_host(mmc);
mmc_add_host_fail:
	mmc_davinci_cpufreq_deregister(host);
cpu_freq_fail:
	davinci_release_dma_channels(host);
parse_fail:
dma_probe_defer:
	clk_disable_unprepare(host->clk);
clk_prepare_enable_fail:
clk_get_fail:
ioremap_fail:
	mmc_free_host(mmc);

	return ret;
}