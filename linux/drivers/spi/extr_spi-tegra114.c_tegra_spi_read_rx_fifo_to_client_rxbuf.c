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
typedef  unsigned int u8 ;
typedef  unsigned int u32 ;
struct tegra_spi_data {int cur_rx_pos; unsigned int curr_dma_words; unsigned int bytes_per_word; unsigned int cur_pos; scalar_t__ is_packed; } ;
struct spi_transfer {unsigned int bits_per_word; unsigned int len; scalar_t__ rx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_FIFO_STATUS ; 
 int /*<<< orphan*/  SPI_RX_FIFO ; 
 unsigned int SPI_RX_FIFO_FULL_COUNT (unsigned int) ; 
 unsigned int tegra_spi_readl (struct tegra_spi_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int tegra_spi_read_rx_fifo_to_client_rxbuf(
		struct tegra_spi_data *tspi, struct spi_transfer *t)
{
	unsigned rx_full_count;
	u32 fifo_status;
	unsigned i, count;
	unsigned int read_words = 0;
	unsigned len;
	u8 *rx_buf = (u8 *)t->rx_buf + tspi->cur_rx_pos;

	fifo_status = tegra_spi_readl(tspi, SPI_FIFO_STATUS);
	rx_full_count = SPI_RX_FIFO_FULL_COUNT(fifo_status);
	if (tspi->is_packed) {
		len = tspi->curr_dma_words * tspi->bytes_per_word;
		for (count = 0; count < rx_full_count; count++) {
			u32 x = tegra_spi_readl(tspi, SPI_RX_FIFO);

			for (i = 0; len && (i < 4); i++, len--)
				*rx_buf++ = (x >> i*8) & 0xFF;
		}
		read_words += tspi->curr_dma_words;
		tspi->cur_rx_pos += tspi->curr_dma_words * tspi->bytes_per_word;
	} else {
		u32 rx_mask = ((u32)1 << t->bits_per_word) - 1;
		u8 bytes_per_word = tspi->bytes_per_word;
		unsigned int read_bytes;

		len = rx_full_count * bytes_per_word;
		if (len > t->len - tspi->cur_pos)
			len = t->len - tspi->cur_pos;
		read_bytes = len;
		for (count = 0; count < rx_full_count; count++) {
			u32 x = tegra_spi_readl(tspi, SPI_RX_FIFO) & rx_mask;

			for (i = 0; len && (i < bytes_per_word); i++, len--)
				*rx_buf++ = (x >> (i*8)) & 0xFF;
		}
		read_words += rx_full_count;
		tspi->cur_rx_pos += read_bytes;
	}

	return read_words;
}