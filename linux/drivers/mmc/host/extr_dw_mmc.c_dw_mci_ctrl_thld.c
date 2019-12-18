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
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned int u32 ;
typedef  unsigned int u16 ;
struct mmc_data {unsigned int blksz; int flags; } ;
struct dw_mci {scalar_t__ verid; scalar_t__ timing; int data_shift; unsigned int fifo_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDTHRCTL ; 
 scalar_t__ DW_MMC_240A ; 
 scalar_t__ DW_MMC_280A ; 
 int MMC_DATA_WRITE ; 
 scalar_t__ MMC_TIMING_MMC_HS200 ; 
 scalar_t__ MMC_TIMING_MMC_HS400 ; 
 scalar_t__ MMC_TIMING_UHS_SDR104 ; 
 int /*<<< orphan*/  SDMMC_CARD_RD_THR_EN ; 
 int /*<<< orphan*/  SDMMC_CARD_WR_THR_EN ; 
 int /*<<< orphan*/  SDMMC_SET_THLD (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mci_writel (struct dw_mci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_mci_ctrl_thld(struct dw_mci *host, struct mmc_data *data)
{
	unsigned int blksz = data->blksz;
	u32 blksz_depth, fifo_depth;
	u16 thld_size;
	u8 enable;

	/*
	 * CDTHRCTL doesn't exist prior to 240A (in fact that register offset is
	 * in the FIFO region, so we really shouldn't access it).
	 */
	if (host->verid < DW_MMC_240A ||
		(host->verid < DW_MMC_280A && data->flags & MMC_DATA_WRITE))
		return;

	/*
	 * Card write Threshold is introduced since 2.80a
	 * It's used when HS400 mode is enabled.
	 */
	if (data->flags & MMC_DATA_WRITE &&
		host->timing != MMC_TIMING_MMC_HS400)
		goto disable;

	if (data->flags & MMC_DATA_WRITE)
		enable = SDMMC_CARD_WR_THR_EN;
	else
		enable = SDMMC_CARD_RD_THR_EN;

	if (host->timing != MMC_TIMING_MMC_HS200 &&
	    host->timing != MMC_TIMING_UHS_SDR104 &&
	    host->timing != MMC_TIMING_MMC_HS400)
		goto disable;

	blksz_depth = blksz / (1 << host->data_shift);
	fifo_depth = host->fifo_depth;

	if (blksz_depth > fifo_depth)
		goto disable;

	/*
	 * If (blksz_depth) >= (fifo_depth >> 1), should be 'thld_size <= blksz'
	 * If (blksz_depth) <  (fifo_depth >> 1), should be thld_size = blksz
	 * Currently just choose blksz.
	 */
	thld_size = blksz;
	mci_writel(host, CDTHRCTL, SDMMC_SET_THLD(thld_size, enable));
	return;

disable:
	mci_writel(host, CDTHRCTL, 0);
}