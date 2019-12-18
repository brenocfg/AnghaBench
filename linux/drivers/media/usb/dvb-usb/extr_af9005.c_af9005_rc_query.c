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
typedef  int /*<<< orphan*/  u32 ;
struct dvb_usb_device {int /*<<< orphan*/  data_mutex; int /*<<< orphan*/  last_event; struct af9005_device_state* priv; } ;
struct af9005_device_state {int* data; int /*<<< orphan*/  sequence; } ;

/* Variables and functions */
 int EIO ; 
 int REMOTE_KEY_REPEAT ; 
 int REMOTE_NO_KEY_PRESSED ; 
 int /*<<< orphan*/  deb_rc (char*,int,...) ; 
 int /*<<< orphan*/  debug_dump (int*,int,int /*<<< orphan*/  (*) (char*,int,int /*<<< orphan*/ )) ; 
 int dvb_usb_generic_rw (struct dvb_usb_device*,int*,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rc_decode (struct dvb_usb_device*,int*,int,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int af9005_rc_query(struct dvb_usb_device *d, u32 * event, int *state)
{
	struct af9005_device_state *st = d->priv;
	int ret, len;
	u8 seq;

	*state = REMOTE_NO_KEY_PRESSED;
	if (rc_decode == NULL) {
		/* it shouldn't never come here */
		return 0;
	}

	mutex_lock(&d->data_mutex);

	/* deb_info("rc_query\n"); */
	st->data[0] = 3;		/* rest of packet length low */
	st->data[1] = 0;		/* rest of packet length high */
	st->data[2] = 0x40;		/* read remote */
	st->data[3] = 1;		/* rest of packet length */
	st->data[4] = seq = st->sequence++;	/* sequence number */
	ret = dvb_usb_generic_rw(d, st->data, 5, st->data, 256, 0);
	if (ret) {
		err("rc query failed");
		goto ret;
	}
	if (st->data[2] != 0x41) {
		err("rc query bad header.");
		ret = -EIO;
		goto ret;
	} else if (st->data[4] != seq) {
		err("rc query bad sequence.");
		ret = -EIO;
		goto ret;
	}
	len = st->data[5];
	if (len > 246) {
		err("rc query invalid length");
		ret = -EIO;
		goto ret;
	}
	if (len > 0) {
		deb_rc("rc data (%d) ", len);
		debug_dump((st->data + 6), len, deb_rc);
		ret = rc_decode(d, &st->data[6], len, event, state);
		if (ret) {
			err("rc_decode failed");
			goto ret;
		} else {
			deb_rc("rc_decode state %x event %x\n", *state, *event);
			if (*state == REMOTE_KEY_REPEAT)
				*event = d->last_event;
		}
	}

ret:
	mutex_unlock(&d->data_mutex);
	return ret;
}