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
struct spi_device {int mode; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int SPI_3WIRE ; 
 int SPI_CS_HIGH ; 
 int SPI_LSB_FIRST ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
spi_lp8841_rtc_setup(struct spi_device *spi)
{
	if ((spi->mode & SPI_CS_HIGH) == 0) {
		dev_err(&spi->dev, "unsupported active low chip select\n");
		return -EINVAL;
	}

	if ((spi->mode & SPI_LSB_FIRST) == 0) {
		dev_err(&spi->dev, "unsupported MSB first mode\n");
		return -EINVAL;
	}

	if ((spi->mode & SPI_3WIRE) == 0) {
		dev_err(&spi->dev, "unsupported wiring. 3 wires required\n");
		return -EINVAL;
	}

	return 0;
}