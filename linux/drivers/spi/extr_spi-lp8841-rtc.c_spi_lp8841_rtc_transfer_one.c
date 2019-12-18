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
struct spi_transfer {unsigned int len; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct spi_master {int dummy; } ;
struct spi_lp8841_rtc {int /*<<< orphan*/  iomem; int /*<<< orphan*/  state; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SPI_LP8841_RTC_nWE ; 
 int /*<<< orphan*/  SPI_MASTER_NO_RX ; 
 int /*<<< orphan*/  SPI_MASTER_NO_TX ; 
 int /*<<< orphan*/  bitbang_txrx_be_cpha0_lsb (struct spi_lp8841_rtc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (struct spi_master*) ; 
 struct spi_lp8841_rtc* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spi_lp8841_rtc_transfer_one(struct spi_master *master,
			    struct spi_device *spi,
			    struct spi_transfer *t)
{
	struct spi_lp8841_rtc	*data = spi_master_get_devdata(master);
	unsigned		count = t->len;
	const u8		*tx = t->tx_buf;
	u8			*rx = t->rx_buf;
	u8			word = 0;
	int			ret = 0;

	if (tx) {
		data->state &= ~SPI_LP8841_RTC_nWE;
		writeb(data->state, data->iomem);
		while (likely(count > 0)) {
			word = *tx++;
			bitbang_txrx_be_cpha0_lsb(data, 1, 0,
					SPI_MASTER_NO_RX, word, 8);
			count--;
		}
	} else if (rx) {
		data->state |= SPI_LP8841_RTC_nWE;
		writeb(data->state, data->iomem);
		while (likely(count > 0)) {
			word = bitbang_txrx_be_cpha0_lsb(data, 1, 0,
					SPI_MASTER_NO_TX, word, 8);
			*rx++ = word;
			count--;
		}
	} else {
		ret = -EINVAL;
	}

	spi_finalize_current_transfer(master);

	return ret;
}