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
typedef  int u32 ;
struct fsl_dspi {int bits_per_word; TYPE_2__* cur_chip; TYPE_1__* devtype_data; int /*<<< orphan*/  tx_cmd; } ;
struct TYPE_4__ {int ctar_val; } ;
struct TYPE_3__ {scalar_t__ xspi_mode; } ;

/* Variables and functions */
 int SPI_CTAR_LSBFE ; 
 int /*<<< orphan*/  SPI_PUSHR_CMD_CTCNT ; 
 int /*<<< orphan*/  cmd_fifo_write (struct fsl_dspi*) ; 
 int dspi_pop_tx (struct fsl_dspi*) ; 
 int /*<<< orphan*/  fifo_write (struct fsl_dspi*) ; 
 int /*<<< orphan*/  tx_fifo_write (struct fsl_dspi*,int) ; 

__attribute__((used)) static void dspi_tcfq_write(struct fsl_dspi *dspi)
{
	/* Clear transfer count */
	dspi->tx_cmd |= SPI_PUSHR_CMD_CTCNT;

	if (dspi->devtype_data->xspi_mode && dspi->bits_per_word > 16) {
		/* Write two TX FIFO entries first, and then the corresponding
		 * CMD FIFO entry.
		 */
		u32 data = dspi_pop_tx(dspi);

		if (dspi->cur_chip->ctar_val & SPI_CTAR_LSBFE) {
			/* LSB */
			tx_fifo_write(dspi, data & 0xFFFF);
			tx_fifo_write(dspi, data >> 16);
		} else {
			/* MSB */
			tx_fifo_write(dspi, data >> 16);
			tx_fifo_write(dspi, data & 0xFFFF);
		}
		cmd_fifo_write(dspi);
	} else {
		/* Write one entry to both TX FIFO and CMD FIFO
		 * simultaneously.
		 */
		fifo_write(dspi);
	}
}