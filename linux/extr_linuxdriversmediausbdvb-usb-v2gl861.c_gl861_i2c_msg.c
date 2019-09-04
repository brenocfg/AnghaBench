#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct dvb_usb_device {TYPE_1__* udev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GL861_READ ; 
 int GL861_REQ_I2C_READ ; 
 int GL861_REQ_I2C_WRITE ; 
 int GL861_WRITE ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int* kmemdup (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int usb_control_msg (TYPE_1__*,int /*<<< orphan*/ ,int,int,int,int,int*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int gl861_i2c_msg(struct dvb_usb_device *d, u8 addr,
			 u8 *wbuf, u16 wlen, u8 *rbuf, u16 rlen)
{
	u16 index;
	u16 value = addr << (8 + 1);
	int wo = (rbuf == NULL || rlen == 0); /* write-only */
	u8 req, type;
	u8 *buf;
	int ret;

	if (wo) {
		req = GL861_REQ_I2C_WRITE;
		type = GL861_WRITE;
		buf = kmemdup(wbuf, wlen, GFP_KERNEL);
	} else { /* rw */
		req = GL861_REQ_I2C_READ;
		type = GL861_READ;
		buf = kmalloc(rlen, GFP_KERNEL);
	}
	if (!buf)
		return -ENOMEM;

	switch (wlen) {
	case 1:
		index = wbuf[0];
		break;
	case 2:
		index = wbuf[0];
		value = value + wbuf[1];
		break;
	default:
		dev_err(&d->udev->dev, "%s: wlen=%d, aborting\n",
				KBUILD_MODNAME, wlen);
		kfree(buf);
		return -EINVAL;
	}

	usleep_range(1000, 2000); /* avoid I2C errors */

	ret = usb_control_msg(d->udev, usb_rcvctrlpipe(d->udev, 0), req, type,
			      value, index, buf, rlen, 2000);

	if (!wo && ret > 0)
		memcpy(rbuf, buf, rlen);

	kfree(buf);
	return ret;
}