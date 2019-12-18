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
struct spi_transfer {int /*<<< orphan*/  rx_sg; scalar_t__ rx_buf; int /*<<< orphan*/  tx_sg; } ;
struct rspi_data {TYPE_1__* ctlr; } ;
struct TYPE_2__ {int /*<<< orphan*/  can_dma; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  __rspi_can_dma (struct rspi_data*,struct spi_transfer*) ; 
 int rspi_dma_transfer (struct rspi_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rspi_dma_check_then_transfer(struct rspi_data *rspi,
					 struct spi_transfer *xfer)
{
	if (!rspi->ctlr->can_dma || !__rspi_can_dma(rspi, xfer))
		return -EAGAIN;

	/* rx_buf can be NULL on RSPI on SH in TX-only Mode */
	return rspi_dma_transfer(rspi, &xfer->tx_sg,
				xfer->rx_buf ? &xfer->rx_sg : NULL);
}