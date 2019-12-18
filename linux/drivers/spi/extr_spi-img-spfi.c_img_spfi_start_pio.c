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
struct spi_transfer {void* tx_buf; unsigned int len; int speed_hz; void* rx_buf; } ;
struct spi_master {int dummy; } ;
struct spi_device {int /*<<< orphan*/  master; } ;
struct img_spfi {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 unsigned int spfi_pio_read32 (struct img_spfi*,void*,unsigned int) ; 
 unsigned int spfi_pio_read8 (struct img_spfi*,void*,unsigned int) ; 
 unsigned int spfi_pio_write32 (struct img_spfi*,void const*,unsigned int) ; 
 unsigned int spfi_pio_write8 (struct img_spfi*,void const*,unsigned int) ; 
 int /*<<< orphan*/  spfi_start (struct img_spfi*) ; 
 int spfi_wait_all_done (struct img_spfi*) ; 
 struct img_spfi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int img_spfi_start_pio(struct spi_master *master,
			       struct spi_device *spi,
			       struct spi_transfer *xfer)
{
	struct img_spfi *spfi = spi_master_get_devdata(spi->master);
	unsigned int tx_bytes = 0, rx_bytes = 0;
	const void *tx_buf = xfer->tx_buf;
	void *rx_buf = xfer->rx_buf;
	unsigned long timeout;
	int ret;

	if (tx_buf)
		tx_bytes = xfer->len;
	if (rx_buf)
		rx_bytes = xfer->len;

	spfi_start(spfi);

	timeout = jiffies +
		msecs_to_jiffies(xfer->len * 8 * 1000 / xfer->speed_hz + 100);
	while ((tx_bytes > 0 || rx_bytes > 0) &&
	       time_before(jiffies, timeout)) {
		unsigned int tx_count, rx_count;

		if (tx_bytes >= 4)
			tx_count = spfi_pio_write32(spfi, tx_buf, tx_bytes);
		else
			tx_count = spfi_pio_write8(spfi, tx_buf, tx_bytes);

		if (rx_bytes >= 4)
			rx_count = spfi_pio_read32(spfi, rx_buf, rx_bytes);
		else
			rx_count = spfi_pio_read8(spfi, rx_buf, rx_bytes);

		tx_buf += tx_count;
		rx_buf += rx_count;
		tx_bytes -= tx_count;
		rx_bytes -= rx_count;

		cpu_relax();
	}

	if (rx_bytes > 0 || tx_bytes > 0) {
		dev_err(spfi->dev, "PIO transfer timed out\n");
		return -ETIMEDOUT;
	}

	ret = spfi_wait_all_done(spfi);
	if (ret < 0)
		return ret;

	return 0;
}