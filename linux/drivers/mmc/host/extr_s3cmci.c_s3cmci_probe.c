#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct s3cmci_host {int clk_div; scalar_t__ irq; int irq_state; int clk_rate; TYPE_2__* mem; int /*<<< orphan*/  base; int /*<<< orphan*/  dma; int /*<<< orphan*/ * clk; int /*<<< orphan*/  irq_cd; scalar_t__ is2440; TYPE_1__* pdata; int /*<<< orphan*/  pio_active; int /*<<< orphan*/  complete_what; int /*<<< orphan*/  sdidata; int /*<<< orphan*/  sdiimsk; int /*<<< orphan*/  pio_tasklet; int /*<<< orphan*/  complete_lock; struct platform_device* pdev; struct mmc_host* mmc; } ;
struct TYPE_12__ {scalar_t__ of_node; TYPE_1__* platform_data; } ;
struct platform_device {TYPE_5__ dev; int /*<<< orphan*/  name; } ;
struct mmc_host {int ocr_avail; int caps; int f_min; int f_max; int max_blk_count; int max_blk_size; int max_req_size; int max_seg_size; int max_segs; int /*<<< orphan*/ * ops; } ;
struct TYPE_11__ {int /*<<< orphan*/  start; } ;
struct TYPE_10__ {int ocr_avail; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPLETION_NONE ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int MMC_CAP_4_BIT_DATA ; 
 int MMC_CAP_SDIO_IRQ ; 
 int MMC_VDD_32_33 ; 
 int MMC_VDD_33_34 ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int S3C2410_GPE (int) ; 
 int /*<<< orphan*/  S3C2410_SDIDATA ; 
 int /*<<< orphan*/  S3C2410_SDIIMSK ; 
 int /*<<< orphan*/  S3C2440_SDIDATA ; 
 int /*<<< orphan*/  S3C2440_SDIIMSK ; 
 int /*<<< orphan*/  XFER_NONE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * clk_get (TYPE_5__*,char*) ; 
 int clk_get_rate (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg (struct s3cmci_host*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_debug ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_5__*,char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  disable_irq (scalar_t__) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_request_chan (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct s3cmci_host*) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int mmc_add_host (struct mmc_host*) ; 
 struct mmc_host* mmc_alloc_host (int,TYPE_5__*) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 struct s3cmci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  pio_tasklet ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 TYPE_2__* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mmc_host*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s3cmci_host*) ; 
 TYPE_2__* request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_2__*) ; 
 int /*<<< orphan*/  s3cmci_cpufreq_deregister (struct s3cmci_host*) ; 
 int s3cmci_cpufreq_register (struct s3cmci_host*) ; 
 int /*<<< orphan*/  s3cmci_debugfs_attach (struct s3cmci_host*) ; 
 scalar_t__ s3cmci_host_usedma (struct s3cmci_host*) ; 
 int /*<<< orphan*/  s3cmci_irq ; 
 int /*<<< orphan*/  s3cmci_ops ; 
 int s3cmci_probe_dt (struct s3cmci_host*) ; 
 int s3cmci_probe_pdata (struct s3cmci_host*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int s3cmci_probe(struct platform_device *pdev)
{
	struct s3cmci_host *host;
	struct mmc_host	*mmc;
	int ret;
	int i;

	mmc = mmc_alloc_host(sizeof(struct s3cmci_host), &pdev->dev);
	if (!mmc) {
		ret = -ENOMEM;
		goto probe_out;
	}

	host = mmc_priv(mmc);
	host->mmc 	= mmc;
	host->pdev	= pdev;

	if (pdev->dev.of_node)
		ret = s3cmci_probe_dt(host);
	else
		ret = s3cmci_probe_pdata(host);

	if (ret)
		goto probe_free_host;

	host->pdata = pdev->dev.platform_data;

	spin_lock_init(&host->complete_lock);
	tasklet_init(&host->pio_tasklet, pio_tasklet, (unsigned long) host);

	if (host->is2440) {
		host->sdiimsk	= S3C2440_SDIIMSK;
		host->sdidata	= S3C2440_SDIDATA;
		host->clk_div	= 1;
	} else {
		host->sdiimsk	= S3C2410_SDIIMSK;
		host->sdidata	= S3C2410_SDIDATA;
		host->clk_div	= 2;
	}

	host->complete_what 	= COMPLETION_NONE;
	host->pio_active 	= XFER_NONE;

	host->mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!host->mem) {
		dev_err(&pdev->dev,
			"failed to get io memory region resource.\n");

		ret = -ENOENT;
		goto probe_free_gpio;
	}

	host->mem = request_mem_region(host->mem->start,
				       resource_size(host->mem), pdev->name);

	if (!host->mem) {
		dev_err(&pdev->dev, "failed to request io memory region.\n");
		ret = -ENOENT;
		goto probe_free_gpio;
	}

	host->base = ioremap(host->mem->start, resource_size(host->mem));
	if (!host->base) {
		dev_err(&pdev->dev, "failed to ioremap() io memory region.\n");
		ret = -EINVAL;
		goto probe_free_mem_region;
	}

	host->irq = platform_get_irq(pdev, 0);
	if (host->irq <= 0) {
		ret = -EINVAL;
		goto probe_iounmap;
	}

	if (request_irq(host->irq, s3cmci_irq, 0, DRIVER_NAME, host)) {
		dev_err(&pdev->dev, "failed to request mci interrupt.\n");
		ret = -ENOENT;
		goto probe_iounmap;
	}

	/* We get spurious interrupts even when we have set the IMSK
	 * register to ignore everything, so use disable_irq() to make
	 * ensure we don't lock the system with un-serviceable requests. */

	disable_irq(host->irq);
	host->irq_state = false;

	/* Depending on the dma state, get a DMA channel to use. */

	if (s3cmci_host_usedma(host)) {
		host->dma = dma_request_chan(&pdev->dev, "rx-tx");
		ret = PTR_ERR_OR_ZERO(host->dma);
		if (ret) {
			dev_err(&pdev->dev, "cannot get DMA channel.\n");
			goto probe_free_irq;
		}
	}

	host->clk = clk_get(&pdev->dev, "sdi");
	if (IS_ERR(host->clk)) {
		dev_err(&pdev->dev, "failed to find clock source.\n");
		ret = PTR_ERR(host->clk);
		host->clk = NULL;
		goto probe_free_dma;
	}

	ret = clk_prepare_enable(host->clk);
	if (ret) {
		dev_err(&pdev->dev, "failed to enable clock source.\n");
		goto clk_free;
	}

	host->clk_rate = clk_get_rate(host->clk);

	mmc->ops 	= &s3cmci_ops;
	mmc->ocr_avail	= MMC_VDD_32_33 | MMC_VDD_33_34;
#ifdef CONFIG_MMC_S3C_HW_SDIO_IRQ
	mmc->caps	= MMC_CAP_4_BIT_DATA | MMC_CAP_SDIO_IRQ;
#else
	mmc->caps	= MMC_CAP_4_BIT_DATA;
#endif
	mmc->f_min 	= host->clk_rate / (host->clk_div * 256);
	mmc->f_max 	= host->clk_rate / host->clk_div;

	if (host->pdata->ocr_avail)
		mmc->ocr_avail = host->pdata->ocr_avail;

	mmc->max_blk_count	= 4095;
	mmc->max_blk_size	= 4095;
	mmc->max_req_size	= 4095 * 512;
	mmc->max_seg_size	= mmc->max_req_size;

	mmc->max_segs		= 128;

	dbg(host, dbg_debug,
	    "probe: mode:%s mapped mci_base:%p irq:%u irq_cd:%u dma:%p.\n",
	    (host->is2440?"2440":""),
	    host->base, host->irq, host->irq_cd, host->dma);

	ret = s3cmci_cpufreq_register(host);
	if (ret) {
		dev_err(&pdev->dev, "failed to register cpufreq\n");
		goto free_dmabuf;
	}

	ret = mmc_add_host(mmc);
	if (ret) {
		dev_err(&pdev->dev, "failed to add mmc host.\n");
		goto free_cpufreq;
	}

	s3cmci_debugfs_attach(host);

	platform_set_drvdata(pdev, mmc);
	dev_info(&pdev->dev, "%s - using %s, %s SDIO IRQ\n", mmc_hostname(mmc),
		 s3cmci_host_usedma(host) ? "dma" : "pio",
		 mmc->caps & MMC_CAP_SDIO_IRQ ? "hw" : "sw");

	return 0;

 free_cpufreq:
	s3cmci_cpufreq_deregister(host);

 free_dmabuf:
	clk_disable_unprepare(host->clk);

 clk_free:
	clk_put(host->clk);

 probe_free_dma:
	if (s3cmci_host_usedma(host))
		dma_release_channel(host->dma);

 probe_free_irq:
	free_irq(host->irq, host);

 probe_iounmap:
	iounmap(host->base);

 probe_free_mem_region:
	release_mem_region(host->mem->start, resource_size(host->mem));

 probe_free_gpio:
	if (!pdev->dev.of_node)
		for (i = S3C2410_GPE(5); i <= S3C2410_GPE(10); i++)
			gpio_free(i);

 probe_free_host:
	mmc_free_host(mmc);

 probe_out:
	return ret;
}