#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct usb_req {int cmd; int* data; int /*<<< orphan*/  data_len; int /*<<< orphan*/  index; int /*<<< orphan*/  value; } ;
struct dvb_usb_device {TYPE_1__* udev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE6230_USB_TIMEOUT ; 
#define  DEMOD_READ 133 
#define  DEMOD_WRITE 132 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  I2C_READ 131 
#define  I2C_WRITE 130 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
#define  REG_READ 129 
#define  REG_WRITE 128 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dvb_usb_dbg_usb_control_msg (TYPE_1__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int usb_control_msg (TYPE_1__*,unsigned int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int usb_rcvctrlpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndctrlpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ce6230_ctrl_msg(struct dvb_usb_device *d, struct usb_req *req)
{
	int ret;
	unsigned int pipe;
	u8 request;
	u8 requesttype;
	u16 value;
	u16 index;
	u8 *buf;

	request = req->cmd;
	value = req->value;
	index = req->index;

	switch (req->cmd) {
	case I2C_READ:
	case DEMOD_READ:
	case REG_READ:
		requesttype = (USB_TYPE_VENDOR | USB_DIR_IN);
		break;
	case I2C_WRITE:
	case DEMOD_WRITE:
	case REG_WRITE:
		requesttype = (USB_TYPE_VENDOR | USB_DIR_OUT);
		break;
	default:
		dev_err(&d->udev->dev, "%s: unknown command=%02x\n",
				KBUILD_MODNAME, req->cmd);
		ret = -EINVAL;
		goto error;
	}

	buf = kmalloc(req->data_len, GFP_KERNEL);
	if (!buf) {
		ret = -ENOMEM;
		goto error;
	}

	if (requesttype == (USB_TYPE_VENDOR | USB_DIR_OUT)) {
		/* write */
		memcpy(buf, req->data, req->data_len);
		pipe = usb_sndctrlpipe(d->udev, 0);
	} else {
		/* read */
		pipe = usb_rcvctrlpipe(d->udev, 0);
	}

	msleep(1); /* avoid I2C errors */

	ret = usb_control_msg(d->udev, pipe, request, requesttype, value, index,
			buf, req->data_len, CE6230_USB_TIMEOUT);

	dvb_usb_dbg_usb_control_msg(d->udev, request, requesttype, value, index,
			buf, req->data_len);

	if (ret < 0)
		dev_err(&d->udev->dev, "%s: usb_control_msg() failed=%d\n",
				KBUILD_MODNAME, ret);
	else
		ret = 0;

	/* read request, copy returned data to return buf */
	if (!ret && requesttype == (USB_TYPE_VENDOR | USB_DIR_IN))
		memcpy(req->data, buf, req->data_len);

	kfree(buf);
error:
	return ret;
}