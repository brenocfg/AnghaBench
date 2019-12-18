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
struct spi_transfer {int dummy; } ;
struct spi_master {int dummy; } ;
struct spi_device {int dummy; } ;
struct a3700_spi {int buf_len; int byte_len; int* tx_buf; int rx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  A3700_SPI_DATA_IN_REG ; 
 int /*<<< orphan*/  A3700_SPI_DATA_OUT_REG ; 
 int /*<<< orphan*/  A3700_SPI_IF_CTRL_REG ; 
 int A3700_SPI_XFER_DONE ; 
 int /*<<< orphan*/  a3700_spi_bytelen_set (struct a3700_spi*,int) ; 
 int /*<<< orphan*/  a3700_spi_fifo_mode_set (struct a3700_spi*,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  memcpy (int,int*,int) ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (struct spi_master*) ; 
 struct a3700_spi* spi_master_get_devdata (struct spi_master*) ; 
 int spireg_read (struct a3700_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spireg_write (struct a3700_spi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int a3700_spi_transfer_one_full_duplex(struct spi_master *master,
				  struct spi_device *spi,
				  struct spi_transfer *xfer)
{
	struct a3700_spi *a3700_spi = spi_master_get_devdata(master);
	u32 val;

	/* Disable FIFO mode */
	a3700_spi_fifo_mode_set(a3700_spi, false);

	while (a3700_spi->buf_len) {

		/* When we have less than 4 bytes to transfer, switch to 1 byte
		 * mode. This is reset after each transfer
		 */
		if (a3700_spi->buf_len < 4)
			a3700_spi_bytelen_set(a3700_spi, 1);

		if (a3700_spi->byte_len == 1)
			val = *a3700_spi->tx_buf;
		else
			val = *(u32 *)a3700_spi->tx_buf;

		spireg_write(a3700_spi, A3700_SPI_DATA_OUT_REG, val);

		/* Wait for all the data to be shifted in / out */
		while (!(spireg_read(a3700_spi, A3700_SPI_IF_CTRL_REG) &
				A3700_SPI_XFER_DONE))
			cpu_relax();

		val = spireg_read(a3700_spi, A3700_SPI_DATA_IN_REG);

		memcpy(a3700_spi->rx_buf, &val, a3700_spi->byte_len);

		a3700_spi->buf_len -= a3700_spi->byte_len;
		a3700_spi->tx_buf += a3700_spi->byte_len;
		a3700_spi->rx_buf += a3700_spi->byte_len;

	}

	spi_finalize_current_transfer(master);

	return 0;
}