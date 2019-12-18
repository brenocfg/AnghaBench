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
typedef  int /*<<< orphan*/  u16 ;
struct dvb_usb_device {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GL861_REQ_I2C_RAW ; 
 int /*<<< orphan*/  GL861_WRITE ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmemdup (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gl861_i2c_write_ex(struct dvb_usb_device *d, u8 addr, u8 *wbuf, u16 wlen)
{
	u8 *buf;
	int ret;

	buf = kmemdup(wbuf, wlen, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	ret = usb_control_msg(d->udev, usb_sndctrlpipe(d->udev, 0),
				 GL861_REQ_I2C_RAW, GL861_WRITE,
				 addr << (8 + 1), 0x0100, buf, wlen, 2000);
	kfree(buf);
	return ret;
}