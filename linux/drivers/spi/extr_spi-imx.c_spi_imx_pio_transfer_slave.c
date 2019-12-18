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
struct spi_transfer {int len; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct spi_imx_data {int count; int slave_aborted; TYPE_1__* devtype_data; int /*<<< orphan*/  xfer_done; scalar_t__ remainder; scalar_t__ txfifo; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct spi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  master; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (struct spi_imx_data*) ;int /*<<< orphan*/  (* intctrl ) (struct spi_imx_data*,int) ;} ;

/* Variables and functions */
 int EINTR ; 
 int EMSGSIZE ; 
 int MX53_MAX_TRANSFER_BYTES ; 
 int MXC_INT_RDR ; 
 int MXC_INT_TE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ is_imx53_ecspi (struct spi_imx_data*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_imx_push (struct spi_imx_data*) ; 
 struct spi_imx_data* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct spi_imx_data*,int) ; 
 int /*<<< orphan*/  stub2 (struct spi_imx_data*) ; 
 scalar_t__ wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spi_imx_pio_transfer_slave(struct spi_device *spi,
				      struct spi_transfer *transfer)
{
	struct spi_imx_data *spi_imx = spi_master_get_devdata(spi->master);
	int ret = transfer->len;

	if (is_imx53_ecspi(spi_imx) &&
	    transfer->len > MX53_MAX_TRANSFER_BYTES) {
		dev_err(&spi->dev, "Transaction too big, max size is %d bytes\n",
			MX53_MAX_TRANSFER_BYTES);
		return -EMSGSIZE;
	}

	spi_imx->tx_buf = transfer->tx_buf;
	spi_imx->rx_buf = transfer->rx_buf;
	spi_imx->count = transfer->len;
	spi_imx->txfifo = 0;
	spi_imx->remainder = 0;

	reinit_completion(&spi_imx->xfer_done);
	spi_imx->slave_aborted = false;

	spi_imx_push(spi_imx);

	spi_imx->devtype_data->intctrl(spi_imx, MXC_INT_TE | MXC_INT_RDR);

	if (wait_for_completion_interruptible(&spi_imx->xfer_done) ||
	    spi_imx->slave_aborted) {
		dev_dbg(&spi->dev, "interrupted\n");
		ret = -EINTR;
	}

	/* ecspi has a HW issue when works in Slave mode,
	 * after 64 words writtern to TXFIFO, even TXFIFO becomes empty,
	 * ECSPI_TXDATA keeps shift out the last word data,
	 * so we have to disable ECSPI when in slave mode after the
	 * transfer completes
	 */
	if (spi_imx->devtype_data->disable)
		spi_imx->devtype_data->disable(spi_imx);

	return ret;
}