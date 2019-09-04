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
struct dvb_usb_device {int /*<<< orphan*/  usb_mutex; int /*<<< orphan*/  udev; int /*<<< orphan*/ * priv; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  TH_COMMAND_IN ; 
 int /*<<< orphan*/  TH_COMMAND_OUT ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  deb_xfer (char*) ; 
 int /*<<< orphan*/  debug_dump (int /*<<< orphan*/ *,int,int /*<<< orphan*/  (*) (char*)) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vp7045_usb_op(struct dvb_usb_device *d, u8 cmd, u8 *out, int outlen, u8 *in, int inlen, int msec)
{
	int ret = 0;
	u8 *buf = d->priv;

	buf[0] = cmd;

	if (outlen > 19)
		outlen = 19;

	if (inlen > 11)
		inlen = 11;

	ret = mutex_lock_interruptible(&d->usb_mutex);
	if (ret)
		return ret;

	if (out != NULL && outlen > 0)
		memcpy(&buf[1], out, outlen);

	deb_xfer("out buffer: ");
	debug_dump(buf, outlen+1, deb_xfer);


	if (usb_control_msg(d->udev,
			usb_sndctrlpipe(d->udev,0),
			TH_COMMAND_OUT, USB_TYPE_VENDOR | USB_DIR_OUT, 0, 0,
			buf, 20, 2000) != 20) {
		err("USB control message 'out' went wrong.");
		ret = -EIO;
		goto unlock;
	}

	msleep(msec);

	if (usb_control_msg(d->udev,
			usb_rcvctrlpipe(d->udev,0),
			TH_COMMAND_IN, USB_TYPE_VENDOR | USB_DIR_IN, 0, 0,
			buf, 12, 2000) != 12) {
		err("USB control message 'in' went wrong.");
		ret = -EIO;
		goto unlock;
	}

	deb_xfer("in buffer: ");
	debug_dump(buf, 12, deb_xfer);

	if (in != NULL && inlen > 0)
		memcpy(in, &buf[1], inlen);

unlock:
	mutex_unlock(&d->usb_mutex);

	return ret;
}