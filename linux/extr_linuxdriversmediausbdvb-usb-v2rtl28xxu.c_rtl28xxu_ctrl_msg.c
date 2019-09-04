#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct rtl28xxu_req {int size; int index; int /*<<< orphan*/  data; int /*<<< orphan*/  value; } ;
struct rtl28xxu_dev {int /*<<< orphan*/  buf; } ;
struct dvb_usb_device {TYPE_1__* intf; int /*<<< orphan*/  usb_mutex; int /*<<< orphan*/  udev; struct rtl28xxu_dev* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CMD_WR_FLAG ; 
 int EINVAL ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dvb_usb_dbg_usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 unsigned int usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl28xxu_ctrl_msg(struct dvb_usb_device *d, struct rtl28xxu_req *req)
{
	struct rtl28xxu_dev *dev = d->priv;
	int ret;
	unsigned int pipe;
	u8 requesttype;

	mutex_lock(&d->usb_mutex);

	if (req->size > sizeof(dev->buf)) {
		dev_err(&d->intf->dev, "too large message %u\n", req->size);
		ret = -EINVAL;
		goto err_mutex_unlock;
	}

	if (req->index & CMD_WR_FLAG) {
		/* write */
		memcpy(dev->buf, req->data, req->size);
		requesttype = (USB_TYPE_VENDOR | USB_DIR_OUT);
		pipe = usb_sndctrlpipe(d->udev, 0);
	} else {
		/* read */
		requesttype = (USB_TYPE_VENDOR | USB_DIR_IN);
		pipe = usb_rcvctrlpipe(d->udev, 0);
	}

	ret = usb_control_msg(d->udev, pipe, 0, requesttype, req->value,
			req->index, dev->buf, req->size, 1000);
	dvb_usb_dbg_usb_control_msg(d->udev, 0, requesttype, req->value,
			req->index, dev->buf, req->size);
	if (ret < 0)
		goto err_mutex_unlock;

	/* read request, copy returned data to return buf */
	if (requesttype == (USB_TYPE_VENDOR | USB_DIR_IN))
		memcpy(req->data, dev->buf, req->size);

	mutex_unlock(&d->usb_mutex);

	return 0;
err_mutex_unlock:
	mutex_unlock(&d->usb_mutex);
	dev_dbg(&d->intf->dev, "failed=%d\n", ret);
	return ret;
}