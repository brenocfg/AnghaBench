#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct sunxi_mmc_host {int use_new_timings; int /*<<< orphan*/  sg_dma; int /*<<< orphan*/  sg_cpu; TYPE_1__* cfg; int /*<<< orphan*/  clk_mmc; int /*<<< orphan*/  lock; struct mmc_host* mmc; TYPE_2__* dev; } ;
struct sunxi_idma_des {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct mmc_host {int max_blk_count; int max_blk_size; int max_segs; int max_seg_size; int max_req_size; int f_min; int f_max; int caps; int /*<<< orphan*/  caps2; int /*<<< orphan*/ * ops; } ;
struct TYPE_12__ {int idma_des_size_bits; scalar_t__ clk_delays; scalar_t__ needs_new_timings; scalar_t__ ccu_has_timings_switch; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MMC_CAP2_HS200 ; 
 int /*<<< orphan*/  MMC_CAP2_HS400 ; 
 int MMC_CAP_1_2V_DDR ; 
 int MMC_CAP_1_8V_DDR ; 
 int MMC_CAP_3_3V_DDR ; 
 int MMC_CAP_ERASE ; 
 int MMC_CAP_MMC_HIGHSPEED ; 
 int MMC_CAP_SDIO_IRQ ; 
 int MMC_CAP_SD_HIGHSPEED ; 
 int MMC_CAP_UHS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mmc_add_host (struct mmc_host*) ; 
 struct mmc_host* mmc_alloc_host (int,TYPE_2__*) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 int mmc_of_parse (struct mmc_host*) ; 
 struct sunxi_mmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mmc_host*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_2__*,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int sunxi_ccu_get_mmc_timing_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunxi_ccu_set_mmc_timing_mode (int /*<<< orphan*/ ,int) ; 
 int sunxi_mmc_init_host (struct sunxi_mmc_host*) ; 
 int /*<<< orphan*/  sunxi_mmc_ops ; 
 int sunxi_mmc_resource_request (struct sunxi_mmc_host*,struct platform_device*) ; 

__attribute__((used)) static int sunxi_mmc_probe(struct platform_device *pdev)
{
	struct sunxi_mmc_host *host;
	struct mmc_host *mmc;
	int ret;

	mmc = mmc_alloc_host(sizeof(struct sunxi_mmc_host), &pdev->dev);
	if (!mmc) {
		dev_err(&pdev->dev, "mmc alloc host failed\n");
		return -ENOMEM;
	}
	platform_set_drvdata(pdev, mmc);

	host = mmc_priv(mmc);
	host->dev = &pdev->dev;
	host->mmc = mmc;
	spin_lock_init(&host->lock);

	ret = sunxi_mmc_resource_request(host, pdev);
	if (ret)
		goto error_free_host;

	host->sg_cpu = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
					  &host->sg_dma, GFP_KERNEL);
	if (!host->sg_cpu) {
		dev_err(&pdev->dev, "Failed to allocate DMA descriptor mem\n");
		ret = -ENOMEM;
		goto error_free_host;
	}

	if (host->cfg->ccu_has_timings_switch) {
		/*
		 * Supports both old and new timing modes.
		 * Try setting the clk to new timing mode.
		 */
		sunxi_ccu_set_mmc_timing_mode(host->clk_mmc, true);

		/* And check the result */
		ret = sunxi_ccu_get_mmc_timing_mode(host->clk_mmc);
		if (ret < 0) {
			/*
			 * For whatever reason we were not able to get
			 * the current active mode. Default to old mode.
			 */
			dev_warn(&pdev->dev, "MMC clk timing mode unknown\n");
			host->use_new_timings = false;
		} else {
			host->use_new_timings = !!ret;
		}
	} else if (host->cfg->needs_new_timings) {
		/* Supports new timing mode only */
		host->use_new_timings = true;
	}

	mmc->ops		= &sunxi_mmc_ops;
	mmc->max_blk_count	= 8192;
	mmc->max_blk_size	= 4096;
	mmc->max_segs		= PAGE_SIZE / sizeof(struct sunxi_idma_des);
	mmc->max_seg_size	= (1 << host->cfg->idma_des_size_bits);
	mmc->max_req_size	= mmc->max_seg_size * mmc->max_segs;
	/* 400kHz ~ 52MHz */
	mmc->f_min		=   400000;
	mmc->f_max		= 52000000;
	mmc->caps	       |= MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED |
				  MMC_CAP_ERASE | MMC_CAP_SDIO_IRQ;

	/*
	 * Some H5 devices do not have signal traces precise enough to
	 * use HS DDR mode for their eMMC chips.
	 *
	 * We still enable HS DDR modes for all the other controller
	 * variants that support them.
	 */
	if ((host->cfg->clk_delays || host->use_new_timings) &&
	    !of_device_is_compatible(pdev->dev.of_node,
				     "allwinner,sun50i-h5-emmc"))
		mmc->caps      |= MMC_CAP_1_8V_DDR | MMC_CAP_3_3V_DDR;

	ret = mmc_of_parse(mmc);
	if (ret)
		goto error_free_dma;

	/*
	 * If we don't support delay chains in the SoC, we can't use any
	 * of the higher speed modes. Mask them out in case the device
	 * tree specifies the properties for them, which gets added to
	 * the caps by mmc_of_parse() above.
	 */
	if (!(host->cfg->clk_delays || host->use_new_timings)) {
		mmc->caps &= ~(MMC_CAP_3_3V_DDR | MMC_CAP_1_8V_DDR |
			       MMC_CAP_1_2V_DDR | MMC_CAP_UHS);
		mmc->caps2 &= ~MMC_CAP2_HS200;
	}

	/* TODO: This driver doesn't support HS400 mode yet */
	mmc->caps2 &= ~MMC_CAP2_HS400;

	ret = sunxi_mmc_init_host(host);
	if (ret)
		goto error_free_dma;

	pm_runtime_set_active(&pdev->dev);
	pm_runtime_set_autosuspend_delay(&pdev->dev, 50);
	pm_runtime_use_autosuspend(&pdev->dev);
	pm_runtime_enable(&pdev->dev);

	ret = mmc_add_host(mmc);
	if (ret)
		goto error_free_dma;

	dev_info(&pdev->dev, "initialized, max. request size: %u KB%s\n",
		 mmc->max_req_size >> 10,
		 host->use_new_timings ? ", uses new timings mode" : "");

	return 0;

error_free_dma:
	dma_free_coherent(&pdev->dev, PAGE_SIZE, host->sg_cpu, host->sg_dma);
error_free_host:
	mmc_free_host(mmc);
	return ret;
}