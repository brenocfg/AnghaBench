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
typedef  int /*<<< orphan*/  u8 ;
struct spi_transfer {unsigned int len; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct spi_master {int dummy; } ;
struct spi_device {int dummy; } ;
struct sifive_spi {int /*<<< orphan*/  fifo_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIFIVE_SPI_IP_RXWM ; 
 int /*<<< orphan*/  SIFIVE_SPI_IP_TXWM ; 
 int /*<<< orphan*/  SIFIVE_SPI_REG_RXMARK ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 
 int sifive_spi_prep_transfer (struct sifive_spi*,struct spi_device*,struct spi_transfer*) ; 
 int /*<<< orphan*/  sifive_spi_rx (struct sifive_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sifive_spi_tx (struct sifive_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sifive_spi_wait (struct sifive_spi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sifive_spi_write (struct sifive_spi*,int /*<<< orphan*/ ,unsigned int) ; 
 struct sifive_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int
sifive_spi_transfer_one(struct spi_master *master, struct spi_device *device,
			struct spi_transfer *t)
{
	struct sifive_spi *spi = spi_master_get_devdata(master);
	int poll = sifive_spi_prep_transfer(spi, device, t);
	const u8 *tx_ptr = t->tx_buf;
	u8 *rx_ptr = t->rx_buf;
	unsigned int remaining_words = t->len;

	while (remaining_words) {
		unsigned int n_words = min(remaining_words, spi->fifo_depth);
		unsigned int i;

		/* Enqueue n_words for transmission */
		for (i = 0; i < n_words; i++)
			sifive_spi_tx(spi, tx_ptr++);

		if (rx_ptr) {
			/* Wait for transmission + reception to complete */
			sifive_spi_write(spi, SIFIVE_SPI_REG_RXMARK,
					 n_words - 1);
			sifive_spi_wait(spi, SIFIVE_SPI_IP_RXWM, poll);

			/* Read out all the data from the RX FIFO */
			for (i = 0; i < n_words; i++)
				sifive_spi_rx(spi, rx_ptr++);
		} else {
			/* Wait for transmission to complete */
			sifive_spi_wait(spi, SIFIVE_SPI_IP_TXWM, poll);
		}

		remaining_words -= n_words;
	}

	return 0;
}