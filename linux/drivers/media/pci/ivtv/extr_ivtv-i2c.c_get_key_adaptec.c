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
typedef  scalar_t__ u8 ;
typedef  unsigned char u32 ;
struct IR_i2c {int /*<<< orphan*/  c; } ;
typedef  int /*<<< orphan*/  keybuf ;
typedef  enum rc_proto { ____Placeholder_rc_proto } rc_proto ;

/* Variables and functions */
 int RC_PROTO_UNKNOWN ; 
 int i2c_master_recv (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  i2c_master_send (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int get_key_adaptec(struct IR_i2c *ir, enum rc_proto *protocol,
			   u32 *scancode, u8 *toggle)
{
	unsigned char keybuf[4];

	keybuf[0] = 0x00;
	i2c_master_send(ir->c, keybuf, 1);
	/* poll IR chip */
	if (i2c_master_recv(ir->c, keybuf, sizeof(keybuf)) != sizeof(keybuf)) {
		return 0;
	}

	/* key pressed ? */
	if (keybuf[2] == 0xff)
		return 0;

	/* remove repeat bit */
	keybuf[2] &= 0x7f;
	keybuf[3] |= 0x80;

	*protocol = RC_PROTO_UNKNOWN;
	*scancode = keybuf[3] | keybuf[2] << 8 | keybuf[1] << 16 |keybuf[0] << 24;
	*toggle = 0;
	return 1;
}