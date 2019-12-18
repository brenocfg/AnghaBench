#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tmio_mmc_host {int dma_on; TYPE_2__* mmc; struct mmc_data* data; struct tmio_mmc_data* pdata; } ;
struct tmio_mmc_data {int flags; } ;
struct mmc_data {int blksz; int blocks; } ;
struct TYPE_3__ {scalar_t__ bus_width; } ;
struct TYPE_4__ {scalar_t__ max_blk_count; TYPE_1__ ios; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_SD_XFER_LEN ; 
 int /*<<< orphan*/  CTL_XFER_BLK_COUNT ; 
 int EINVAL ; 
 scalar_t__ MMC_BUS_WIDTH_4 ; 
 scalar_t__ MMC_BUS_WIDTH_8 ; 
 scalar_t__ SZ_64K ; 
 int TMIO_MMC_BLKSZ_2BYTES ; 
 int /*<<< orphan*/  mmc_hostname (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sd_ctrl_write16 (struct tmio_mmc_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sd_ctrl_write32 (struct tmio_mmc_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tmio_mmc_init_sg (struct tmio_mmc_host*,struct mmc_data*) ; 
 int /*<<< orphan*/  tmio_mmc_start_dma (struct tmio_mmc_host*,struct mmc_data*) ; 

__attribute__((used)) static int tmio_mmc_start_data(struct tmio_mmc_host *host,
			       struct mmc_data *data)
{
	struct tmio_mmc_data *pdata = host->pdata;

	pr_debug("setup data transfer: blocksize %08x  nr_blocks %d\n",
		 data->blksz, data->blocks);

	/* Some hardware cannot perform 2 byte requests in 4/8 bit mode */
	if (host->mmc->ios.bus_width == MMC_BUS_WIDTH_4 ||
	    host->mmc->ios.bus_width == MMC_BUS_WIDTH_8) {
		int blksz_2bytes = pdata->flags & TMIO_MMC_BLKSZ_2BYTES;

		if (data->blksz < 2 || (data->blksz < 4 && !blksz_2bytes)) {
			pr_err("%s: %d byte block unsupported in 4/8 bit mode\n",
			       mmc_hostname(host->mmc), data->blksz);
			return -EINVAL;
		}
	}

	tmio_mmc_init_sg(host, data);
	host->data = data;
	host->dma_on = false;

	/* Set transfer length / blocksize */
	sd_ctrl_write16(host, CTL_SD_XFER_LEN, data->blksz);
	if (host->mmc->max_blk_count >= SZ_64K)
		sd_ctrl_write32(host, CTL_XFER_BLK_COUNT, data->blocks);
	else
		sd_ctrl_write16(host, CTL_XFER_BLK_COUNT, data->blocks);

	tmio_mmc_start_dma(host, data);

	return 0;
}