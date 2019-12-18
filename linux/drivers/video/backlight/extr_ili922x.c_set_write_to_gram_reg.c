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
struct spi_transfer {unsigned char* tx_buf; int cs_change; int bits_per_word; int len; int /*<<< orphan*/ * rx_buf; } ;
struct spi_message {int dummy; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int CMD_BUFSIZE ; 
 unsigned char REG_WRITE_DATA_TO_GRAM ; 
 unsigned char START_BYTE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_RS_INDEX ; 
 int /*<<< orphan*/  START_RW_WRITE ; 
 int /*<<< orphan*/  ili922x_id ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int /*<<< orphan*/  spi_sync (struct spi_device*,struct spi_message*) ; 

__attribute__((used)) static void set_write_to_gram_reg(struct spi_device *spi)
{
	struct spi_message msg;
	struct spi_transfer xfer;
	unsigned char tbuf[CMD_BUFSIZE];

	memset(&xfer, 0, sizeof(struct spi_transfer));

	spi_message_init(&msg);
	xfer.tx_buf = tbuf;
	xfer.rx_buf = NULL;
	xfer.cs_change = 1;

	tbuf[0] = START_BYTE(ili922x_id, START_RS_INDEX, START_RW_WRITE);
	tbuf[1] = 0;
	tbuf[2] = REG_WRITE_DATA_TO_GRAM;

	xfer.bits_per_word = 8;
	xfer.len = 3;
	spi_message_add_tail(&xfer, &msg);
	spi_sync(spi, &msg);
}