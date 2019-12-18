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
typedef  int u32 ;
struct spi_device {int chip_select; int /*<<< orphan*/  master; } ;
struct cdns_spi {int /*<<< orphan*/  is_decoded_cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS_SPI_CR ; 
 int CDNS_SPI_CR_SSCTRL ; 
 int CDNS_SPI_SS0 ; 
 int CDNS_SPI_SS_SHIFT ; 
 int cdns_spi_read (struct cdns_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns_spi_write (struct cdns_spi*,int /*<<< orphan*/ ,int) ; 
 struct cdns_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cdns_spi_chipselect(struct spi_device *spi, bool enable)
{
	struct cdns_spi *xspi = spi_master_get_devdata(spi->master);
	u32 ctrl_reg;

	ctrl_reg = cdns_spi_read(xspi, CDNS_SPI_CR);

	if (!enable) {
		/* Deselect the slave */
		ctrl_reg |= CDNS_SPI_CR_SSCTRL;
	} else {
		/* Select the slave */
		ctrl_reg &= ~CDNS_SPI_CR_SSCTRL;
		if (!(xspi->is_decoded_cs))
			ctrl_reg |= ((~(CDNS_SPI_SS0 << spi->chip_select)) <<
				     CDNS_SPI_SS_SHIFT) &
				     CDNS_SPI_CR_SSCTRL;
		else
			ctrl_reg |= (spi->chip_select << CDNS_SPI_SS_SHIFT) &
				     CDNS_SPI_CR_SSCTRL;
	}

	cdns_spi_write(xspi, CDNS_SPI_CR, ctrl_reg);
}