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
struct spi_controller {int dummy; } ;
struct fsl_lpspi_data {int slave_aborted; int /*<<< orphan*/  dma_rx_completion; int /*<<< orphan*/  dma_tx_completion; int /*<<< orphan*/  xfer_done; int /*<<< orphan*/  usedma; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct fsl_lpspi_data* spi_controller_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static int fsl_lpspi_slave_abort(struct spi_controller *controller)
{
	struct fsl_lpspi_data *fsl_lpspi =
				spi_controller_get_devdata(controller);

	fsl_lpspi->slave_aborted = true;
	if (!fsl_lpspi->usedma)
		complete(&fsl_lpspi->xfer_done);
	else {
		complete(&fsl_lpspi->dma_tx_completion);
		complete(&fsl_lpspi->dma_rx_completion);
	}

	return 0;
}