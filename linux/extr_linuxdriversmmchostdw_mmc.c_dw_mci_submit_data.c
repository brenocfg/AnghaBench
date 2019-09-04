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
typedef  int u32 ;
struct mmc_data {int flags; scalar_t__ blksz; int /*<<< orphan*/ * sg; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  error; } ;
struct dw_mci {int fifoth_val; scalar_t__ prev_blksz; scalar_t__ wm_aligned; int /*<<< orphan*/  irq_lock; scalar_t__ part_buf_count; scalar_t__ part_buf_start; int /*<<< orphan*/ * sg; int /*<<< orphan*/  sg_miter; struct mmc_data* data; int /*<<< orphan*/  dir_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  DW_MCI_RECV_STATUS ; 
 int /*<<< orphan*/  DW_MCI_SEND_STATUS ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  FIFOTH ; 
 int /*<<< orphan*/  INTMASK ; 
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  RINTSTS ; 
 int SDMMC_CTRL_DMA_ENABLE ; 
 int SDMMC_INT_RXDR ; 
 int SDMMC_INT_TXDR ; 
 int SG_MITER_ATOMIC ; 
 int SG_MITER_FROM_SG ; 
 int SG_MITER_TO_SG ; 
 int /*<<< orphan*/  WARN_ON (struct mmc_data*) ; 
 int /*<<< orphan*/  dw_mci_adjust_fifoth (struct dw_mci*,struct mmc_data*) ; 
 int /*<<< orphan*/  dw_mci_ctrl_thld (struct dw_mci*,struct mmc_data*) ; 
 scalar_t__ dw_mci_submit_data_dma (struct dw_mci*,struct mmc_data*) ; 
 int mci_readl (struct dw_mci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mci_writel (struct dw_mci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_miter_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void dw_mci_submit_data(struct dw_mci *host, struct mmc_data *data)
{
	unsigned long irqflags;
	int flags = SG_MITER_ATOMIC;
	u32 temp;

	data->error = -EINPROGRESS;

	WARN_ON(host->data);
	host->sg = NULL;
	host->data = data;

	if (data->flags & MMC_DATA_READ)
		host->dir_status = DW_MCI_RECV_STATUS;
	else
		host->dir_status = DW_MCI_SEND_STATUS;

	dw_mci_ctrl_thld(host, data);

	if (dw_mci_submit_data_dma(host, data)) {
		if (host->data->flags & MMC_DATA_READ)
			flags |= SG_MITER_TO_SG;
		else
			flags |= SG_MITER_FROM_SG;

		sg_miter_start(&host->sg_miter, data->sg, data->sg_len, flags);
		host->sg = data->sg;
		host->part_buf_start = 0;
		host->part_buf_count = 0;

		mci_writel(host, RINTSTS, SDMMC_INT_TXDR | SDMMC_INT_RXDR);

		spin_lock_irqsave(&host->irq_lock, irqflags);
		temp = mci_readl(host, INTMASK);
		temp |= SDMMC_INT_TXDR | SDMMC_INT_RXDR;
		mci_writel(host, INTMASK, temp);
		spin_unlock_irqrestore(&host->irq_lock, irqflags);

		temp = mci_readl(host, CTRL);
		temp &= ~SDMMC_CTRL_DMA_ENABLE;
		mci_writel(host, CTRL, temp);

		/*
		 * Use the initial fifoth_val for PIO mode. If wm_algined
		 * is set, we set watermark same as data size.
		 * If next issued data may be transfered by DMA mode,
		 * prev_blksz should be invalidated.
		 */
		if (host->wm_aligned)
			dw_mci_adjust_fifoth(host, data);
		else
			mci_writel(host, FIFOTH, host->fifoth_val);
		host->prev_blksz = 0;
	} else {
		/*
		 * Keep the current block size.
		 * It will be used to decide whether to update
		 * fifoth register next time.
		 */
		host->prev_blksz = data->blksz;
	}
}