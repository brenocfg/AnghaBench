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
typedef  int /*<<< orphan*/  u8 ;
struct spi_transfer {unsigned int len; int /*<<< orphan*/  tx_sg; int /*<<< orphan*/ * tx_buf; } ;
struct rspi_data {TYPE_1__* ctlr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; scalar_t__ can_dma; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ __rspi_can_dma (struct rspi_data*,struct spi_transfer*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned int qspi_set_send_trigger (struct rspi_data*,unsigned int) ; 
 int rspi_dma_transfer (struct rspi_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rspi_wait_for_tx_empty (struct rspi_data*) ; 
 int /*<<< orphan*/  rspi_write_data (struct rspi_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qspi_transfer_out(struct rspi_data *rspi, struct spi_transfer *xfer)
{
	const u8 *tx = xfer->tx_buf;
	unsigned int n = xfer->len;
	unsigned int i, len;
	int ret;

	if (rspi->ctlr->can_dma && __rspi_can_dma(rspi, xfer)) {
		ret = rspi_dma_transfer(rspi, &xfer->tx_sg, NULL);
		if (ret != -EAGAIN)
			return ret;
	}

	while (n > 0) {
		len = qspi_set_send_trigger(rspi, n);
		ret = rspi_wait_for_tx_empty(rspi);
		if (ret < 0) {
			dev_err(&rspi->ctlr->dev, "transmit timeout\n");
			return ret;
		}
		for (i = 0; i < len; i++)
			rspi_write_data(rspi, *tx++);

		n -= len;
	}

	/* Wait for the last transmission */
	rspi_wait_for_tx_empty(rspi);

	return 0;
}