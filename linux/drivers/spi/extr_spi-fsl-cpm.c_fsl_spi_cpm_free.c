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
struct mpc8xxx_spi {int flags; int /*<<< orphan*/  pram; int /*<<< orphan*/  tx_bd; int /*<<< orphan*/  dma_dummy_tx; int /*<<< orphan*/  dma_dummy_rx; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int SPI_CPM_MODE ; 
 int /*<<< orphan*/  SPI_MRBLR ; 
 int /*<<< orphan*/  cpm_muram_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpm_muram_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_spi_free_dummy_rx () ; 

void fsl_spi_cpm_free(struct mpc8xxx_spi *mspi)
{
	struct device *dev = mspi->dev;

	if (!(mspi->flags & SPI_CPM_MODE))
		return;

	dma_unmap_single(dev, mspi->dma_dummy_rx, SPI_MRBLR, DMA_FROM_DEVICE);
	dma_unmap_single(dev, mspi->dma_dummy_tx, PAGE_SIZE, DMA_TO_DEVICE);
	cpm_muram_free(cpm_muram_offset(mspi->tx_bd));
	cpm_muram_free(cpm_muram_offset(mspi->pram));
	fsl_spi_free_dummy_rx();
}