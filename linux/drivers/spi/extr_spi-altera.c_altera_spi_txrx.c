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
struct spi_transfer {int len; int /*<<< orphan*/  bits_per_word; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct spi_master {int dummy; } ;
struct spi_device {int dummy; } ;
struct altera_spi {int count; int bytes_per_word; int len; scalar_t__ irq; scalar_t__ base; int /*<<< orphan*/  imr; int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 scalar_t__ ALTERA_SPI_CONTROL ; 
 int /*<<< orphan*/  ALTERA_SPI_CONTROL_IRRDY_MSK ; 
 scalar_t__ ALTERA_SPI_STATUS ; 
 int ALTERA_SPI_STATUS_RRDY_MSK ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  altera_spi_rx_word (struct altera_spi*) ; 
 int /*<<< orphan*/  altera_spi_tx_word (struct altera_spi*) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (struct spi_master*) ; 
 struct altera_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int altera_spi_txrx(struct spi_master *master,
	struct spi_device *spi, struct spi_transfer *t)
{
	struct altera_spi *hw = spi_master_get_devdata(master);

	hw->tx = t->tx_buf;
	hw->rx = t->rx_buf;
	hw->count = 0;
	hw->bytes_per_word = DIV_ROUND_UP(t->bits_per_word, 8);
	hw->len = t->len / hw->bytes_per_word;

	if (hw->irq >= 0) {
		/* enable receive interrupt */
		hw->imr |= ALTERA_SPI_CONTROL_IRRDY_MSK;
		writel(hw->imr, hw->base + ALTERA_SPI_CONTROL);

		/* send the first byte */
		altera_spi_tx_word(hw);
	} else {
		while (hw->count < hw->len) {
			altera_spi_tx_word(hw);

			while (!(readl(hw->base + ALTERA_SPI_STATUS) &
				 ALTERA_SPI_STATUS_RRDY_MSK))
				cpu_relax();

			altera_spi_rx_word(hw);
		}
		spi_finalize_current_transfer(master);
	}

	return t->len;
}