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
struct st_i2c_client {int /*<<< orphan*/  count; } ;
struct st_i2c_dev {struct st_i2c_client client; } ;

/* Variables and functions */
 int /*<<< orphan*/  st_i2c_flush_rx_fifo (struct st_i2c_dev*) ; 
 int /*<<< orphan*/  st_i2c_terminate_xfer (struct st_i2c_dev*) ; 
 int /*<<< orphan*/  st_i2c_wr_fill_tx_fifo (struct st_i2c_dev*) ; 

__attribute__((used)) static void st_i2c_handle_write(struct st_i2c_dev *i2c_dev)
{
	struct st_i2c_client *c = &i2c_dev->client;

	st_i2c_flush_rx_fifo(i2c_dev);

	if (!c->count)
		/* End of xfer, send stop or repstart */
		st_i2c_terminate_xfer(i2c_dev);
	else
		st_i2c_wr_fill_tx_fifo(i2c_dev);
}