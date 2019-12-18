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
struct fsl_dspi {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SPI_SR ; 
 int SPI_SR_EOQF ; 
 int SPI_SR_TCFQF ; 
 int dspi_rxtx (struct fsl_dspi*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dspi_poll(struct fsl_dspi *dspi)
{
	int tries = 1000;
	u32 spi_sr;

	do {
		regmap_read(dspi->regmap, SPI_SR, &spi_sr);
		regmap_write(dspi->regmap, SPI_SR, spi_sr);

		if (spi_sr & (SPI_SR_EOQF | SPI_SR_TCFQF))
			break;
	} while (--tries);

	if (!tries)
		return -ETIMEDOUT;

	return dspi_rxtx(dspi);
}