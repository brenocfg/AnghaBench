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
struct spi_transfer {int cs_change; int /*<<< orphan*/  len; int /*<<< orphan*/  rx_buf; void* delay_usecs; int /*<<< orphan*/  tx_buf; } ;
struct spi_message {int dummy; } ;
struct TYPE_2__ {void* spi_cs_delay; } ;
struct applespi_data {int /*<<< orphan*/  tx_status; int /*<<< orphan*/  tx_buffer; TYPE_1__ spi_settings; struct spi_transfer st_t; struct spi_transfer wr_t; struct spi_transfer wd_t; struct spi_transfer ww_t; struct spi_message wr_m; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPLESPI_PACKET_SIZE ; 
 int /*<<< orphan*/  APPLESPI_STATUS_SIZE ; 
 void* SPI_RW_CHG_DELAY_US ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 

__attribute__((used)) static void applespi_setup_write_txfrs(struct applespi_data *applespi)
{
	struct spi_message *msg = &applespi->wr_m;
	struct spi_transfer *wt_t = &applespi->ww_t;
	struct spi_transfer *dl_t = &applespi->wd_t;
	struct spi_transfer *wr_t = &applespi->wr_t;
	struct spi_transfer *st_t = &applespi->st_t;

	memset(wt_t, 0, sizeof(*wt_t));
	memset(dl_t, 0, sizeof(*dl_t));
	memset(wr_t, 0, sizeof(*wr_t));
	memset(st_t, 0, sizeof(*st_t));

	/*
	 * All we need here is a delay at the beginning of the message before
	 * asserting cs. But the current spi API doesn't support this, so we
	 * end up with an extra unnecessary (but harmless) cs assertion and
	 * deassertion.
	 */
	wt_t->delay_usecs = SPI_RW_CHG_DELAY_US;
	wt_t->cs_change = 1;

	dl_t->delay_usecs = applespi->spi_settings.spi_cs_delay;

	wr_t->tx_buf = applespi->tx_buffer;
	wr_t->len = APPLESPI_PACKET_SIZE;
	wr_t->delay_usecs = SPI_RW_CHG_DELAY_US;

	st_t->rx_buf = applespi->tx_status;
	st_t->len = APPLESPI_STATUS_SIZE;

	spi_message_init(msg);
	spi_message_add_tail(wt_t, msg);
	spi_message_add_tail(dl_t, msg);
	spi_message_add_tail(wr_t, msg);
	spi_message_add_tail(st_t, msg);
}