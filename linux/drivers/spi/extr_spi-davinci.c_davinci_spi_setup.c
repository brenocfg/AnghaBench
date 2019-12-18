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
struct TYPE_2__ {struct device_node* of_node; } ;
struct spi_device {int mode; int chip_select; scalar_t__ cs_gpiod; int /*<<< orphan*/  master; TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct davinci_spi {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SPIGCR1 ; 
 int SPIGCR1_LOOPBACK_MASK ; 
 scalar_t__ SPIPC0 ; 
 int SPIPC0_SPIENA_MASK ; 
 int SPI_LOOP ; 
 int SPI_NO_CS ; 
 int SPI_READY ; 
 int /*<<< orphan*/  clear_io_bits (scalar_t__,int) ; 
 int davinci_spi_of_setup (struct spi_device*) ; 
 int /*<<< orphan*/  set_io_bits (scalar_t__,int) ; 
 struct davinci_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int davinci_spi_setup(struct spi_device *spi)
{
	struct davinci_spi *dspi;
	struct device_node *np = spi->dev.of_node;
	bool internal_cs = true;

	dspi = spi_master_get_devdata(spi->master);

	if (!(spi->mode & SPI_NO_CS)) {
		if (np && spi->cs_gpiod)
			internal_cs = false;

		if (internal_cs)
			set_io_bits(dspi->base + SPIPC0, 1 << spi->chip_select);
	}

	if (spi->mode & SPI_READY)
		set_io_bits(dspi->base + SPIPC0, SPIPC0_SPIENA_MASK);

	if (spi->mode & SPI_LOOP)
		set_io_bits(dspi->base + SPIGCR1, SPIGCR1_LOOPBACK_MASK);
	else
		clear_io_bits(dspi->base + SPIGCR1, SPIGCR1_LOOPBACK_MASK);

	return davinci_spi_of_setup(spi);
}