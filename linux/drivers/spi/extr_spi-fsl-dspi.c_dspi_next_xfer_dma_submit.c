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
struct fsl_dspi_dma {int curr_xfer_len; int /*<<< orphan*/  chan_rx; int /*<<< orphan*/  chan_tx; int /*<<< orphan*/  cmd_rx_complete; int /*<<< orphan*/  cmd_tx_complete; TYPE_2__* rx_desc; int /*<<< orphan*/  rx_dma_phys; TYPE_2__* tx_desc; int /*<<< orphan*/  tx_dma_phys; int /*<<< orphan*/ * tx_dma_buf; } ;
struct fsl_dspi {struct fsl_dspi_dma* dma; int /*<<< orphan*/  ctlr; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct fsl_dspi* callback_param; int /*<<< orphan*/  callback; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_COMPLETION_TIMEOUT ; 
 int DMA_CTRL_ACK ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int DMA_PREP_INTERRUPT ; 
 int DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int EINVAL ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ dma_submit_error (int /*<<< orphan*/ ) ; 
 void* dmaengine_prep_slave_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmaengine_submit (TYPE_2__*) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dspi_pop_tx_pushr (struct fsl_dspi*) ; 
 int /*<<< orphan*/  dspi_rx_dma_callback ; 
 int /*<<< orphan*/  dspi_tx_dma_callback ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ spi_controller_is_slave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dspi_next_xfer_dma_submit(struct fsl_dspi *dspi)
{
	struct device *dev = &dspi->pdev->dev;
	struct fsl_dspi_dma *dma = dspi->dma;
	int time_left;
	int i;

	for (i = 0; i < dma->curr_xfer_len; i++)
		dspi->dma->tx_dma_buf[i] = dspi_pop_tx_pushr(dspi);

	dma->tx_desc = dmaengine_prep_slave_single(dma->chan_tx,
					dma->tx_dma_phys,
					dma->curr_xfer_len *
					DMA_SLAVE_BUSWIDTH_4_BYTES,
					DMA_MEM_TO_DEV,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	if (!dma->tx_desc) {
		dev_err(dev, "Not able to get desc for DMA xfer\n");
		return -EIO;
	}

	dma->tx_desc->callback = dspi_tx_dma_callback;
	dma->tx_desc->callback_param = dspi;
	if (dma_submit_error(dmaengine_submit(dma->tx_desc))) {
		dev_err(dev, "DMA submit failed\n");
		return -EINVAL;
	}

	dma->rx_desc = dmaengine_prep_slave_single(dma->chan_rx,
					dma->rx_dma_phys,
					dma->curr_xfer_len *
					DMA_SLAVE_BUSWIDTH_4_BYTES,
					DMA_DEV_TO_MEM,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	if (!dma->rx_desc) {
		dev_err(dev, "Not able to get desc for DMA xfer\n");
		return -EIO;
	}

	dma->rx_desc->callback = dspi_rx_dma_callback;
	dma->rx_desc->callback_param = dspi;
	if (dma_submit_error(dmaengine_submit(dma->rx_desc))) {
		dev_err(dev, "DMA submit failed\n");
		return -EINVAL;
	}

	reinit_completion(&dspi->dma->cmd_rx_complete);
	reinit_completion(&dspi->dma->cmd_tx_complete);

	dma_async_issue_pending(dma->chan_rx);
	dma_async_issue_pending(dma->chan_tx);

	if (spi_controller_is_slave(dspi->ctlr)) {
		wait_for_completion_interruptible(&dspi->dma->cmd_rx_complete);
		return 0;
	}

	time_left = wait_for_completion_timeout(&dspi->dma->cmd_tx_complete,
						DMA_COMPLETION_TIMEOUT);
	if (time_left == 0) {
		dev_err(dev, "DMA tx timeout\n");
		dmaengine_terminate_all(dma->chan_tx);
		dmaengine_terminate_all(dma->chan_rx);
		return -ETIMEDOUT;
	}

	time_left = wait_for_completion_timeout(&dspi->dma->cmd_rx_complete,
						DMA_COMPLETION_TIMEOUT);
	if (time_left == 0) {
		dev_err(dev, "DMA rx timeout\n");
		dmaengine_terminate_all(dma->chan_tx);
		dmaengine_terminate_all(dma->chan_rx);
		return -ETIMEDOUT;
	}

	return 0;
}