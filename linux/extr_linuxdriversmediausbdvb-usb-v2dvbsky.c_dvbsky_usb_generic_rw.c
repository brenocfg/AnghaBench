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
typedef  scalar_t__ u16 ;
struct dvbsky_state {int /*<<< orphan*/ * ibuf; int /*<<< orphan*/ * obuf; } ;
struct dvb_usb_device {int /*<<< orphan*/  usb_mutex; } ;

/* Variables and functions */
 struct dvbsky_state* d_to_priv (struct dvb_usb_device*) ; 
 int dvb_usbv2_generic_rw_locked (struct dvb_usb_device*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dvbsky_usb_generic_rw(struct dvb_usb_device *d,
		u8 *wbuf, u16 wlen, u8 *rbuf, u16 rlen)
{
	int ret;
	struct dvbsky_state *state = d_to_priv(d);

	mutex_lock(&d->usb_mutex);
	if (wlen != 0)
		memcpy(state->obuf, wbuf, wlen);

	ret = dvb_usbv2_generic_rw_locked(d, state->obuf, wlen,
			state->ibuf, rlen);

	if (!ret && (rlen != 0))
		memcpy(rbuf, state->ibuf, rlen);

	mutex_unlock(&d->usb_mutex);
	return ret;
}