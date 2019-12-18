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
struct stm32_spi {int /*<<< orphan*/  lock; scalar_t__ base; scalar_t__ tx_buf; scalar_t__ rx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  STM32H7_SPI_CR1 ; 
 int /*<<< orphan*/  STM32H7_SPI_CR1_CSTART ; 
 scalar_t__ STM32H7_SPI_IER ; 
 int STM32H7_SPI_IER_DXPIE ; 
 int STM32H7_SPI_IER_EOTIE ; 
 int STM32H7_SPI_IER_MODFIE ; 
 int STM32H7_SPI_IER_OVRIE ; 
 int STM32H7_SPI_IER_RXPIE ; 
 int STM32H7_SPI_IER_TXPIE ; 
 int STM32H7_SPI_IER_TXTFIE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stm32_spi_enable (struct stm32_spi*) ; 
 int /*<<< orphan*/  stm32_spi_set_bits (struct stm32_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32h7_spi_write_txfifo (struct stm32_spi*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int stm32h7_spi_transfer_one_irq(struct stm32_spi *spi)
{
	unsigned long flags;
	u32 ier = 0;

	/* Enable the interrupts relative to the current communication mode */
	if (spi->tx_buf && spi->rx_buf)	/* Full Duplex */
		ier |= STM32H7_SPI_IER_DXPIE;
	else if (spi->tx_buf)		/* Half-Duplex TX dir or Simplex TX */
		ier |= STM32H7_SPI_IER_TXPIE;
	else if (spi->rx_buf)		/* Half-Duplex RX dir or Simplex RX */
		ier |= STM32H7_SPI_IER_RXPIE;

	/* Enable the interrupts relative to the end of transfer */
	ier |= STM32H7_SPI_IER_EOTIE | STM32H7_SPI_IER_TXTFIE |
	       STM32H7_SPI_IER_OVRIE | STM32H7_SPI_IER_MODFIE;

	spin_lock_irqsave(&spi->lock, flags);

	stm32_spi_enable(spi);

	/* Be sure to have data in fifo before starting data transfer */
	if (spi->tx_buf)
		stm32h7_spi_write_txfifo(spi);

	stm32_spi_set_bits(spi, STM32H7_SPI_CR1, STM32H7_SPI_CR1_CSTART);

	writel_relaxed(ier, spi->base + STM32H7_SPI_IER);

	spin_unlock_irqrestore(&spi->lock, flags);

	return 1;
}