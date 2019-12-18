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
typedef  int u32 ;
struct stm32_spi {scalar_t__ base; } ;

/* Variables and functions */
 unsigned int SPI_3WIRE_RX ; 
 unsigned int SPI_3WIRE_TX ; 
 unsigned int SPI_SIMPLEX_RX ; 
 unsigned int SPI_SIMPLEX_TX ; 
 scalar_t__ STM32H7_SPI_CFG2 ; 
 int STM32H7_SPI_CFG2_COMM ; 
 int STM32H7_SPI_CFG2_COMM_SHIFT ; 
 int /*<<< orphan*/  STM32H7_SPI_CR1 ; 
 int /*<<< orphan*/  STM32H7_SPI_CR1_HDDIR ; 
 int STM32H7_SPI_FULL_DUPLEX ; 
 int STM32H7_SPI_HALF_DUPLEX ; 
 int STM32H7_SPI_SIMPLEX_RX ; 
 int STM32H7_SPI_SIMPLEX_TX ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  stm32_spi_clr_bits (struct stm32_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_spi_set_bits (struct stm32_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int stm32h7_spi_set_mode(struct stm32_spi *spi, unsigned int comm_type)
{
	u32 mode;
	u32 cfg2_clrb = 0, cfg2_setb = 0;

	if (comm_type == SPI_3WIRE_RX) {
		mode = STM32H7_SPI_HALF_DUPLEX;
		stm32_spi_clr_bits(spi, STM32H7_SPI_CR1, STM32H7_SPI_CR1_HDDIR);
	} else if (comm_type == SPI_3WIRE_TX) {
		mode = STM32H7_SPI_HALF_DUPLEX;
		stm32_spi_set_bits(spi, STM32H7_SPI_CR1, STM32H7_SPI_CR1_HDDIR);
	} else if (comm_type == SPI_SIMPLEX_RX) {
		mode = STM32H7_SPI_SIMPLEX_RX;
	} else if (comm_type == SPI_SIMPLEX_TX) {
		mode = STM32H7_SPI_SIMPLEX_TX;
	} else {
		mode = STM32H7_SPI_FULL_DUPLEX;
	}

	cfg2_clrb |= STM32H7_SPI_CFG2_COMM;
	cfg2_setb |= (mode << STM32H7_SPI_CFG2_COMM_SHIFT) &
		     STM32H7_SPI_CFG2_COMM;

	writel_relaxed(
		(readl_relaxed(spi->base + STM32H7_SPI_CFG2) &
		 ~cfg2_clrb) | cfg2_setb,
		spi->base + STM32H7_SPI_CFG2);

	return 0;
}