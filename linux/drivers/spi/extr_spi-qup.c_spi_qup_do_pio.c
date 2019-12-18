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
typedef  int /*<<< orphan*/  u32 ;
struct spi_transfer {scalar_t__ rx_buf; scalar_t__ tx_buf; } ;
struct spi_qup {int n_words; int in_fifo_sz; scalar_t__ mode; int /*<<< orphan*/  done; int /*<<< orphan*/  dev; scalar_t__ rx_buf; scalar_t__ tx_buf; } ;
struct spi_master {int dummy; } ;
struct spi_device {struct spi_master* master; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ QUP_IO_M_MODE_FIFO ; 
 int /*<<< orphan*/  QUP_STATE_PAUSE ; 
 int /*<<< orphan*/  QUP_STATE_RUN ; 
 int SPI_MAX_XFER ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct spi_qup* spi_master_get_devdata (struct spi_master*) ; 
 int spi_qup_io_config (struct spi_device*,struct spi_transfer*) ; 
 int spi_qup_set_state (struct spi_qup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_qup_write (struct spi_qup*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int spi_qup_do_pio(struct spi_device *spi, struct spi_transfer *xfer,
			  unsigned long timeout)
{
	struct spi_master *master = spi->master;
	struct spi_qup *qup = spi_master_get_devdata(master);
	int ret, n_words, iterations, offset = 0;

	n_words = qup->n_words;
	iterations = n_words / SPI_MAX_XFER; /* round down */
	qup->rx_buf = xfer->rx_buf;
	qup->tx_buf = xfer->tx_buf;

	do {
		if (iterations)
			qup->n_words = SPI_MAX_XFER;
		else
			qup->n_words = n_words % SPI_MAX_XFER;

		if (qup->tx_buf && offset)
			qup->tx_buf = xfer->tx_buf + offset * SPI_MAX_XFER;

		if (qup->rx_buf && offset)
			qup->rx_buf = xfer->rx_buf + offset * SPI_MAX_XFER;

		/*
		 * if the transaction is small enough, we need
		 * to fallback to FIFO mode
		 */
		if (qup->n_words <= (qup->in_fifo_sz / sizeof(u32)))
			qup->mode = QUP_IO_M_MODE_FIFO;

		ret = spi_qup_io_config(spi, xfer);
		if (ret)
			return ret;

		ret = spi_qup_set_state(qup, QUP_STATE_RUN);
		if (ret) {
			dev_warn(qup->dev, "cannot set RUN state\n");
			return ret;
		}

		ret = spi_qup_set_state(qup, QUP_STATE_PAUSE);
		if (ret) {
			dev_warn(qup->dev, "cannot set PAUSE state\n");
			return ret;
		}

		if (qup->mode == QUP_IO_M_MODE_FIFO)
			spi_qup_write(qup);

		ret = spi_qup_set_state(qup, QUP_STATE_RUN);
		if (ret) {
			dev_warn(qup->dev, "cannot set RUN state\n");
			return ret;
		}

		if (!wait_for_completion_timeout(&qup->done, timeout))
			return -ETIMEDOUT;

		offset++;
	} while (iterations--);

	return 0;
}