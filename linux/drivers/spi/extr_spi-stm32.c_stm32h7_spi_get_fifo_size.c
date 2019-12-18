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
struct stm32_spi {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  STM32H7_SPI_CR1 ; 
 int /*<<< orphan*/  STM32H7_SPI_CR1_SPE ; 
 scalar_t__ STM32H7_SPI_SR ; 
 int STM32H7_SPI_SR_TXP ; 
 scalar_t__ STM32H7_SPI_TXDR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stm32_spi_clr_bits (struct stm32_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_spi_set_bits (struct stm32_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int stm32h7_spi_get_fifo_size(struct stm32_spi *spi)
{
	unsigned long flags;
	u32 count = 0;

	spin_lock_irqsave(&spi->lock, flags);

	stm32_spi_set_bits(spi, STM32H7_SPI_CR1, STM32H7_SPI_CR1_SPE);

	while (readl_relaxed(spi->base + STM32H7_SPI_SR) & STM32H7_SPI_SR_TXP)
		writeb_relaxed(++count, spi->base + STM32H7_SPI_TXDR);

	stm32_spi_clr_bits(spi, STM32H7_SPI_CR1, STM32H7_SPI_CR1_SPE);

	spin_unlock_irqrestore(&spi->lock, flags);

	dev_dbg(spi->dev, "%d x 8-bit fifo size\n", count);

	return count;
}