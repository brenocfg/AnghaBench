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
struct mmc_host {int caps; int max_blk_count; int max_req_size; int max_blk_size; int /*<<< orphan*/  max_seg_size; int /*<<< orphan*/  max_segs; int /*<<< orphan*/ * ops; int /*<<< orphan*/  caps2; int /*<<< orphan*/  ocr_avail; int /*<<< orphan*/  f_max; int /*<<< orphan*/  f_min; } ;
struct alcor_sdmmc_host {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU6601_MAX_CLOCK ; 
 int /*<<< orphan*/  AU6601_MAX_DMA_BLOCK_SIZE ; 
 int /*<<< orphan*/  AU6601_MAX_DMA_SEGMENTS ; 
 int /*<<< orphan*/  AU6601_MIN_CLOCK ; 
 int /*<<< orphan*/  MMC_CAP2_NO_SDIO ; 
 int MMC_CAP_4_BIT_DATA ; 
 int MMC_CAP_SD_HIGHSPEED ; 
 int MMC_CAP_UHS_DDR50 ; 
 int MMC_CAP_UHS_SDR104 ; 
 int MMC_CAP_UHS_SDR12 ; 
 int MMC_CAP_UHS_SDR25 ; 
 int MMC_CAP_UHS_SDR50 ; 
 int /*<<< orphan*/  MMC_VDD_33_34 ; 
 int /*<<< orphan*/  alcor_sdc_ops ; 
 int /*<<< orphan*/  dma_set_max_seg_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mmc_host* mmc_from_priv (struct alcor_sdmmc_host*) ; 

__attribute__((used)) static void alcor_init_mmc(struct alcor_sdmmc_host *host)
{
	struct mmc_host *mmc = mmc_from_priv(host);

	mmc->f_min = AU6601_MIN_CLOCK;
	mmc->f_max = AU6601_MAX_CLOCK;
	mmc->ocr_avail = MMC_VDD_33_34;
	mmc->caps = MMC_CAP_4_BIT_DATA | MMC_CAP_SD_HIGHSPEED
		| MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 | MMC_CAP_UHS_SDR50
		| MMC_CAP_UHS_SDR104 | MMC_CAP_UHS_DDR50;
	mmc->caps2 = MMC_CAP2_NO_SDIO;
	mmc->ops = &alcor_sdc_ops;

	/* The hardware does DMA data transfer of 4096 bytes to/from a single
	 * buffer address. Scatterlists are not supported at the hardware
	 * level, however we can work with them at the driver level,
	 * provided that each segment is exactly 4096 bytes in size.
	 * Upon DMA completion of a single segment (signalled via IRQ), we
	 * immediately proceed to transfer the next segment from the
	 * scatterlist.
	 *
	 * The overall request is limited to 240 sectors, matching the
	 * original vendor driver.
	 */
	mmc->max_segs = AU6601_MAX_DMA_SEGMENTS;
	mmc->max_seg_size = AU6601_MAX_DMA_BLOCK_SIZE;
	mmc->max_blk_count = 240;
	mmc->max_req_size = mmc->max_blk_count * mmc->max_blk_size;
	dma_set_max_seg_size(host->dev, mmc->max_seg_size);
}