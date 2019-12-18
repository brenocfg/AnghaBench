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
typedef  unsigned int u32 ;
struct geni_se {scalar_t__ base; } ;
struct spi_geni_master {unsigned int rx_rem_bytes; TYPE_1__* cur_xfer; struct geni_se se; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/  rx_buf; } ;

/* Variables and functions */
 unsigned int RX_FIFO_WC_MSK ; 
 unsigned int RX_LAST ; 
 unsigned int RX_LAST_BYTE_VALID_MSK ; 
 unsigned int RX_LAST_BYTE_VALID_SHFT ; 
 scalar_t__ SE_GENI_RX_FIFO_STATUS ; 
 scalar_t__ SE_GENI_RX_FIFOn ; 
 unsigned int geni_byte_per_fifo_word (struct spi_geni_master*) ; 
 int /*<<< orphan*/  ioread32_rep (scalar_t__,unsigned int*,int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static void geni_spi_handle_rx(struct spi_geni_master *mas)
{
	struct geni_se *se = &mas->se;
	u32 rx_fifo_status;
	unsigned int rx_bytes;
	unsigned int rx_last_byte_valid;
	u8 *rx_buf;
	unsigned int bytes_per_fifo_word = geni_byte_per_fifo_word(mas);
	unsigned int i = 0;

	rx_fifo_status = readl(se->base + SE_GENI_RX_FIFO_STATUS);
	rx_bytes = (rx_fifo_status & RX_FIFO_WC_MSK) * bytes_per_fifo_word;
	if (rx_fifo_status & RX_LAST) {
		rx_last_byte_valid = rx_fifo_status & RX_LAST_BYTE_VALID_MSK;
		rx_last_byte_valid >>= RX_LAST_BYTE_VALID_SHFT;
		if (rx_last_byte_valid && rx_last_byte_valid < 4)
			rx_bytes -= bytes_per_fifo_word - rx_last_byte_valid;
	}
	if (mas->rx_rem_bytes < rx_bytes)
		rx_bytes = mas->rx_rem_bytes;

	rx_buf = mas->cur_xfer->rx_buf + mas->cur_xfer->len - mas->rx_rem_bytes;
	while (i < rx_bytes) {
		u32 fifo_word = 0;
		u8 *fifo_byte = (u8 *)&fifo_word;
		unsigned int bytes_to_read;
		unsigned int j;

		bytes_to_read = min(bytes_per_fifo_word, rx_bytes - i);
		ioread32_rep(se->base + SE_GENI_RX_FIFOn, &fifo_word, 1);
		for (j = 0; j < bytes_to_read; j++)
			rx_buf[i++] = fifo_byte[j];
	}
	mas->rx_rem_bytes -= rx_bytes;
}