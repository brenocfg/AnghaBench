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
typedef  int /*<<< orphan*/  u16 ;
struct dvb_usb_device {int /*<<< orphan*/  usb_mutex; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int USB_DIR_IN ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  deb_xfer (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_dump (int /*<<< orphan*/ *,int,int /*<<< orphan*/  (*) (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int) ; 

__attribute__((used)) static int az6027_usb_in_op(struct dvb_usb_device *d, u8 req,
			    u16 value, u16 index, u8 *b, int blen)
{
	int ret = -1;
	if (mutex_lock_interruptible(&d->usb_mutex))
		return -EAGAIN;

	ret = usb_control_msg(d->udev,
			      usb_rcvctrlpipe(d->udev, 0),
			      req,
			      USB_TYPE_VENDOR | USB_DIR_IN,
			      value,
			      index,
			      b,
			      blen,
			      2000);

	if (ret < 0) {
		warn("usb in operation failed. (%d)", ret);
		ret = -EIO;
	} else
		ret = 0;

	deb_xfer("in: req. %02x, val: %04x, ind: %04x, buffer: ", req, value, index);
	debug_dump(b, blen, deb_xfer);

	mutex_unlock(&d->usb_mutex);
	return ret;
}