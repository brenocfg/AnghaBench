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
struct stm32_spi {scalar_t__ cur_comm; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 scalar_t__ SPI_3WIRE_TX ; 
 scalar_t__ SPI_SIMPLEX_TX ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32f4_spi_disable (struct stm32_spi*) ; 

__attribute__((used)) static void stm32f4_spi_dma_tx_cb(void *data)
{
	struct stm32_spi *spi = data;

	if (spi->cur_comm == SPI_SIMPLEX_TX || spi->cur_comm == SPI_3WIRE_TX) {
		spi_finalize_current_transfer(spi->master);
		stm32f4_spi_disable(spi);
	}
}