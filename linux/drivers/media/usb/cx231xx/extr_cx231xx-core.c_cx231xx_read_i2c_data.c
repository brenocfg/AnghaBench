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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct cx231xx_i2c_xfer_data {int dev_addr; int saddr_len; int saddr_dat; int buf_size; int* p_buffer; int /*<<< orphan*/  direction; } ;
struct cx231xx {int (* cx231xx_send_usb_command ) (int /*<<< orphan*/ *,struct cx231xx_i2c_xfer_data*) ;int /*<<< orphan*/ * i2c_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int stub1 (int /*<<< orphan*/ *,struct cx231xx_i2c_xfer_data*) ; 

int cx231xx_read_i2c_data(struct cx231xx *dev, u8 dev_addr, u16 saddr,
			  u8 saddr_len, u32 *data, u8 data_len)
{
	int status = 0;
	struct cx231xx_i2c_xfer_data req_data;
	u8 value[4] = { 0, 0, 0, 0 };

	if (saddr_len == 0)
		saddr = 0;
	else if (saddr_len == 1)
		saddr &= 0xff;

	/* prepare xfer_data struct */
	req_data.dev_addr = dev_addr >> 1;
	req_data.direction = I2C_M_RD;
	req_data.saddr_len = saddr_len;
	req_data.saddr_dat = saddr;
	req_data.buf_size = data_len;
	req_data.p_buffer = (u8 *) value;

	/* usb send command */
	status = dev->cx231xx_send_usb_command(&dev->i2c_bus[0], &req_data);

	if (status >= 0) {
		/* Copy the data read back to main buffer */
		if (data_len == 1)
			*data = value[0];
		else
			*data =
			    value[0] | value[1] << 8 | value[2] << 16 | value[3]
			    << 24;
	}

	return status;
}