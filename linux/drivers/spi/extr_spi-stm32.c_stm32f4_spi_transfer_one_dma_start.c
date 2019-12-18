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
struct stm32_spi {scalar_t__ cur_comm; } ;

/* Variables and functions */
 scalar_t__ SPI_3WIRE_RX ; 
 scalar_t__ SPI_FULL_DUPLEX ; 
 scalar_t__ SPI_SIMPLEX_RX ; 
 int /*<<< orphan*/  STM32F4_SPI_CR2 ; 
 int /*<<< orphan*/  STM32F4_SPI_CR2_ERRIE ; 
 int /*<<< orphan*/  stm32_spi_enable (struct stm32_spi*) ; 
 int /*<<< orphan*/  stm32_spi_set_bits (struct stm32_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32f4_spi_transfer_one_dma_start(struct stm32_spi *spi)
{
	/* In DMA mode end of transfer is handled by DMA TX or RX callback. */
	if (spi->cur_comm == SPI_SIMPLEX_RX || spi->cur_comm == SPI_3WIRE_RX ||
	    spi->cur_comm == SPI_FULL_DUPLEX) {
		/*
		 * In transmit-only mode, the OVR flag is set in the SR register
		 * since the received data are never read. Therefore set OVR
		 * interrupt only when rx buffer is available.
		 */
		stm32_spi_set_bits(spi, STM32F4_SPI_CR2, STM32F4_SPI_CR2_ERRIE);
	}

	stm32_spi_enable(spi);
}