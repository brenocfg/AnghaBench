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
struct spi_controller {int /*<<< orphan*/  max_dma_len; int /*<<< orphan*/  can_dma; int /*<<< orphan*/ * dma_rx; int /*<<< orphan*/ * dma_tx; } ;
struct fsl_lpspi_data {int /*<<< orphan*/  dma_tx_completion; int /*<<< orphan*/  dma_rx_completion; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSL_LPSPI_MAX_EDMA_BYTES ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 void* dma_request_slave_channel_reason (struct device*,char*) ; 
 int /*<<< orphan*/  fsl_lpspi_can_dma ; 
 int /*<<< orphan*/  fsl_lpspi_dma_exit (struct spi_controller*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsl_lpspi_dma_init(struct device *dev,
			      struct fsl_lpspi_data *fsl_lpspi,
			      struct spi_controller *controller)
{
	int ret;

	/* Prepare for TX DMA: */
	controller->dma_tx = dma_request_slave_channel_reason(dev, "tx");
	if (IS_ERR(controller->dma_tx)) {
		ret = PTR_ERR(controller->dma_tx);
		dev_dbg(dev, "can't get the TX DMA channel, error %d!\n", ret);
		controller->dma_tx = NULL;
		goto err;
	}

	/* Prepare for RX DMA: */
	controller->dma_rx = dma_request_slave_channel_reason(dev, "rx");
	if (IS_ERR(controller->dma_rx)) {
		ret = PTR_ERR(controller->dma_rx);
		dev_dbg(dev, "can't get the RX DMA channel, error %d\n", ret);
		controller->dma_rx = NULL;
		goto err;
	}

	init_completion(&fsl_lpspi->dma_rx_completion);
	init_completion(&fsl_lpspi->dma_tx_completion);
	controller->can_dma = fsl_lpspi_can_dma;
	controller->max_dma_len = FSL_LPSPI_MAX_EDMA_BYTES;

	return 0;
err:
	fsl_lpspi_dma_exit(controller);
	return ret;
}