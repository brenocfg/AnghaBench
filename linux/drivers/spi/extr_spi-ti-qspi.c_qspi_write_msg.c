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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ti_qspi {unsigned int cmd; int /*<<< orphan*/  dev; scalar_t__ base; int /*<<< orphan*/  dc; } ;
struct spi_transfer {int bits_per_word; int /*<<< orphan*/ * tx_buf; } ;

/* Variables and functions */
 int EBUSY ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  QSPI_SPI_CMD_REG ; 
 scalar_t__ QSPI_SPI_DATA_REG ; 
 scalar_t__ QSPI_SPI_DATA_REG_1 ; 
 scalar_t__ QSPI_SPI_DATA_REG_2 ; 
 scalar_t__ QSPI_SPI_DATA_REG_3 ; 
 unsigned int QSPI_WLEN (int) ; 
 int QSPI_WLEN_MAX_BITS ; 
 int QSPI_WLEN_MAX_BYTES ; 
 unsigned int QSPI_WR_SNGL ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ qspi_is_busy (struct ti_qspi*) ; 
 scalar_t__ ti_qspi_poll_wc (struct ti_qspi*) ; 
 int /*<<< orphan*/  ti_qspi_write (struct ti_qspi*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/  const,scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int qspi_write_msg(struct ti_qspi *qspi, struct spi_transfer *t,
			  int count)
{
	int wlen, xfer_len;
	unsigned int cmd;
	const u8 *txbuf;
	u32 data;

	txbuf = t->tx_buf;
	cmd = qspi->cmd | QSPI_WR_SNGL;
	wlen = t->bits_per_word >> 3;	/* in bytes */
	xfer_len = wlen;

	while (count) {
		if (qspi_is_busy(qspi))
			return -EBUSY;

		switch (wlen) {
		case 1:
			dev_dbg(qspi->dev, "tx cmd %08x dc %08x data %02x\n",
					cmd, qspi->dc, *txbuf);
			if (count >= QSPI_WLEN_MAX_BYTES) {
				u32 *txp = (u32 *)txbuf;

				data = cpu_to_be32(*txp++);
				writel(data, qspi->base +
				       QSPI_SPI_DATA_REG_3);
				data = cpu_to_be32(*txp++);
				writel(data, qspi->base +
				       QSPI_SPI_DATA_REG_2);
				data = cpu_to_be32(*txp++);
				writel(data, qspi->base +
				       QSPI_SPI_DATA_REG_1);
				data = cpu_to_be32(*txp++);
				writel(data, qspi->base +
				       QSPI_SPI_DATA_REG);
				xfer_len = QSPI_WLEN_MAX_BYTES;
				cmd |= QSPI_WLEN(QSPI_WLEN_MAX_BITS);
			} else {
				writeb(*txbuf, qspi->base + QSPI_SPI_DATA_REG);
				cmd = qspi->cmd | QSPI_WR_SNGL;
				xfer_len = wlen;
				cmd |= QSPI_WLEN(wlen);
			}
			break;
		case 2:
			dev_dbg(qspi->dev, "tx cmd %08x dc %08x data %04x\n",
					cmd, qspi->dc, *txbuf);
			writew(*((u16 *)txbuf), qspi->base + QSPI_SPI_DATA_REG);
			break;
		case 4:
			dev_dbg(qspi->dev, "tx cmd %08x dc %08x data %08x\n",
					cmd, qspi->dc, *txbuf);
			writel(*((u32 *)txbuf), qspi->base + QSPI_SPI_DATA_REG);
			break;
		}

		ti_qspi_write(qspi, cmd, QSPI_SPI_CMD_REG);
		if (ti_qspi_poll_wc(qspi)) {
			dev_err(qspi->dev, "write timed out\n");
			return -ETIMEDOUT;
		}
		txbuf += xfer_len;
		count -= xfer_len;
	}

	return 0;
}