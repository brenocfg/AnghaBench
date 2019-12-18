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
struct rspi_data {TYPE_1__* ctlr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  qspi_set_receive_trigger (struct rspi_data*,unsigned int) ; 
 unsigned int qspi_set_send_trigger (struct rspi_data*,unsigned int) ; 
 int /*<<< orphan*/  rspi_read_data (struct rspi_data*) ; 
 int rspi_wait_for_rx_full (struct rspi_data*) ; 
 int rspi_wait_for_tx_empty (struct rspi_data*) ; 
 int /*<<< orphan*/  rspi_write_data (struct rspi_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qspi_trigger_transfer_out_in(struct rspi_data *rspi, const u8 *tx,
					u8 *rx, unsigned int len)
{
	unsigned int i, n;
	int ret;

	while (len > 0) {
		n = qspi_set_send_trigger(rspi, len);
		qspi_set_receive_trigger(rspi, len);
		ret = rspi_wait_for_tx_empty(rspi);
		if (ret < 0) {
			dev_err(&rspi->ctlr->dev, "transmit timeout\n");
			return ret;
		}
		for (i = 0; i < n; i++)
			rspi_write_data(rspi, *tx++);

		ret = rspi_wait_for_rx_full(rspi);
		if (ret < 0) {
			dev_err(&rspi->ctlr->dev, "receive timeout\n");
			return ret;
		}
		for (i = 0; i < n; i++)
			*rx++ = rspi_read_data(rspi);

		len -= n;
	}

	return 0;
}