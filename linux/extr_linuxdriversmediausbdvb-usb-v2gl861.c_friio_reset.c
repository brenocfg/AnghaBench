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
struct dvb_usb_device {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const**) ; 
 int ENODEV ; 
 int gl861_i2c_msg (struct dvb_usb_device*,int,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int gl861_i2c_read_ex (struct dvb_usb_device*,int,int*,int) ; 
 int gl861_i2c_write_ex (struct dvb_usb_device*,int,int*,int) ; 
 int usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int friio_reset(struct dvb_usb_device *d)
{
	int i, ret;
	u8 wbuf[2], rbuf[2];

	static const u8 friio_init_cmds[][2] = {
		{0x33, 0x08}, {0x37, 0x40}, {0x3a, 0x1f}, {0x3b, 0xff},
		{0x3c, 0x1f}, {0x3d, 0xff}, {0x38, 0x00}, {0x35, 0x00},
		{0x39, 0x00}, {0x36, 0x00},
	};

	ret = usb_set_interface(d->udev, 0, 0);
	if (ret < 0)
		return ret;

	wbuf[0] = 0x11;
	wbuf[1] = 0x02;
	ret = gl861_i2c_msg(d, 0x00, wbuf, 2, NULL, 0);
	if (ret < 0)
		return ret;
	usleep_range(2000, 3000);

	wbuf[0] = 0x11;
	wbuf[1] = 0x00;
	ret = gl861_i2c_msg(d, 0x00, wbuf, 2, NULL, 0);
	if (ret < 0)
		return ret;

	/*
	 * Check if the dev is really a Friio White, since it might be
	 * another device, Friio Black, with the same VID/PID.
	 */

	usleep_range(1000, 2000);
	wbuf[0] = 0x03;
	wbuf[1] = 0x80;
	ret = gl861_i2c_write_ex(d, 0x09, wbuf, 2);
	if (ret < 0)
		return ret;

	usleep_range(2000, 3000);
	ret = gl861_i2c_read_ex(d, 0x09, rbuf, 2);
	if (ret < 0)
		return ret;
	if (rbuf[0] != 0xff || rbuf[1] != 0xff)
		return -ENODEV;


	usleep_range(1000, 2000);
	ret = gl861_i2c_write_ex(d, 0x48, wbuf, 2);
	if (ret < 0)
		return ret;

	usleep_range(2000, 3000);
	ret = gl861_i2c_read_ex(d, 0x48, rbuf, 2);
	if (ret < 0)
		return ret;
	if (rbuf[0] != 0xff || rbuf[1] != 0xff)
		return -ENODEV;

	wbuf[0] = 0x30;
	wbuf[1] = 0x04;
	ret = gl861_i2c_msg(d, 0x00, wbuf, 2, NULL, 0);
	if (ret < 0)
		return ret;

	wbuf[0] = 0x00;
	wbuf[1] = 0x01;
	ret = gl861_i2c_msg(d, 0x00, wbuf, 2, NULL, 0);
	if (ret < 0)
		return ret;

	wbuf[0] = 0x06;
	wbuf[1] = 0x0f;
	ret = gl861_i2c_msg(d, 0x00, wbuf, 2, NULL, 0);
	if (ret < 0)
		return ret;

	for (i = 0; i < ARRAY_SIZE(friio_init_cmds); i++) {
		ret = gl861_i2c_msg(d, 0x00, (u8 *)friio_init_cmds[i], 2,
				      NULL, 0);
		if (ret < 0)
			return ret;
	}
	return 0;
}