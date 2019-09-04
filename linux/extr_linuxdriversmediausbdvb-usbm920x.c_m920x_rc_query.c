#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int rc_map_size; TYPE_4__* rc_map_table; } ;
struct TYPE_6__ {TYPE_1__ legacy; } ;
struct TYPE_7__ {TYPE_2__ rc; } ;
struct dvb_usb_device {TYPE_3__ props; int /*<<< orphan*/  udev; } ;
struct TYPE_8__ {int /*<<< orphan*/  keycode; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  M9206_CORE ; 
 int /*<<< orphan*/  M9206_RC_KEY ; 
 int /*<<< orphan*/  M9206_RC_STATE ; 
 int REMOTE_NO_KEY_PRESSED ; 
 int /*<<< orphan*/  deb (char*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m920x_parse_rc_state (struct dvb_usb_device*,scalar_t__,int*) ; 
 int m920x_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ rc5_data (TYPE_4__*) ; 

__attribute__((used)) static int m920x_rc_query(struct dvb_usb_device *d, u32 *event, int *state)
{
	int i, ret = 0;
	u8 *rc_state;

	rc_state = kmalloc(2, GFP_KERNEL);
	if (!rc_state)
		return -ENOMEM;

	ret = m920x_read(d->udev, M9206_CORE, 0x0, M9206_RC_STATE,
			 rc_state, 1);
	if (ret != 0)
		goto out;

	ret = m920x_read(d->udev, M9206_CORE, 0x0, M9206_RC_KEY,
			 rc_state + 1, 1);
	if (ret != 0)
		goto out;

	m920x_parse_rc_state(d, rc_state[0], state);

	for (i = 0; i < d->props.rc.legacy.rc_map_size; i++)
		if (rc5_data(&d->props.rc.legacy.rc_map_table[i]) == rc_state[1]) {
			*event = d->props.rc.legacy.rc_map_table[i].keycode;
			goto out;
		}

	if (rc_state[1] != 0)
		deb("Unknown rc key %02x\n", rc_state[1]);

	*state = REMOTE_NO_KEY_PRESSED;

 out:
	kfree(rc_state);
	return ret;
}