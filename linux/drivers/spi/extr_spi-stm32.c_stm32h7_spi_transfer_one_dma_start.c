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
struct stm32_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STM32H7_SPI_CR1 ; 
 int STM32H7_SPI_CR1_CSTART ; 
 int /*<<< orphan*/  STM32H7_SPI_IER ; 
 int STM32H7_SPI_IER_EOTIE ; 
 int STM32H7_SPI_IER_MODFIE ; 
 int STM32H7_SPI_IER_OVRIE ; 
 int STM32H7_SPI_IER_TXTFIE ; 
 int /*<<< orphan*/  stm32_spi_enable (struct stm32_spi*) ; 
 int /*<<< orphan*/  stm32_spi_set_bits (struct stm32_spi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stm32h7_spi_transfer_one_dma_start(struct stm32_spi *spi)
{
	/* Enable the interrupts relative to the end of transfer */
	stm32_spi_set_bits(spi, STM32H7_SPI_IER, STM32H7_SPI_IER_EOTIE |
						 STM32H7_SPI_IER_TXTFIE |
						 STM32H7_SPI_IER_OVRIE |
						 STM32H7_SPI_IER_MODFIE);

	stm32_spi_enable(spi);

	stm32_spi_set_bits(spi, STM32H7_SPI_CR1, STM32H7_SPI_CR1_CSTART);
}