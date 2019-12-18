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
struct spi_transfer {unsigned int len; int /*<<< orphan*/  rx_sg; int /*<<< orphan*/ * rx_buf; } ;
struct rspi_data {TYPE_1__* ctlr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; scalar_t__ can_dma; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ __rspi_can_dma (struct rspi_data*,struct spi_transfer*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned int qspi_set_receive_trigger (struct rspi_data*,unsigned int) ; 
 int rspi_dma_transfer (struct rspi_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rspi_read_data (struct rspi_data*) ; 
 int rspi_wait_for_rx_full (struct rspi_data*) ; 

__attribute__((used)) static int qspi_transfer_in(struct rspi_data *rspi, struct spi_transfer *xfer)
{
	u8 *rx = xfer->rx_buf;
	unsigned int n = xfer->len;
	unsigned int i, len;
	int ret;

	if (rspi->ctlr->can_dma && __rspi_can_dma(rspi, xfer)) {
		int ret = rspi_dma_transfer(rspi, NULL, &xfer->rx_sg);
		if (ret != -EAGAIN)
			return ret;
	}

	while (n > 0) {
		len = qspi_set_receive_trigger(rspi, n);
		ret = rspi_wait_for_rx_full(rspi);
		if (ret < 0) {
			dev_err(&rspi->ctlr->dev, "receive timeout\n");
			return ret;
		}
		for (i = 0; i < len; i++)
			*rx++ = rspi_read_data(rspi);

		n -= len;
	}

	return 0;
}