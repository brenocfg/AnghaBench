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
struct wbsd_host {int dma; int /*<<< orphan*/  ignore_timer; int /*<<< orphan*/  lock; struct mmc_host* mmc; } ;
struct mmc_host {int f_min; int f_max; int ocr_avail; int max_segs; int max_req_size; int max_seg_size; int max_blk_size; int max_blk_count; int /*<<< orphan*/  caps; int /*<<< orphan*/ * ops; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MMC_CAP_4_BIT_DATA ; 
 int MMC_VDD_32_33 ; 
 int MMC_VDD_33_34 ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct mmc_host*) ; 
 struct mmc_host* mmc_alloc_host (int,struct device*) ; 
 struct wbsd_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wbsd_ops ; 
 int /*<<< orphan*/  wbsd_reset_ignore ; 

__attribute__((used)) static int wbsd_alloc_mmc(struct device *dev)
{
	struct mmc_host *mmc;
	struct wbsd_host *host;

	/*
	 * Allocate MMC structure.
	 */
	mmc = mmc_alloc_host(sizeof(struct wbsd_host), dev);
	if (!mmc)
		return -ENOMEM;

	host = mmc_priv(mmc);
	host->mmc = mmc;

	host->dma = -1;

	/*
	 * Set host parameters.
	 */
	mmc->ops = &wbsd_ops;
	mmc->f_min = 375000;
	mmc->f_max = 24000000;
	mmc->ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34;
	mmc->caps = MMC_CAP_4_BIT_DATA;

	spin_lock_init(&host->lock);

	/*
	 * Set up timers
	 */
	timer_setup(&host->ignore_timer, wbsd_reset_ignore, 0);

	/*
	 * Maximum number of segments. Worst case is one sector per segment
	 * so this will be 64kB/512.
	 */
	mmc->max_segs = 128;

	/*
	 * Maximum request size. Also limited by 64KiB buffer.
	 */
	mmc->max_req_size = 65536;

	/*
	 * Maximum segment size. Could be one segment with the maximum number
	 * of bytes.
	 */
	mmc->max_seg_size = mmc->max_req_size;

	/*
	 * Maximum block size. We have 12 bits (= 4095) but have to subtract
	 * space for CRC. So the maximum is 4095 - 4*2 = 4087.
	 */
	mmc->max_blk_size = 4087;

	/*
	 * Maximum block count. There is no real limit so the maximum
	 * request size will be the only restriction.
	 */
	mmc->max_blk_count = mmc->max_req_size;

	dev_set_drvdata(dev, mmc);

	return 0;
}