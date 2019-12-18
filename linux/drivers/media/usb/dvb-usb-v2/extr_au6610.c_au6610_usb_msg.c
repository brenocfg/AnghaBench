#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct dvb_usb_device {TYPE_1__* udev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  AU6610_REQ_I2C_READ 129 
#define  AU6610_REQ_USB_READ 128 
 int /*<<< orphan*/  AU6610_USB_TIMEOUT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int USB_DIR_IN ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dvb_usb_dbg_usb_control_msg (TYPE_1__*,int,int,int,int,int*,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int usb_control_msg (TYPE_1__*,int /*<<< orphan*/ ,int,int,int,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int au6610_usb_msg(struct dvb_usb_device *d, u8 operation, u8 addr,
			  u8 *wbuf, u16 wlen, u8 *rbuf, u16 rlen)
{
	int ret;
	u16 index;
	u8 *usb_buf;

	/*
	 * allocate enough for all known requests,
	 * read returns 5 and write 6 bytes
	 */
	usb_buf = kmalloc(6, GFP_KERNEL);
	if (!usb_buf)
		return -ENOMEM;

	switch (wlen) {
	case 1:
		index = wbuf[0] << 8;
		break;
	case 2:
		index = wbuf[0] << 8;
		index += wbuf[1];
		break;
	default:
		dev_err(&d->udev->dev, "%s: wlen=%d, aborting\n",
				KBUILD_MODNAME, wlen);
		ret = -EINVAL;
		goto error;
	}

	ret = usb_control_msg(d->udev, usb_rcvctrlpipe(d->udev, 0), operation,
			      USB_TYPE_VENDOR|USB_DIR_IN, addr << 1, index,
			      usb_buf, 6, AU6610_USB_TIMEOUT);

	dvb_usb_dbg_usb_control_msg(d->udev, operation,
			(USB_TYPE_VENDOR|USB_DIR_IN), addr << 1, index,
			usb_buf, 6);

	if (ret < 0)
		goto error;

	switch (operation) {
	case AU6610_REQ_I2C_READ:
	case AU6610_REQ_USB_READ:
		/* requested value is always 5th byte in buffer */
		rbuf[0] = usb_buf[4];
	}
error:
	kfree(usb_buf);
	return ret;
}