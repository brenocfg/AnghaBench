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
struct spi_transfer {scalar_t__ tx_nbits; scalar_t__ rx_nbits; } ;
struct spi_device {int mode; } ;
struct spi_controller {int dummy; } ;
struct rspi_data {int dummy; } ;

/* Variables and functions */
 int SPI_LOOP ; 
 scalar_t__ SPI_NBITS_SINGLE ; 
 int qspi_transfer_in (struct rspi_data*,struct spi_transfer*) ; 
 int qspi_transfer_out (struct rspi_data*,struct spi_transfer*) ; 
 int qspi_transfer_out_in (struct rspi_data*,struct spi_transfer*) ; 
 struct rspi_data* spi_controller_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static int qspi_transfer_one(struct spi_controller *ctlr,
			     struct spi_device *spi, struct spi_transfer *xfer)
{
	struct rspi_data *rspi = spi_controller_get_devdata(ctlr);

	if (spi->mode & SPI_LOOP) {
		return qspi_transfer_out_in(rspi, xfer);
	} else if (xfer->tx_nbits > SPI_NBITS_SINGLE) {
		/* Quad or Dual SPI Write */
		return qspi_transfer_out(rspi, xfer);
	} else if (xfer->rx_nbits > SPI_NBITS_SINGLE) {
		/* Quad or Dual SPI Read */
		return qspi_transfer_in(rspi, xfer);
	} else {
		/* Single SPI Transfer */
		return qspi_transfer_out_in(rspi, xfer);
	}
}