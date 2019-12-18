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
struct spi_transfer {scalar_t__ len; scalar_t__ rx_buf; scalar_t__ tx_buf; } ;
struct spi_master {int dummy; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ MTK_SPI_MAX_FIFO_SIZE ; 

__attribute__((used)) static bool mtk_spi_can_dma(struct spi_master *master,
			    struct spi_device *spi,
			    struct spi_transfer *xfer)
{
	/* Buffers for DMA transactions must be 4-byte aligned */
	return (xfer->len > MTK_SPI_MAX_FIFO_SIZE &&
		(unsigned long)xfer->tx_buf % 4 == 0 &&
		(unsigned long)xfer->rx_buf % 4 == 0);
}