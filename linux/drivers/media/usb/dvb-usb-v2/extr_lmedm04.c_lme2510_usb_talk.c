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
struct lme2510_state {int /*<<< orphan*/ * usb_buffer; } ;
struct dvb_usb_device {int /*<<< orphan*/  usb_mutex; struct lme2510_state* priv; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int dvb_usbv2_generic_rw_locked (struct dvb_usb_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lme2510_usb_talk(struct dvb_usb_device *d,
			    u8 *wbuf, int wlen, u8 *rbuf, int rlen)
{
	struct lme2510_state *st = d->priv;
	int ret = 0;

	if (max(wlen, rlen) > sizeof(st->usb_buffer))
		return -EINVAL;

	ret = mutex_lock_interruptible(&d->usb_mutex);
	if (ret < 0)
		return -EAGAIN;

	memcpy(st->usb_buffer, wbuf, wlen);

	ret = dvb_usbv2_generic_rw_locked(d, st->usb_buffer, wlen,
					  st->usb_buffer, rlen);

	if (rlen)
		memcpy(rbuf, st->usb_buffer, rlen);

	mutex_unlock(&d->usb_mutex);

	return ret;
}