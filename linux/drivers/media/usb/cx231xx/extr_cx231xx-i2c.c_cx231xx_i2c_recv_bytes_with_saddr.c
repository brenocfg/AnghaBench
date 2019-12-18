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
typedef  int u16 ;
struct i2c_msg {int len; int* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {struct cx231xx_i2c* algo_data; } ;
struct cx231xx_i2c_xfer_data {int saddr_len; int saddr_dat; int buf_size; int* p_buffer; int /*<<< orphan*/  direction; int /*<<< orphan*/  dev_addr; } ;
struct cx231xx_i2c {struct cx231xx* dev; } ;
struct cx231xx {int (* cx231xx_gpio_i2c_write ) (struct cx231xx*,int /*<<< orphan*/ ,int*,int) ;int (* cx231xx_gpio_i2c_read ) (struct cx231xx*,int /*<<< orphan*/ ,int*,int) ;int (* cx231xx_send_usb_command ) (struct cx231xx_i2c*,struct cx231xx_i2c_xfer_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TUNER_XC5000 ; 
 int /*<<< orphan*/  dprintk1 (int,char*,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ is_tuner (struct cx231xx*,struct cx231xx_i2c*,struct i2c_msg const*,int /*<<< orphan*/ ) ; 
 int stub1 (struct cx231xx*,int /*<<< orphan*/ ,int*,int) ; 
 int stub2 (struct cx231xx*,int /*<<< orphan*/ ,int*,int) ; 
 int stub3 (struct cx231xx_i2c*,struct cx231xx_i2c_xfer_data*) ; 

__attribute__((used)) static int cx231xx_i2c_recv_bytes_with_saddr(struct i2c_adapter *i2c_adap,
					     const struct i2c_msg *msg1,
					     const struct i2c_msg *msg2)
{
	struct cx231xx_i2c *bus = i2c_adap->algo_data;
	struct cx231xx *dev = bus->dev;
	struct cx231xx_i2c_xfer_data req_data;
	int status = 0;
	u16 saddr = 0;
	u8 need_gpio = 0;

	if (msg1->len == 2)
		saddr = msg1->buf[0] << 8 | msg1->buf[1];
	else if (msg1->len == 1)
		saddr = msg1->buf[0];

	if (is_tuner(dev, bus, msg2, TUNER_XC5000)) {
		if ((msg2->len < 16)) {

			dprintk1(1,
			"i2c_read: addr 0x%x, len %d, saddr 0x%x, len %d\n",
			msg2->addr, msg2->len, saddr, msg1->len);

			switch (saddr) {
			case 0x0008:	/* read FW load status */
				need_gpio = 1;
				break;
			case 0x0004:	/* read Lock status */
				need_gpio = 1;
				break;
			}

			if (need_gpio) {
				status =
				    dev->cx231xx_gpio_i2c_write(dev, msg1->addr,
								msg1->buf,
								msg1->len);
				status =
				    dev->cx231xx_gpio_i2c_read(dev, msg2->addr,
							       msg2->buf,
							       msg2->len);
				return status;
			}
		}
	}

	/* prepare xfer_data struct */
	req_data.dev_addr = msg2->addr;
	req_data.direction = msg2->flags;
	req_data.saddr_len = msg1->len;
	req_data.saddr_dat = saddr;
	req_data.buf_size = msg2->len;
	req_data.p_buffer = msg2->buf;

	/* usb send command */
	status = dev->cx231xx_send_usb_command(bus, &req_data);

	return status < 0 ? status : 0;
}