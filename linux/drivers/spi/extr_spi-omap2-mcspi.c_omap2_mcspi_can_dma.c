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
struct spi_master {int dummy; } ;
struct spi_device {size_t chip_select; int /*<<< orphan*/  master; } ;
struct omap2_mcspi_dma {int /*<<< orphan*/  dma_tx; int /*<<< orphan*/  dma_rx; } ;
struct omap2_mcspi {struct omap2_mcspi_dma* dma_channels; } ;

/* Variables and functions */
 scalar_t__ DMA_MIN_BYTES ; 
 scalar_t__ spi_controller_is_slave (struct spi_master*) ; 
 struct omap2_mcspi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool omap2_mcspi_can_dma(struct spi_master *master,
				struct spi_device *spi,
				struct spi_transfer *xfer)
{
	struct omap2_mcspi *mcspi = spi_master_get_devdata(spi->master);
	struct omap2_mcspi_dma *mcspi_dma =
		&mcspi->dma_channels[spi->chip_select];

	if (!mcspi_dma->dma_rx || !mcspi_dma->dma_tx)
		return false;

	if (spi_controller_is_slave(master))
		return true;

	return (xfer->len >= DMA_MIN_BYTES);
}