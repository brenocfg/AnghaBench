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
struct stm32_spi {int /*<<< orphan*/  lock; scalar_t__ base; scalar_t__ dma_rx; scalar_t__ cur_usedma; scalar_t__ dma_tx; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ STM32F4_SPI_CR1 ; 
 int STM32F4_SPI_CR1_SPE ; 
 scalar_t__ STM32F4_SPI_CR2 ; 
 int STM32F4_SPI_CR2_ERRIE ; 
 int STM32F4_SPI_CR2_RXDMAEN ; 
 int STM32F4_SPI_CR2_RXNEIE ; 
 int STM32F4_SPI_CR2_TXDMAEN ; 
 int STM32F4_SPI_CR2_TXEIE ; 
 scalar_t__ STM32F4_SPI_DR ; 
 scalar_t__ STM32F4_SPI_SR ; 
 int STM32F4_SPI_SR_BSY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (scalar_t__) ; 
 int readl_relaxed (scalar_t__) ; 
 scalar_t__ readl_relaxed_poll_timeout_atomic (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stm32_spi_clr_bits (struct stm32_spi*,scalar_t__,int) ; 

__attribute__((used)) static void stm32f4_spi_disable(struct stm32_spi *spi)
{
	unsigned long flags;
	u32 sr;

	dev_dbg(spi->dev, "disable controller\n");

	spin_lock_irqsave(&spi->lock, flags);

	if (!(readl_relaxed(spi->base + STM32F4_SPI_CR1) &
	      STM32F4_SPI_CR1_SPE)) {
		spin_unlock_irqrestore(&spi->lock, flags);
		return;
	}

	/* Disable interrupts */
	stm32_spi_clr_bits(spi, STM32F4_SPI_CR2, STM32F4_SPI_CR2_TXEIE |
						 STM32F4_SPI_CR2_RXNEIE |
						 STM32F4_SPI_CR2_ERRIE);

	/* Wait until BSY = 0 */
	if (readl_relaxed_poll_timeout_atomic(spi->base + STM32F4_SPI_SR,
					      sr, !(sr & STM32F4_SPI_SR_BSY),
					      10, 100000) < 0) {
		dev_warn(spi->dev, "disabling condition timeout\n");
	}

	if (spi->cur_usedma && spi->dma_tx)
		dmaengine_terminate_all(spi->dma_tx);
	if (spi->cur_usedma && spi->dma_rx)
		dmaengine_terminate_all(spi->dma_rx);

	stm32_spi_clr_bits(spi, STM32F4_SPI_CR1, STM32F4_SPI_CR1_SPE);

	stm32_spi_clr_bits(spi, STM32F4_SPI_CR2, STM32F4_SPI_CR2_TXDMAEN |
						 STM32F4_SPI_CR2_RXDMAEN);

	/* Sequence to clear OVR flag */
	readl_relaxed(spi->base + STM32F4_SPI_DR);
	readl_relaxed(spi->base + STM32F4_SPI_SR);

	spin_unlock_irqrestore(&spi->lock, flags);
}