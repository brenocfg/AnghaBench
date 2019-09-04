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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ generic_bulk_ctrl_endpoint; scalar_t__ generic_bulk_ctrl_endpoint_response; } ;
struct dvb_usb_device {int /*<<< orphan*/  usb_mutex; TYPE_1__ props; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  deb_xfer (char*) ; 
 int /*<<< orphan*/  debug_dump (int /*<<< orphan*/ *,int,int /*<<< orphan*/  (*) (char*)) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,scalar_t__) ; 

int dvb_usb_generic_rw(struct dvb_usb_device *d, u8 *wbuf, u16 wlen, u8 *rbuf,
	u16 rlen, int delay_ms)
{
	int actlen,ret = -ENOMEM;

	if (!d || wbuf == NULL || wlen == 0)
		return -EINVAL;

	if (d->props.generic_bulk_ctrl_endpoint == 0) {
		err("endpoint for generic control not specified.");
		return -EINVAL;
	}

	if ((ret = mutex_lock_interruptible(&d->usb_mutex)))
		return ret;

	deb_xfer(">>> ");
	debug_dump(wbuf,wlen,deb_xfer);

	ret = usb_bulk_msg(d->udev,usb_sndbulkpipe(d->udev,
			d->props.generic_bulk_ctrl_endpoint), wbuf,wlen,&actlen,
			2000);

	if (ret)
		err("bulk message failed: %d (%d/%d)",ret,wlen,actlen);
	else
		ret = actlen != wlen ? -1 : 0;

	/* an answer is expected, and no error before */
	if (!ret && rbuf && rlen) {
		if (delay_ms)
			msleep(delay_ms);

		ret = usb_bulk_msg(d->udev,usb_rcvbulkpipe(d->udev,
				d->props.generic_bulk_ctrl_endpoint_response ?
				d->props.generic_bulk_ctrl_endpoint_response :
				d->props.generic_bulk_ctrl_endpoint),rbuf,rlen,&actlen,
				2000);

		if (ret)
			err("recv bulk message failed: %d",ret);
		else {
			deb_xfer("<<< ");
			debug_dump(rbuf,actlen,deb_xfer);
		}
	}

	mutex_unlock(&d->usb_mutex);
	return ret;
}