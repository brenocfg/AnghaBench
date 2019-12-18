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
struct tegra_spi_data {unsigned int curr_dma_words; unsigned int bytes_per_word; int cur_rx_pos; int* rx_dma_buf; unsigned int cur_pos; int /*<<< orphan*/  dma_buf_size; int /*<<< orphan*/  rx_dma_phys; int /*<<< orphan*/  dev; scalar_t__ is_packed; } ;
struct spi_transfer {unsigned char* rx_buf; int bits_per_word; unsigned int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int*,unsigned int) ; 

__attribute__((used)) static void tegra_spi_copy_spi_rxbuf_to_client_rxbuf(
		struct tegra_spi_data *tspi, struct spi_transfer *t)
{
	/* Make the dma buffer to read by cpu */
	dma_sync_single_for_cpu(tspi->dev, tspi->rx_dma_phys,
		tspi->dma_buf_size, DMA_FROM_DEVICE);

	if (tspi->is_packed) {
		unsigned len = tspi->curr_dma_words * tspi->bytes_per_word;

		memcpy(t->rx_buf + tspi->cur_rx_pos, tspi->rx_dma_buf, len);
		tspi->cur_rx_pos += tspi->curr_dma_words * tspi->bytes_per_word;
	} else {
		unsigned int i;
		unsigned int count;
		unsigned char *rx_buf = t->rx_buf + tspi->cur_rx_pos;
		u32 rx_mask = ((u32)1 << t->bits_per_word) - 1;
		unsigned consume = tspi->curr_dma_words * tspi->bytes_per_word;
		unsigned int read_bytes;

		if (consume > t->len - tspi->cur_pos)
			consume = t->len - tspi->cur_pos;
		read_bytes = consume;
		for (count = 0; count < tspi->curr_dma_words; count++) {
			u32 x = tspi->rx_dma_buf[count] & rx_mask;

			for (i = 0; consume && (i < tspi->bytes_per_word);
							i++, consume--)
				*rx_buf++ = (x >> (i*8)) & 0xFF;
		}

		tspi->cur_rx_pos += read_bytes;
	}

	/* Make the dma buffer to read by dma */
	dma_sync_single_for_device(tspi->dev, tspi->rx_dma_phys,
		tspi->dma_buf_size, DMA_FROM_DEVICE);
}