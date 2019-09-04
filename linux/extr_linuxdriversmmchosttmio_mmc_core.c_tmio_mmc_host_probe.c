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
struct TYPE_2__ {int /*<<< orphan*/  get_cd; int /*<<< orphan*/  get_ro; } ;
struct tmio_mmc_host {int native_hotplug; int sdio_irq_enabled; int /*<<< orphan*/  done; int /*<<< orphan*/  delayed_reset_work; int /*<<< orphan*/  ios_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  sdcard_irq_mask; int /*<<< orphan*/  sdio_irq_mask; TYPE_1__ ops; int /*<<< orphan*/  set_clk_div; int /*<<< orphan*/  set_pwr; int /*<<< orphan*/ * write16_hook; struct mmc_host* mmc; struct tmio_mmc_data* pdata; struct platform_device* pdev; } ;
struct tmio_mmc_data {int flags; int capabilities; scalar_t__ max_blk_count; scalar_t__ max_segs; int /*<<< orphan*/  capabilities2; int /*<<< orphan*/  cd_gpio; int /*<<< orphan*/  set_clk_div; int /*<<< orphan*/  set_pwr; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mmc_host {scalar_t__ f_min; int caps; int max_segs; int max_blk_size; int max_blk_count; int max_req_size; unsigned int max_seg_size; int /*<<< orphan*/  caps2; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_IRQ_MASK ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IO_TLB_SEGSIZE ; 
 int IO_TLB_SHIFT ; 
 int MMC_CAP_4_BIT_DATA ; 
 int MMC_CAP_NEEDS_POLL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TMIO_MASK_ALL ; 
 int TMIO_MMC_HAS_IDLE_WAIT ; 
 int TMIO_MMC_MIN_RCAR2 ; 
 int TMIO_MMC_SDIO_IRQ ; 
 int TMIO_MMC_USE_GPIO_CD ; 
 int /*<<< orphan*/  TMIO_SDIO_MASK_ALL ; 
 int TMIO_STAT_CARD_INSERT ; 
 int TMIO_STAT_CARD_REMOVE ; 
 int /*<<< orphan*/  dev_pm_qos_expose_latency_limit (int /*<<< orphan*/ *,int) ; 
 int mmc_add_host (struct mmc_host*) ; 
 scalar_t__ mmc_can_gpio_cd (struct mmc_host*) ; 
 scalar_t__ mmc_can_gpio_ro (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_card_is_removable (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_gpio_get_cd ; 
 int /*<<< orphan*/  mmc_gpio_get_ro ; 
 int mmc_gpio_request_cd (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_ctrl_read16_and_16_as_32 (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ swiotlb_max_segment () ; 
 int /*<<< orphan*/  tmio_mmc_clk_stop (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  tmio_mmc_disable_mmc_irqs (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmio_mmc_done_work ; 
 int /*<<< orphan*/  tmio_mmc_enable_mmc_irqs (struct tmio_mmc_host*,int) ; 
 int /*<<< orphan*/  tmio_mmc_host_remove (struct tmio_mmc_host*) ; 
 int tmio_mmc_init_ocr (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  tmio_mmc_request_dma (struct tmio_mmc_host*,struct tmio_mmc_data*) ; 
 int /*<<< orphan*/  tmio_mmc_reset (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  tmio_mmc_reset_work ; 

int tmio_mmc_host_probe(struct tmio_mmc_host *_host)
{
	struct platform_device *pdev = _host->pdev;
	struct tmio_mmc_data *pdata = _host->pdata;
	struct mmc_host *mmc = _host->mmc;
	int ret;

	/*
	 * Check the sanity of mmc->f_min to prevent tmio_mmc_set_clock() from
	 * looping forever...
	 */
	if (mmc->f_min == 0)
		return -EINVAL;

	if (!(pdata->flags & TMIO_MMC_HAS_IDLE_WAIT))
		_host->write16_hook = NULL;

	_host->set_pwr = pdata->set_pwr;
	_host->set_clk_div = pdata->set_clk_div;

	ret = tmio_mmc_init_ocr(_host);
	if (ret < 0)
		return ret;

	if (pdata->flags & TMIO_MMC_USE_GPIO_CD) {
		ret = mmc_gpio_request_cd(mmc, pdata->cd_gpio, 0);
		if (ret)
			return ret;
	}

	mmc->caps |= MMC_CAP_4_BIT_DATA | pdata->capabilities;
	mmc->caps2 |= pdata->capabilities2;
	mmc->max_segs = pdata->max_segs ? : 32;
	mmc->max_blk_size = 512;
	mmc->max_blk_count = pdata->max_blk_count ? :
		(PAGE_SIZE / mmc->max_blk_size) * mmc->max_segs;
	mmc->max_req_size = mmc->max_blk_size * mmc->max_blk_count;
	/*
	 * Since swiotlb has memory size limitation, this will calculate
	 * the maximum size locally (because we don't have any APIs for it now)
	 * and check the current max_req_size. And then, this will update
	 * the max_req_size if needed as a workaround.
	 */
	if (swiotlb_max_segment()) {
		unsigned int max_size = (1 << IO_TLB_SHIFT) * IO_TLB_SEGSIZE;

		if (mmc->max_req_size > max_size)
			mmc->max_req_size = max_size;
	}
	mmc->max_seg_size = mmc->max_req_size;

	if (mmc_can_gpio_ro(mmc))
		_host->ops.get_ro = mmc_gpio_get_ro;

	if (mmc_can_gpio_cd(mmc))
		_host->ops.get_cd = mmc_gpio_get_cd;

	_host->native_hotplug = !(mmc_can_gpio_cd(mmc) ||
				  mmc->caps & MMC_CAP_NEEDS_POLL ||
				  !mmc_card_is_removable(mmc));

	/*
	 * On Gen2+, eMMC with NONREMOVABLE currently fails because native
	 * hotplug gets disabled. It seems RuntimePM related yet we need further
	 * research. Since we are planning a PM overhaul anyway, let's enforce
	 * for now the device being active by enabling native hotplug always.
	 */
	if (pdata->flags & TMIO_MMC_MIN_RCAR2)
		_host->native_hotplug = true;

	/*
	 * While using internal tmio hardware logic for card detection, we need
	 * to ensure it stays powered for it to work.
	 */
	if (_host->native_hotplug)
		pm_runtime_get_noresume(&pdev->dev);

	_host->sdio_irq_enabled = false;
	if (pdata->flags & TMIO_MMC_SDIO_IRQ)
		_host->sdio_irq_mask = TMIO_SDIO_MASK_ALL;

	tmio_mmc_clk_stop(_host);
	tmio_mmc_reset(_host);

	_host->sdcard_irq_mask = sd_ctrl_read16_and_16_as_32(_host, CTL_IRQ_MASK);
	tmio_mmc_disable_mmc_irqs(_host, TMIO_MASK_ALL);

	if (_host->native_hotplug)
		tmio_mmc_enable_mmc_irqs(_host,
				TMIO_STAT_CARD_REMOVE | TMIO_STAT_CARD_INSERT);

	spin_lock_init(&_host->lock);
	mutex_init(&_host->ios_lock);

	/* Init delayed work for request timeouts */
	INIT_DELAYED_WORK(&_host->delayed_reset_work, tmio_mmc_reset_work);
	INIT_WORK(&_host->done, tmio_mmc_done_work);

	/* See if we also get DMA */
	tmio_mmc_request_dma(_host, pdata);

	pm_runtime_set_active(&pdev->dev);
	pm_runtime_set_autosuspend_delay(&pdev->dev, 50);
	pm_runtime_use_autosuspend(&pdev->dev);
	pm_runtime_enable(&pdev->dev);

	ret = mmc_add_host(mmc);
	if (ret)
		goto remove_host;

	dev_pm_qos_expose_latency_limit(&pdev->dev, 100);

	return 0;

remove_host:
	tmio_mmc_host_remove(_host);
	return ret;
}