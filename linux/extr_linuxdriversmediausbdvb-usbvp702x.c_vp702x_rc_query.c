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
typedef  int /*<<< orphan*/  u32 ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int vp702x_rc_query(struct dvb_usb_device *d, u32 *event, int *state)
{
/* remove the following return to enabled remote querying */
#if 0
	u8 *key;
	int i;

	key = kmalloc(10, GFP_KERNEL);
	if (!key)
		return -ENOMEM;

	vp702x_usb_in_op(d,READ_REMOTE_REQ,0,0,key,10);

	deb_rc("remote query key: %x %d\n",key[1],key[1]);

	if (key[1] == 0x44) {
		*state = REMOTE_NO_KEY_PRESSED;
		kfree(key);
		return 0;
	}

	for (i = 0; i < ARRAY_SIZE(rc_map_vp702x_table); i++)
		if (rc5_custom(&rc_map_vp702x_table[i]) == key[1]) {
			*state = REMOTE_KEY_PRESSED;
			*event = rc_map_vp702x_table[i].keycode;
			break;
		}
	kfree(key);
#endif

	return 0;
}