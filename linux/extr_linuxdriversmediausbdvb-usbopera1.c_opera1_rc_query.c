#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct opera1_state {scalar_t__ last_key_pressed; } ;
struct i2c_msg {int len; int /*<<< orphan*/  flags; scalar_t__* buf; int /*<<< orphan*/  addr; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_adap; struct opera1_state* priv; } ;
struct TYPE_4__ {int keycode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_B880_READ_REMOTE ; 
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int REMOTE_KEY_PRESSED ; 
 int REMOTE_KEY_REPEAT ; 
 int REMOTE_NO_KEY_PRESSED ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int rc5_scan (TYPE_1__*) ; 
 TYPE_1__* rc_map_opera1_table ; 

__attribute__((used)) static int opera1_rc_query(struct dvb_usb_device *dev, u32 * event, int *state)
{
	struct opera1_state *opst = dev->priv;
	u8 rcbuffer[32];
	const u16 startmarker1 = 0x10ed;
	const u16 startmarker2 = 0x11ec;
	struct i2c_msg read_remote[] = {
		{.addr = ADDR_B880_READ_REMOTE,.buf = rcbuffer,.flags = I2C_M_RD,.len = 32},
	};
	int i = 0;
	u32 send_key = 0;

	if (i2c_transfer(&dev->i2c_adap, read_remote, 1) == 1) {
		for (i = 0; i < 32; i++) {
			if (rcbuffer[i])
				send_key |= 1;
			if (i < 31)
				send_key = send_key << 1;
		}
		if (send_key & 0x8000)
			send_key = (send_key << 1) | (send_key >> 15 & 0x01);

		if (send_key == 0xffff && opst->last_key_pressed != 0) {
			*state = REMOTE_KEY_REPEAT;
			*event = opst->last_key_pressed;
			return 0;
		}
		for (; send_key != 0;) {
			if (send_key >> 16 == startmarker2) {
				break;
			} else if (send_key >> 16 == startmarker1) {
				send_key =
					(send_key & 0xfffeffff) | (startmarker1 << 16);
				break;
			} else
				send_key >>= 1;
		}

		if (send_key == 0)
			return 0;

		send_key = (send_key & 0xffff) | 0x0100;

		for (i = 0; i < ARRAY_SIZE(rc_map_opera1_table); i++) {
			if (rc5_scan(&rc_map_opera1_table[i]) == (send_key & 0xffff)) {
				*state = REMOTE_KEY_PRESSED;
				*event = rc_map_opera1_table[i].keycode;
				opst->last_key_pressed =
					rc_map_opera1_table[i].keycode;
				break;
			}
			opst->last_key_pressed = 0;
		}
	} else
		*state = REMOTE_NO_KEY_PRESSED;
	return 0;
}