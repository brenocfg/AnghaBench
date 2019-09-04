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
struct mmc_request {struct mmc_data* data; } ;
struct mmc_davinci_host {scalar_t__ version; int ns_in_one_cycle; int bytes_left; struct mmc_data* data; int /*<<< orphan*/  sg; int /*<<< orphan*/  sg_len; scalar_t__ use_dma; int /*<<< orphan*/ * buffer; scalar_t__ base; int /*<<< orphan*/  data_dir; int /*<<< orphan*/  mmc; } ;
struct mmc_data {int flags; int blocks; int blksz; int timeout_clks; int timeout_ns; int /*<<< orphan*/  sg; int /*<<< orphan*/  sg_len; } ;

/* Variables and functions */
 scalar_t__ DAVINCI_MMCBLEN ; 
 scalar_t__ DAVINCI_MMCFIFOCTL ; 
 scalar_t__ DAVINCI_MMCNBLK ; 
 scalar_t__ DAVINCI_MMCTOD ; 
 int /*<<< orphan*/  DAVINCI_MMC_DATADIR_NONE ; 
 int /*<<< orphan*/  DAVINCI_MMC_DATADIR_READ ; 
 int /*<<< orphan*/  DAVINCI_MMC_DATADIR_WRITE ; 
 int MMCFIFOCTL_FIFODIR_RD ; 
 int MMCFIFOCTL_FIFODIR_WR ; 
 int MMCFIFOCTL_FIFOLEV ; 
 int MMCFIFOCTL_FIFORST ; 
 scalar_t__ MMC_CTLR_VERSION_2 ; 
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mmc_davinci_sg_to_buf (struct mmc_davinci_host*) ; 
 scalar_t__ mmc_davinci_start_dma_transfer (struct mmc_davinci_host*,struct mmc_data*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int rw_threshold ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void
mmc_davinci_prepare_data(struct mmc_davinci_host *host, struct mmc_request *req)
{
	int fifo_lev = (rw_threshold == 32) ? MMCFIFOCTL_FIFOLEV : 0;
	int timeout;
	struct mmc_data *data = req->data;

	if (host->version == MMC_CTLR_VERSION_2)
		fifo_lev = (rw_threshold == 64) ? MMCFIFOCTL_FIFOLEV : 0;

	host->data = data;
	if (data == NULL) {
		host->data_dir = DAVINCI_MMC_DATADIR_NONE;
		writel(0, host->base + DAVINCI_MMCBLEN);
		writel(0, host->base + DAVINCI_MMCNBLK);
		return;
	}

	dev_dbg(mmc_dev(host->mmc), "%s, %d blocks of %d bytes\n",
		(data->flags & MMC_DATA_WRITE) ? "write" : "read",
		data->blocks, data->blksz);
	dev_dbg(mmc_dev(host->mmc), "  DTO %d cycles + %d ns\n",
		data->timeout_clks, data->timeout_ns);
	timeout = data->timeout_clks +
		(data->timeout_ns / host->ns_in_one_cycle);
	if (timeout > 0xffff)
		timeout = 0xffff;

	writel(timeout, host->base + DAVINCI_MMCTOD);
	writel(data->blocks, host->base + DAVINCI_MMCNBLK);
	writel(data->blksz, host->base + DAVINCI_MMCBLEN);

	/* Configure the FIFO */
	if (data->flags & MMC_DATA_WRITE) {
		host->data_dir = DAVINCI_MMC_DATADIR_WRITE;
		writel(fifo_lev | MMCFIFOCTL_FIFODIR_WR | MMCFIFOCTL_FIFORST,
			host->base + DAVINCI_MMCFIFOCTL);
		writel(fifo_lev | MMCFIFOCTL_FIFODIR_WR,
			host->base + DAVINCI_MMCFIFOCTL);
	} else {
		host->data_dir = DAVINCI_MMC_DATADIR_READ;
		writel(fifo_lev | MMCFIFOCTL_FIFODIR_RD | MMCFIFOCTL_FIFORST,
			host->base + DAVINCI_MMCFIFOCTL);
		writel(fifo_lev | MMCFIFOCTL_FIFODIR_RD,
			host->base + DAVINCI_MMCFIFOCTL);
	}

	host->buffer = NULL;
	host->bytes_left = data->blocks * data->blksz;

	/* For now we try to use DMA whenever we won't need partial FIFO
	 * reads or writes, either for the whole transfer (as tested here)
	 * or for any individual scatterlist segment (tested when we call
	 * start_dma_transfer).
	 *
	 * While we *could* change that, unusual block sizes are rarely
	 * used.  The occasional fallback to PIO should't hurt.
	 */
	if (host->use_dma && (host->bytes_left & (rw_threshold - 1)) == 0
			&& mmc_davinci_start_dma_transfer(host, data) == 0) {
		/* zero this to ensure we take no PIO paths */
		host->bytes_left = 0;
	} else {
		/* Revert to CPU Copy */
		host->sg_len = data->sg_len;
		host->sg = host->data->sg;
		mmc_davinci_sg_to_buf(host);
	}
}