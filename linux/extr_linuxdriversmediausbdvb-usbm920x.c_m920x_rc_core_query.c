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
struct dvb_usb_device {int /*<<< orphan*/  rc_dev; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  M9206_CORE ; 
 int /*<<< orphan*/  M9206_RC_KEY ; 
 int /*<<< orphan*/  M9206_RC_STATE ; 
 int /*<<< orphan*/  RC_PROTO_UNKNOWN ; 
 int REMOTE_KEY_REPEAT ; 
 int REMOTE_NO_KEY_PRESSED ; 
 int /*<<< orphan*/  deb (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m920x_parse_rc_state (struct dvb_usb_device*,int /*<<< orphan*/ ,int*) ; 
 int m920x_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rc_keydown (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_keyup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_repeat (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m920x_rc_core_query(struct dvb_usb_device *d)
{
	int ret = 0;
	u8 *rc_state;
	int state;

	rc_state = kmalloc(2, GFP_KERNEL);
	if (!rc_state)
		return -ENOMEM;

	if ((ret = m920x_read(d->udev, M9206_CORE, 0x0, M9206_RC_STATE, &rc_state[0], 1)) != 0)
		goto out;

	if ((ret = m920x_read(d->udev, M9206_CORE, 0x0, M9206_RC_KEY, &rc_state[1], 1)) != 0)
		goto out;

	deb("state=0x%02x keycode=0x%02x\n", rc_state[0], rc_state[1]);

	m920x_parse_rc_state(d, rc_state[0], &state);

	if (state == REMOTE_NO_KEY_PRESSED)
		rc_keyup(d->rc_dev);
	else if (state == REMOTE_KEY_REPEAT)
		rc_repeat(d->rc_dev);
	else
		rc_keydown(d->rc_dev, RC_PROTO_UNKNOWN, rc_state[1], 0);

out:
	kfree(rc_state);
	return ret;
}