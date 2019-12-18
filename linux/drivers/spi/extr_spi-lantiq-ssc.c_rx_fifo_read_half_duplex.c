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
typedef  unsigned int u32 ;
struct lantiq_ssc_spi {int rx_todo; int /*<<< orphan*/ * rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTQ_SPI_RB ; 
 int /*<<< orphan*/  LTQ_SPI_STAT ; 
 unsigned int LTQ_SPI_STAT_RXBV_M ; 
 unsigned int LTQ_SPI_STAT_RXBV_S ; 
 unsigned int lantiq_ssc_readl (struct lantiq_ssc_spi*,int /*<<< orphan*/ ) ; 
 unsigned int rx_fifo_level (struct lantiq_ssc_spi*) ; 

__attribute__((used)) static void rx_fifo_read_half_duplex(struct lantiq_ssc_spi *spi)
{
	u32 data, *rx32;
	u8 *rx8;
	unsigned int rxbv, shift;
	unsigned int rx_fill = rx_fifo_level(spi);

	/*
	 * In RX-only mode the bits per word value is ignored by HW. A value
	 * of 32 is used instead. Thus all 4 bytes per FIFO must be read.
	 * If remaining RX bytes are less than 4, the FIFO must be read
	 * differently. The amount of received and valid bytes is indicated
	 * by STAT.RXBV register value.
	 */
	while (rx_fill) {
		if (spi->rx_todo < 4)  {
			rxbv = (lantiq_ssc_readl(spi, LTQ_SPI_STAT) &
				LTQ_SPI_STAT_RXBV_M) >> LTQ_SPI_STAT_RXBV_S;
			data = lantiq_ssc_readl(spi, LTQ_SPI_RB);

			shift = (rxbv - 1) * 8;
			rx8 = spi->rx;

			while (rxbv) {
				*rx8++ = (data >> shift) & 0xFF;
				rxbv--;
				shift -= 8;
				spi->rx_todo--;
				spi->rx++;
			}
		} else {
			data = lantiq_ssc_readl(spi, LTQ_SPI_RB);
			rx32 = (u32 *) spi->rx;

			*rx32++ = data;
			spi->rx_todo -= 4;
			spi->rx += 4;
		}
		rx_fill--;
	}
}