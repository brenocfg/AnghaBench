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
struct stm32_spi {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  STM32H7_SPI_CFG2 ; 
 int STM32H7_SPI_CFG2_AFCNTR ; 
 int STM32H7_SPI_CFG2_MASTER ; 
 int STM32H7_SPI_CFG2_SSM ; 
 int /*<<< orphan*/  STM32H7_SPI_CR1 ; 
 int STM32H7_SPI_CR1_HDDIR ; 
 int STM32H7_SPI_CR1_MASRX ; 
 int STM32H7_SPI_CR1_SSI ; 
 int /*<<< orphan*/  STM32H7_SPI_I2SCFGR ; 
 int /*<<< orphan*/  STM32H7_SPI_I2SCFGR_I2SMOD ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stm32_spi_clr_bits (struct stm32_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_spi_set_bits (struct stm32_spi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stm32h7_spi_config(struct stm32_spi *spi)
{
	unsigned long flags;

	spin_lock_irqsave(&spi->lock, flags);

	/* Ensure I2SMOD bit is kept cleared */
	stm32_spi_clr_bits(spi, STM32H7_SPI_I2SCFGR,
			   STM32H7_SPI_I2SCFGR_I2SMOD);

	/*
	 * - SS input value high
	 * - transmitter half duplex direction
	 * - automatic communication suspend when RX-Fifo is full
	 */
	stm32_spi_set_bits(spi, STM32H7_SPI_CR1, STM32H7_SPI_CR1_SSI |
						 STM32H7_SPI_CR1_HDDIR |
						 STM32H7_SPI_CR1_MASRX);

	/*
	 * - Set the master mode (default Motorola mode)
	 * - Consider 1 master/n slaves configuration and
	 *   SS input value is determined by the SSI bit
	 * - keep control of all associated GPIOs
	 */
	stm32_spi_set_bits(spi, STM32H7_SPI_CFG2, STM32H7_SPI_CFG2_MASTER |
						  STM32H7_SPI_CFG2_SSM |
						  STM32H7_SPI_CFG2_AFCNTR);

	spin_unlock_irqrestore(&spi->lock, flags);

	return 0;
}