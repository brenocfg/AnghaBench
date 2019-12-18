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
struct stm32_spi {int cur_bpw; } ;

/* Variables and functions */
 int /*<<< orphan*/  STM32F4_SPI_CR1 ; 
 int /*<<< orphan*/  STM32F4_SPI_CR1_DFF ; 
 int /*<<< orphan*/  stm32_spi_clr_bits (struct stm32_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_spi_set_bits (struct stm32_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32f4_spi_set_bpw(struct stm32_spi *spi)
{
	if (spi->cur_bpw == 16)
		stm32_spi_set_bits(spi, STM32F4_SPI_CR1, STM32F4_SPI_CR1_DFF);
	else
		stm32_spi_clr_bits(spi, STM32F4_SPI_CR1, STM32F4_SPI_CR1_DFF);
}