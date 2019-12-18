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
struct spi_transfer {scalar_t__ rx_buf; scalar_t__ tx_buf; } ;
struct spi_master {int /*<<< orphan*/  dma_rx; int /*<<< orphan*/  dma_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spi_qup_dma_terminate(struct spi_master *master,
				  struct spi_transfer *xfer)
{
	if (xfer->tx_buf)
		dmaengine_terminate_all(master->dma_tx);
	if (xfer->rx_buf)
		dmaengine_terminate_all(master->dma_rx);
}