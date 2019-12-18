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
typedef  int u8 ;
typedef  int u16 ;
struct spi_device {int chip_select; int mode; scalar_t__ cs_gpiod; int /*<<< orphan*/  master; struct davinci_spi_config* controller_data; } ;
struct davinci_spi_config {scalar_t__ wdelay; } ;
struct davinci_spi {scalar_t__ base; } ;

/* Variables and functions */
 int BITBANG_CS_ACTIVE ; 
 int CS_DEFAULT ; 
 scalar_t__ SPIDAT1 ; 
 int SPIDAT1_CSHOLD_MASK ; 
 int SPIDAT1_WDEL ; 
 int SPI_CS_WORD ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 
 struct davinci_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void davinci_spi_chipselect(struct spi_device *spi, int value)
{
	struct davinci_spi *dspi;
	struct davinci_spi_config *spicfg = spi->controller_data;
	u8 chip_sel = spi->chip_select;
	u16 spidat1 = CS_DEFAULT;

	dspi = spi_master_get_devdata(spi->master);

	/* program delay transfers if tx_delay is non zero */
	if (spicfg && spicfg->wdelay)
		spidat1 |= SPIDAT1_WDEL;

	/*
	 * Board specific chip select logic decides the polarity and cs
	 * line for the controller
	 */
	if (spi->cs_gpiod) {
		/*
		 * FIXME: is this code ever executed? This host does not
		 * set SPI_MASTER_GPIO_SS so this chipselect callback should
		 * not get called from the SPI core when we are using
		 * GPIOs for chip select.
		 */
		if (value == BITBANG_CS_ACTIVE)
			gpiod_set_value(spi->cs_gpiod, 1);
		else
			gpiod_set_value(spi->cs_gpiod, 0);
	} else {
		if (value == BITBANG_CS_ACTIVE) {
			if (!(spi->mode & SPI_CS_WORD))
				spidat1 |= SPIDAT1_CSHOLD_MASK;
			spidat1 &= ~(0x1 << chip_sel);
		}
	}

	iowrite16(spidat1, dspi->base + SPIDAT1 + 2);
}