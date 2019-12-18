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
struct mmci_host {scalar_t__ base; TYPE_1__* ops; int /*<<< orphan*/  mmc; int /*<<< orphan*/  use_dma; struct mmc_data* data; } ;
struct mmc_data {int /*<<< orphan*/  flags; int /*<<< orphan*/  blocks; int /*<<< orphan*/  blksz; int /*<<< orphan*/  sg_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dma_start ) (struct mmci_host*,unsigned int*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int MCI_DATAENDMASK ; 
 scalar_t__ MMCIMASK0 ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int mmci_prep_data (struct mmci_host*,struct mmc_data*,int) ; 
 int /*<<< orphan*/  mmci_write_datactrlreg (struct mmci_host*,unsigned int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct mmci_host*,unsigned int*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int mmci_dma_start(struct mmci_host *host, unsigned int datactrl)
{
	struct mmc_data *data = host->data;
	int ret;

	if (!host->use_dma)
		return -EINVAL;

	ret = mmci_prep_data(host, data, false);
	if (ret)
		return ret;

	if (!host->ops || !host->ops->dma_start)
		return -EINVAL;

	/* Okay, go for it. */
	dev_vdbg(mmc_dev(host->mmc),
		 "Submit MMCI DMA job, sglen %d blksz %04x blks %04x flags %08x\n",
		 data->sg_len, data->blksz, data->blocks, data->flags);

	host->ops->dma_start(host, &datactrl);

	/* Trigger the DMA transfer */
	mmci_write_datactrlreg(host, datactrl);

	/*
	 * Let the MMCI say when the data is ended and it's time
	 * to fire next DMA request. When that happens, MMCI will
	 * call mmci_data_end()
	 */
	writel(readl(host->base + MMCIMASK0) | MCI_DATAENDMASK,
	       host->base + MMCIMASK0);
	return 0;
}