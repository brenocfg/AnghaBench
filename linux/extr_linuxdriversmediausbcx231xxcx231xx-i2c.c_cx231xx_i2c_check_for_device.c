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
struct i2c_msg {int /*<<< orphan*/  addr; } ;
struct i2c_adapter {struct cx231xx_i2c* algo_data; } ;
struct cx231xx_i2c_xfer_data {int buf_size; int /*<<< orphan*/ * p_buffer; scalar_t__ saddr_dat; scalar_t__ saddr_len; int /*<<< orphan*/  direction; int /*<<< orphan*/  dev_addr; } ;
struct cx231xx_i2c {struct cx231xx* dev; } ;
struct cx231xx {int (* cx231xx_send_usb_command ) (struct cx231xx_i2c*,struct cx231xx_i2c_xfer_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int stub1 (struct cx231xx_i2c*,struct cx231xx_i2c_xfer_data*) ; 

__attribute__((used)) static int cx231xx_i2c_check_for_device(struct i2c_adapter *i2c_adap,
					const struct i2c_msg *msg)
{
	struct cx231xx_i2c *bus = i2c_adap->algo_data;
	struct cx231xx *dev = bus->dev;
	struct cx231xx_i2c_xfer_data req_data;
	int status = 0;
	u8 buf[1];

	/* prepare xfer_data struct */
	req_data.dev_addr = msg->addr;
	req_data.direction = I2C_M_RD;
	req_data.saddr_len = 0;
	req_data.saddr_dat = 0;
	req_data.buf_size = 1;
	req_data.p_buffer = buf;

	/* usb send command */
	status = dev->cx231xx_send_usb_command(bus, &req_data);

	return status < 0 ? status : 0;
}