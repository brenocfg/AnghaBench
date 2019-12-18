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
struct a3700_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A3700_SPI_IF_CFG_REG ; 
 int A3700_SPI_TIMEOUT ; 
 int A3700_SPI_XFER_START ; 
 int A3700_SPI_XFER_STOP ; 
 int /*<<< orphan*/  a3700_spi_fifo_flush (struct a3700_spi*) ; 
 int spireg_read (struct a3700_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spireg_write (struct a3700_spi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void a3700_spi_transfer_abort_fifo(struct a3700_spi *a3700_spi)
{
	int timeout = A3700_SPI_TIMEOUT;
	u32 val;

	val = spireg_read(a3700_spi, A3700_SPI_IF_CFG_REG);
	val |= A3700_SPI_XFER_STOP;
	spireg_write(a3700_spi, A3700_SPI_IF_CFG_REG, val);

	while (--timeout) {
		val = spireg_read(a3700_spi, A3700_SPI_IF_CFG_REG);
		if (!(val & A3700_SPI_XFER_START))
			break;
		udelay(1);
	}

	a3700_spi_fifo_flush(a3700_spi);

	val &= ~A3700_SPI_XFER_STOP;
	spireg_write(a3700_spi, A3700_SPI_IF_CFG_REG, val);
}