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
struct xlp_spi_priv {int rx_len; int* rx_buf; int /*<<< orphan*/  cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  XLP_SPI_FIFO_WCNT ; 
 int /*<<< orphan*/  XLP_SPI_RXDATA_FIFO ; 
 int XLP_SPI_RXFIFO_WCNT_MASK ; 
 int min (int,int) ; 
 int xlp_spi_reg_read (struct xlp_spi_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xlp_spi_read_rxfifo(struct xlp_spi_priv *xspi)
{
	u32 rx_data, rxfifo_cnt;
	int i, j, nbytes;

	rxfifo_cnt = xlp_spi_reg_read(xspi, xspi->cs, XLP_SPI_FIFO_WCNT);
	rxfifo_cnt &= XLP_SPI_RXFIFO_WCNT_MASK;
	while (rxfifo_cnt) {
		rx_data = xlp_spi_reg_read(xspi, xspi->cs, XLP_SPI_RXDATA_FIFO);
		j = 0;
		nbytes = min(xspi->rx_len, 4);
		for (i = nbytes - 1; i >= 0; i--, j++)
			xspi->rx_buf[i] = (rx_data >> (j * 8)) & 0xff;

		xspi->rx_len -= nbytes;
		xspi->rx_buf += nbytes;
		rxfifo_cnt--;
	}
}