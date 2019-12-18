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
struct spi_transfer {int /*<<< orphan*/  len; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct spi_controller {int dummy; } ;
struct fsl_lpspi_data {int slave_aborted; int /*<<< orphan*/  xfer_done; int /*<<< orphan*/  remain; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsl_lpspi_reset (struct fsl_lpspi_data*) ; 
 int fsl_lpspi_wait_for_completion (struct spi_controller*) ; 
 int /*<<< orphan*/  fsl_lpspi_write_tx_fifo (struct fsl_lpspi_data*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct fsl_lpspi_data* spi_controller_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static int fsl_lpspi_pio_transfer(struct spi_controller *controller,
				  struct spi_transfer *t)
{
	struct fsl_lpspi_data *fsl_lpspi =
				spi_controller_get_devdata(controller);
	int ret;

	fsl_lpspi->tx_buf = t->tx_buf;
	fsl_lpspi->rx_buf = t->rx_buf;
	fsl_lpspi->remain = t->len;

	reinit_completion(&fsl_lpspi->xfer_done);
	fsl_lpspi->slave_aborted = false;

	fsl_lpspi_write_tx_fifo(fsl_lpspi);

	ret = fsl_lpspi_wait_for_completion(controller);
	if (ret)
		return ret;

	fsl_lpspi_reset(fsl_lpspi);

	return 0;
}