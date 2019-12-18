#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct geni_se {scalar_t__ base; } ;
struct spi_geni_master {unsigned int tx_fifo_depth; unsigned int tx_wm; unsigned int tx_rem_bytes; TYPE_1__* cur_xfer; struct geni_se se; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/  tx_buf; } ;

/* Variables and functions */
 scalar_t__ SE_GENI_TX_FIFOn ; 
 scalar_t__ SE_GENI_TX_WATERMARK_REG ; 
 unsigned int geni_byte_per_fifo_word (struct spi_geni_master*) ; 
 int /*<<< orphan*/  iowrite32_rep (scalar_t__,int /*<<< orphan*/ *,int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void geni_spi_handle_tx(struct spi_geni_master *mas)
{
	struct geni_se *se = &mas->se;
	unsigned int max_bytes;
	const u8 *tx_buf;
	unsigned int bytes_per_fifo_word = geni_byte_per_fifo_word(mas);
	unsigned int i = 0;

	max_bytes = (mas->tx_fifo_depth - mas->tx_wm) * bytes_per_fifo_word;
	if (mas->tx_rem_bytes < max_bytes)
		max_bytes = mas->tx_rem_bytes;

	tx_buf = mas->cur_xfer->tx_buf + mas->cur_xfer->len - mas->tx_rem_bytes;
	while (i < max_bytes) {
		unsigned int j;
		unsigned int bytes_to_write;
		u32 fifo_word = 0;
		u8 *fifo_byte = (u8 *)&fifo_word;

		bytes_to_write = min(bytes_per_fifo_word, max_bytes - i);
		for (j = 0; j < bytes_to_write; j++)
			fifo_byte[j] = tx_buf[i++];
		iowrite32_rep(se->base + SE_GENI_TX_FIFOn, &fifo_word, 1);
	}
	mas->tx_rem_bytes -= max_bytes;
	if (!mas->tx_rem_bytes)
		writel(0, se->base + SE_GENI_TX_WATERMARK_REG);
}