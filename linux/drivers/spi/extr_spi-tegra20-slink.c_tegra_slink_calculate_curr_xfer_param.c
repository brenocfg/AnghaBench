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
struct tegra_slink_data {unsigned int cur_pos; unsigned int bytes_per_word; int is_packed; int words_per_32bit; int max_buf_size; unsigned int curr_dma_words; int /*<<< orphan*/  packed_size; } ;
struct spi_transfer {unsigned int len; unsigned int bits_per_word; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,int) ; 
 unsigned int min (unsigned int,int) ; 
 int /*<<< orphan*/  tegra_slink_get_packed_size (struct tegra_slink_data*,struct spi_transfer*) ; 

__attribute__((used)) static unsigned tegra_slink_calculate_curr_xfer_param(
	struct spi_device *spi, struct tegra_slink_data *tspi,
	struct spi_transfer *t)
{
	unsigned remain_len = t->len - tspi->cur_pos;
	unsigned max_word;
	unsigned bits_per_word;
	unsigned max_len;
	unsigned total_fifo_words;

	bits_per_word = t->bits_per_word;
	tspi->bytes_per_word = DIV_ROUND_UP(bits_per_word, 8);

	if (bits_per_word == 8 || bits_per_word == 16) {
		tspi->is_packed = true;
		tspi->words_per_32bit = 32/bits_per_word;
	} else {
		tspi->is_packed = false;
		tspi->words_per_32bit = 1;
	}
	tspi->packed_size = tegra_slink_get_packed_size(tspi, t);

	if (tspi->is_packed) {
		max_len = min(remain_len, tspi->max_buf_size);
		tspi->curr_dma_words = max_len/tspi->bytes_per_word;
		total_fifo_words = max_len/4;
	} else {
		max_word = (remain_len - 1) / tspi->bytes_per_word + 1;
		max_word = min(max_word, tspi->max_buf_size/4);
		tspi->curr_dma_words = max_word;
		total_fifo_words = max_word;
	}
	return total_fifo_words;
}