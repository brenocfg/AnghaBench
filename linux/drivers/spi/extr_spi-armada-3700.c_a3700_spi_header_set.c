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
struct a3700_spi {int* tx_buf; int buf_len; } ;

/* Variables and functions */
 unsigned int A3700_SPI_ADDR_CNT_BIT ; 
 unsigned int A3700_SPI_ADDR_CNT_MASK ; 
 int /*<<< orphan*/  A3700_SPI_IF_ADDR_REG ; 
 int /*<<< orphan*/  A3700_SPI_IF_HDR_CNT_REG ; 
 int /*<<< orphan*/  A3700_SPI_IF_INST_REG ; 
 int /*<<< orphan*/  A3700_SPI_IF_RMODE_REG ; 
 int /*<<< orphan*/  spireg_write (struct a3700_spi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void a3700_spi_header_set(struct a3700_spi *a3700_spi)
{
	unsigned int addr_cnt;
	u32 val = 0;

	/* Clear the header registers */
	spireg_write(a3700_spi, A3700_SPI_IF_INST_REG, 0);
	spireg_write(a3700_spi, A3700_SPI_IF_ADDR_REG, 0);
	spireg_write(a3700_spi, A3700_SPI_IF_RMODE_REG, 0);
	spireg_write(a3700_spi, A3700_SPI_IF_HDR_CNT_REG, 0);

	/* Set header counters */
	if (a3700_spi->tx_buf) {
		/*
		 * when tx data is not 4 bytes aligned, there will be unexpected
		 * bytes out of SPI output register, since it always shifts out
		 * as whole 4 bytes. This might cause incorrect transaction with
		 * some devices. To avoid that, use SPI header count feature to
		 * transfer up to 3 bytes of data first, and then make the rest
		 * of data 4-byte aligned.
		 */
		addr_cnt = a3700_spi->buf_len % 4;
		if (addr_cnt) {
			val = (addr_cnt & A3700_SPI_ADDR_CNT_MASK)
				<< A3700_SPI_ADDR_CNT_BIT;
			spireg_write(a3700_spi, A3700_SPI_IF_HDR_CNT_REG, val);

			/* Update the buffer length to be transferred */
			a3700_spi->buf_len -= addr_cnt;

			/* transfer 1~3 bytes through address count */
			val = 0;
			while (addr_cnt--) {
				val = (val << 8) | a3700_spi->tx_buf[0];
				a3700_spi->tx_buf++;
			}
			spireg_write(a3700_spi, A3700_SPI_IF_ADDR_REG, val);
		}
	}
}