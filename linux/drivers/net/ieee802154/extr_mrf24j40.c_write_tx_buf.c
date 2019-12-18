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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_2__ {size_t len; int /*<<< orphan*/  const* tx_buf; } ;
struct mrf24j40 {int* tx_hdr_buf; int* tx_len_buf; int /*<<< orphan*/  tx_msg; int /*<<< orphan*/  spi; TYPE_1__ tx_buf_trx; } ;

/* Variables and functions */
 int MRF24J40_WRITELONG (int) ; 
 int TX_FIFO_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printdev (struct mrf24j40*) ; 
 int spi_async (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int write_tx_buf(struct mrf24j40 *devrec, u16 reg,
			const u8 *data, size_t length)
{
	u16 cmd;
	int ret;

	/* Range check the length. 2 bytes are used for the length fields.*/
	if (length > TX_FIFO_SIZE-2) {
		dev_err(printdev(devrec), "write_tx_buf() was passed too large a buffer. Performing short write.\n");
		length = TX_FIFO_SIZE-2;
	}

	cmd = MRF24J40_WRITELONG(reg);
	devrec->tx_hdr_buf[0] = cmd >> 8 & 0xff;
	devrec->tx_hdr_buf[1] = cmd & 0xff;
	devrec->tx_len_buf[0] = 0x0; /* Header Length. Set to 0 for now. TODO */
	devrec->tx_len_buf[1] = length; /* Total length */
	devrec->tx_buf_trx.tx_buf = data;
	devrec->tx_buf_trx.len = length;

	ret = spi_async(devrec->spi, &devrec->tx_msg);
	if (ret)
		dev_err(printdev(devrec), "SPI write Failed for TX buf\n");

	return ret;
}