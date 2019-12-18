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
struct spi_device {int mode; int /*<<< orphan*/  master; } ;
struct cdns_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS_SPI_CR ; 
 int CDNS_SPI_CR_CPHA ; 
 int CDNS_SPI_CR_CPOL ; 
 int /*<<< orphan*/  CDNS_SPI_ER ; 
 int CDNS_SPI_ER_DISABLE ; 
 int CDNS_SPI_ER_ENABLE ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int cdns_spi_read (struct cdns_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns_spi_write (struct cdns_spi*,int /*<<< orphan*/ ,int) ; 
 struct cdns_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cdns_spi_config_clock_mode(struct spi_device *spi)
{
	struct cdns_spi *xspi = spi_master_get_devdata(spi->master);
	u32 ctrl_reg, new_ctrl_reg;

	new_ctrl_reg = cdns_spi_read(xspi, CDNS_SPI_CR);
	ctrl_reg = new_ctrl_reg;

	/* Set the SPI clock phase and clock polarity */
	new_ctrl_reg &= ~(CDNS_SPI_CR_CPHA | CDNS_SPI_CR_CPOL);
	if (spi->mode & SPI_CPHA)
		new_ctrl_reg |= CDNS_SPI_CR_CPHA;
	if (spi->mode & SPI_CPOL)
		new_ctrl_reg |= CDNS_SPI_CR_CPOL;

	if (new_ctrl_reg != ctrl_reg) {
		/*
		 * Just writing the CR register does not seem to apply the clock
		 * setting changes. This is problematic when changing the clock
		 * polarity as it will cause the SPI slave to see spurious clock
		 * transitions. To workaround the issue toggle the ER register.
		 */
		cdns_spi_write(xspi, CDNS_SPI_ER, CDNS_SPI_ER_DISABLE);
		cdns_spi_write(xspi, CDNS_SPI_CR, new_ctrl_reg);
		cdns_spi_write(xspi, CDNS_SPI_ER, CDNS_SPI_ER_ENABLE);
	}
}