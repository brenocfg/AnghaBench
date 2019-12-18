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
struct spi_transfer {scalar_t__ len; } ;
struct spi_device {int dummy; } ;
struct spi_controller {int dummy; } ;

/* Variables and functions */
 scalar_t__ BCM2835_SPI_DMA_MIN_LENGTH ; 

__attribute__((used)) static bool bcm2835_spi_can_dma(struct spi_controller *ctlr,
				struct spi_device *spi,
				struct spi_transfer *tfr)
{
	/* we start DMA efforts only on bigger transfers */
	if (tfr->len < BCM2835_SPI_DMA_MIN_LENGTH)
		return false;

	/* return OK */
	return true;
}