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
struct spi_master {int dummy; } ;
struct altera_spi {scalar_t__ count; scalar_t__ len; scalar_t__ base; int /*<<< orphan*/  imr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ ALTERA_SPI_CONTROL ; 
 int /*<<< orphan*/  ALTERA_SPI_CONTROL_IRRDY_MSK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  altera_spi_rx_word (struct altera_spi*) ; 
 int /*<<< orphan*/  altera_spi_tx_word (struct altera_spi*) ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (struct spi_master*) ; 
 struct altera_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t altera_spi_irq(int irq, void *dev)
{
	struct spi_master *master = dev;
	struct altera_spi *hw = spi_master_get_devdata(master);

	altera_spi_rx_word(hw);

	if (hw->count < hw->len) {
		altera_spi_tx_word(hw);
	} else {
		/* disable receive interrupt */
		hw->imr &= ~ALTERA_SPI_CONTROL_IRRDY_MSK;
		writel(hw->imr, hw->base + ALTERA_SPI_CONTROL);

		spi_finalize_current_transfer(master);
	}

	return IRQ_HANDLED;
}