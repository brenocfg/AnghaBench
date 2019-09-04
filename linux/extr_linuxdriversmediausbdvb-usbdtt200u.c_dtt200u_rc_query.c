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
typedef  int u32 ;
struct dvb_usb_device {int /*<<< orphan*/  data_mutex; int /*<<< orphan*/  rc_dev; struct dtt200u_state* priv; } ;
struct dtt200u_state {int* data; } ;
typedef  enum rc_proto { ____Placeholder_rc_proto } rc_proto ;

/* Variables and functions */
 int GET_RC_CODE ; 
 int RC_PROTO_NEC ; 
 int RC_PROTO_NECX ; 
 int /*<<< orphan*/  deb_info (char*,int,int*) ; 
 int dvb_usb_generic_rw (struct dvb_usb_device*,int*,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc_keydown (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_keyup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_repeat (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dtt200u_rc_query(struct dvb_usb_device *d)
{
	struct dtt200u_state *st = d->priv;
	u32 scancode;
	int ret;

	mutex_lock(&d->data_mutex);
	st->data[0] = GET_RC_CODE;

	ret = dvb_usb_generic_rw(d, st->data, 1, st->data, 5, 0);
	if (ret < 0)
		goto ret;

	if (st->data[0] == 1) {
		enum rc_proto proto = RC_PROTO_NEC;

		scancode = st->data[1];
		if ((u8) ~st->data[1] != st->data[2]) {
			/* Extended NEC */
			scancode = scancode << 8;
			scancode |= st->data[2];
			proto = RC_PROTO_NECX;
		}
		scancode = scancode << 8;
		scancode |= st->data[3];

		/* Check command checksum is ok */
		if ((u8) ~st->data[3] == st->data[4])
			rc_keydown(d->rc_dev, proto, scancode, 0);
		else
			rc_keyup(d->rc_dev);
	} else if (st->data[0] == 2) {
		rc_repeat(d->rc_dev);
	} else {
		rc_keyup(d->rc_dev);
	}

	if (st->data[0] != 0)
		deb_info("st->data: %*ph\n", 5, st->data);

ret:
	mutex_unlock(&d->data_mutex);
	return ret;
}