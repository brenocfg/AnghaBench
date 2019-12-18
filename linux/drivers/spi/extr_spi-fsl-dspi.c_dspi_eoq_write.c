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
typedef  int /*<<< orphan*/  u16 ;
struct fsl_dspi {scalar_t__ len; scalar_t__ bytes_per_word; int /*<<< orphan*/  tx_cmd; } ;

/* Variables and functions */
 int DSPI_FIFO_SIZE ; 
 int /*<<< orphan*/  SPI_PUSHR_CMD_CTCNT ; 
 int /*<<< orphan*/  SPI_PUSHR_CMD_EOQ ; 
 int /*<<< orphan*/  fifo_write (struct fsl_dspi*) ; 

__attribute__((used)) static void dspi_eoq_write(struct fsl_dspi *dspi)
{
	int fifo_size = DSPI_FIFO_SIZE;
	u16 xfer_cmd = dspi->tx_cmd;

	/* Fill TX FIFO with as many transfers as possible */
	while (dspi->len && fifo_size--) {
		dspi->tx_cmd = xfer_cmd;
		/* Request EOQF for last transfer in FIFO */
		if (dspi->len == dspi->bytes_per_word || fifo_size == 0)
			dspi->tx_cmd |= SPI_PUSHR_CMD_EOQ;
		/* Clear transfer count for first transfer in FIFO */
		if (fifo_size == (DSPI_FIFO_SIZE - 1))
			dspi->tx_cmd |= SPI_PUSHR_CMD_CTCNT;
		/* Write combined TX FIFO and CMD FIFO entry */
		fifo_write(dspi);
	}
}