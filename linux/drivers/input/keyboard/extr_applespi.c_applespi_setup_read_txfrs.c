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
struct spi_transfer {int /*<<< orphan*/  len; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  delay_usecs; } ;
struct spi_message {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  spi_cs_delay; } ;
struct applespi_data {int /*<<< orphan*/  rx_buffer; TYPE_1__ spi_settings; struct spi_transfer rd_t; struct spi_transfer dl_t; struct spi_message rd_m; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPLESPI_PACKET_SIZE ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 

__attribute__((used)) static void applespi_setup_read_txfrs(struct applespi_data *applespi)
{
	struct spi_message *msg = &applespi->rd_m;
	struct spi_transfer *dl_t = &applespi->dl_t;
	struct spi_transfer *rd_t = &applespi->rd_t;

	memset(dl_t, 0, sizeof(*dl_t));
	memset(rd_t, 0, sizeof(*rd_t));

	dl_t->delay_usecs = applespi->spi_settings.spi_cs_delay;

	rd_t->rx_buf = applespi->rx_buffer;
	rd_t->len = APPLESPI_PACKET_SIZE;

	spi_message_init(msg);
	spi_message_add_tail(dl_t, msg);
	spi_message_add_tail(rd_t, msg);
}