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
typedef  scalar_t__ u32 ;
struct dvb_usb_device {scalar_t__ last_event; int /*<<< orphan*/  data_mutex; struct cinergyt2_state* priv; } ;
struct cinergyt2_state {int* data; scalar_t__ rc_counter; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int CINERGYT2_EP1_GET_RC_EVENTS ; 
 scalar_t__ RC_REPEAT_DELAY ; 
 int REMOTE_KEY_REPEAT ; 
 int REMOTE_NO_KEY_PRESSED ; 
 int /*<<< orphan*/  deb_rc (char*,...) ; 
 int dvb_usb_generic_rw (struct dvb_usb_device*,int*,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_usb_nec_rc_key_to_event (struct dvb_usb_device*,int*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__* repeatable_keys ; 

__attribute__((used)) static int cinergyt2_rc_query(struct dvb_usb_device *d, u32 *event, int *state)
{
	struct cinergyt2_state *st = d->priv;
	int i, ret;

	*state = REMOTE_NO_KEY_PRESSED;

	mutex_lock(&d->data_mutex);
	st->data[0] = CINERGYT2_EP1_GET_RC_EVENTS;

	ret = dvb_usb_generic_rw(d, st->data, 1, st->data, 5, 0);
	if (ret < 0)
		goto ret;

	if (st->data[4] == 0xff) {
		/* key repeat */
		st->rc_counter++;
		if (st->rc_counter > RC_REPEAT_DELAY) {
			for (i = 0; i < ARRAY_SIZE(repeatable_keys); i++) {
				if (d->last_event == repeatable_keys[i]) {
					*state = REMOTE_KEY_REPEAT;
					*event = d->last_event;
					deb_rc("repeat key, event %x\n",
						   *event);
					goto ret;
				}
			}
			deb_rc("repeated key (non repeatable)\n");
		}
		goto ret;
	}

	/* hack to pass checksum on the custom field */
	st->data[2] = ~st->data[1];
	dvb_usb_nec_rc_key_to_event(d, st->data, event, state);
	if (st->data[0] != 0) {
		if (*event != d->last_event)
			st->rc_counter = 0;

		deb_rc("key: %*ph\n", 5, st->data);
	}

ret:
	mutex_unlock(&d->data_mutex);
	return ret;
}