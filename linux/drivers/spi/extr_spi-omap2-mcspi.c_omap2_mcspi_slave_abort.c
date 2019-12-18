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
struct spi_master {int dummy; } ;
struct omap2_mcspi_dma {int /*<<< orphan*/  dma_tx_completion; int /*<<< orphan*/  dma_rx_completion; } ;
struct omap2_mcspi {int slave_aborted; int /*<<< orphan*/  txdone; struct omap2_mcspi_dma* dma_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct omap2_mcspi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int omap2_mcspi_slave_abort(struct spi_master *master)
{
	struct omap2_mcspi *mcspi = spi_master_get_devdata(master);
	struct omap2_mcspi_dma *mcspi_dma = mcspi->dma_channels;

	mcspi->slave_aborted = true;
	complete(&mcspi_dma->dma_rx_completion);
	complete(&mcspi_dma->dma_tx_completion);
	complete(&mcspi->txdone);

	return 0;
}