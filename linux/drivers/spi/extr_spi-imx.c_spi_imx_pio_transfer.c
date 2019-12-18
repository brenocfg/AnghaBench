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
struct spi_imx_data {int count; TYPE_1__* devtype_data; int /*<<< orphan*/  xfer_done; scalar_t__ remainder; scalar_t__ txfifo; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct spi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  master; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct spi_imx_data*) ;int /*<<< orphan*/  (* intctrl ) (struct spi_imx_data*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MXC_INT_TE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long spi_imx_calculate_timeout (struct spi_imx_data*,int) ; 
 int /*<<< orphan*/  spi_imx_push (struct spi_imx_data*) ; 
 struct spi_imx_data* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct spi_imx_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct spi_imx_data*) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int spi_imx_pio_transfer(struct spi_device *spi,
				struct spi_transfer *transfer)
{
	struct spi_imx_data *spi_imx = spi_master_get_devdata(spi->master);
	unsigned long transfer_timeout;
	unsigned long timeout;

	spi_imx->tx_buf = transfer->tx_buf;
	spi_imx->rx_buf = transfer->rx_buf;
	spi_imx->count = transfer->len;
	spi_imx->txfifo = 0;
	spi_imx->remainder = 0;

	reinit_completion(&spi_imx->xfer_done);

	spi_imx_push(spi_imx);

	spi_imx->devtype_data->intctrl(spi_imx, MXC_INT_TE);

	transfer_timeout = spi_imx_calculate_timeout(spi_imx, transfer->len);

	timeout = wait_for_completion_timeout(&spi_imx->xfer_done,
					      transfer_timeout);
	if (!timeout) {
		dev_err(&spi->dev, "I/O Error in PIO\n");
		spi_imx->devtype_data->reset(spi_imx);
		return -ETIMEDOUT;
	}

	return transfer->len;
}