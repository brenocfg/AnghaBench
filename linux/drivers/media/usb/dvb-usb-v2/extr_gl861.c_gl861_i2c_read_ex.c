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
typedef  scalar_t__ u16 ;
struct dvb_usb_device {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GL861_READ ; 
 int /*<<< orphan*/  GL861_REQ_I2C_READ ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,scalar_t__) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*,scalar_t__,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gl861_i2c_read_ex(struct dvb_usb_device *d, u8 addr, u8 *rbuf, u16 rlen)
{
	u8 *buf;
	int ret;

	buf = kmalloc(rlen, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	ret = usb_control_msg(d->udev, usb_rcvctrlpipe(d->udev, 0),
				 GL861_REQ_I2C_READ, GL861_READ,
				 addr << (8 + 1), 0x0100, buf, rlen, 2000);
	if (ret > 0 && rlen > 0)
		memcpy(buf, rbuf, rlen);
	kfree(buf);
	return ret;
}