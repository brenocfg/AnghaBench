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
struct sifive_spi {int dummy; } ;

/* Variables and functions */
 int SIFIVE_SPI_DELAY0_CSSCK (int) ; 
 int SIFIVE_SPI_DELAY0_SCKCS (int) ; 
 int SIFIVE_SPI_DELAY1_INTERCS (int) ; 
 int SIFIVE_SPI_DELAY1_INTERXFR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIFIVE_SPI_REG_DELAY0 ; 
 int /*<<< orphan*/  SIFIVE_SPI_REG_DELAY1 ; 
 int /*<<< orphan*/  SIFIVE_SPI_REG_FCTRL ; 
 int /*<<< orphan*/  SIFIVE_SPI_REG_IE ; 
 int /*<<< orphan*/  SIFIVE_SPI_REG_RXMARK ; 
 int /*<<< orphan*/  SIFIVE_SPI_REG_TXMARK ; 
 int /*<<< orphan*/  sifive_spi_write (struct sifive_spi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sifive_spi_init(struct sifive_spi *spi)
{
	/* Watermark interrupts are disabled by default */
	sifive_spi_write(spi, SIFIVE_SPI_REG_IE, 0);

	/* Default watermark FIFO threshold values */
	sifive_spi_write(spi, SIFIVE_SPI_REG_TXMARK, 1);
	sifive_spi_write(spi, SIFIVE_SPI_REG_RXMARK, 0);

	/* Set CS/SCK Delays and Inactive Time to defaults */
	sifive_spi_write(spi, SIFIVE_SPI_REG_DELAY0,
			 SIFIVE_SPI_DELAY0_CSSCK(1) |
			 SIFIVE_SPI_DELAY0_SCKCS(1));
	sifive_spi_write(spi, SIFIVE_SPI_REG_DELAY1,
			 SIFIVE_SPI_DELAY1_INTERCS(1) |
			 SIFIVE_SPI_DELAY1_INTERXFR(0));

	/* Exit specialized memory-mapped SPI flash mode */
	sifive_spi_write(spi, SIFIVE_SPI_REG_FCTRL, 0);
}