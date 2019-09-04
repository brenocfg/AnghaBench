#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct dvb_usb_device {struct dibusb_device_state* priv; } ;
struct dibusb_device_state {int old_toggle; int /*<<< orphan*/  last_repeat_count; } ;
struct TYPE_5__ {int /*<<< orphan*/  keycode; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
#define  DIBUSB_RC_HAUPPAUGE_KEY_EMPTY 129 
#define  DIBUSB_RC_HAUPPAUGE_KEY_PRESSED 128 
 int DIBUSB_REQ_POLL_REMOTE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int REMOTE_KEY_PRESSED ; 
 int REMOTE_NO_KEY_PRESSED ; 
 int /*<<< orphan*/  deb_rc (char*,int,int,...) ; 
 int dvb_usb_generic_rw (struct dvb_usb_device*,int*,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int rc5_custom (TYPE_1__*) ; 
 int rc5_data (TYPE_1__*) ; 
 TYPE_1__* rc_map_haupp_table ; 

__attribute__((used)) static int nova_t_rc_query(struct dvb_usb_device *d, u32 *event, int *state)
{
	u8 *buf, data, toggle, custom;
	u16 raw;
	int i, ret;
	struct dibusb_device_state *st = d->priv;

	buf = kmalloc(5, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	buf[0] = DIBUSB_REQ_POLL_REMOTE;
	buf[1] = 0x35;
	ret = dvb_usb_generic_rw(d, buf, 2, buf, 5, 0);
	if (ret < 0)
		goto ret;

	*state = REMOTE_NO_KEY_PRESSED;
	switch (buf[0]) {
		case DIBUSB_RC_HAUPPAUGE_KEY_PRESSED:
			raw = ((buf[1] << 8) | buf[2]) >> 3;
			toggle = !!(raw & 0x800);
			data = raw & 0x3f;
			custom = (raw >> 6) & 0x1f;

			deb_rc("raw key code 0x%02x, 0x%02x, 0x%02x to c: %02x d: %02x toggle: %d\n",
			       buf[1], buf[2], buf[3], custom, data, toggle);

			for (i = 0; i < ARRAY_SIZE(rc_map_haupp_table); i++) {
				if (rc5_data(&rc_map_haupp_table[i]) == data &&
					rc5_custom(&rc_map_haupp_table[i]) == custom) {

					deb_rc("c: %x, d: %x\n", rc5_data(&rc_map_haupp_table[i]),
								 rc5_custom(&rc_map_haupp_table[i]));

					*event = rc_map_haupp_table[i].keycode;
					*state = REMOTE_KEY_PRESSED;
					if (st->old_toggle == toggle) {
						if (st->last_repeat_count++ < 2)
							*state = REMOTE_NO_KEY_PRESSED;
					} else {
						st->last_repeat_count = 0;
						st->old_toggle = toggle;
					}
					break;
				}
			}

			break;
		case DIBUSB_RC_HAUPPAUGE_KEY_EMPTY:
		default:
			break;
	}

ret:
	kfree(buf);
	return ret;
}