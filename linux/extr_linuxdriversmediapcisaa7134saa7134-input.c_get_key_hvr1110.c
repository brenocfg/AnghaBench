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
struct IR_i2c {int /*<<< orphan*/  c; } ;
typedef  enum rc_proto { ____Placeholder_rc_proto } rc_proto ;

/* Variables and functions */
 int EIO ; 
 int RC_PROTO_RC5 ; 
 int /*<<< orphan*/  RC_SCANCODE_RC5 (unsigned char,unsigned char) ; 
 int i2c_master_recv (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  ir_dbg (struct IR_i2c*,char*) ; 

__attribute__((used)) static int get_key_hvr1110(struct IR_i2c *ir, enum rc_proto *protocol,
			   u32 *scancode, u8 *toggle)
{
	int rc;
	unsigned char buf[5];

	/* poll IR chip */
	rc = i2c_master_recv(ir->c, buf, 5);
	if (rc != 5) {
		ir_dbg(ir, "read error\n");
		if (rc < 0)
			return rc;
		return -EIO;
	}

	/* Check if some key were pressed */
	if (!(buf[0] & 0x80))
		return 0;

	/*
	 * buf[3] & 0x80 is always high.
	 * buf[3] & 0x40 is a parity bit. A repeat event is marked
	 * by preserving it into two separate readings
	 * buf[4] bits 0 and 1, and buf[1] and buf[2] are always
	 * zero.
	 *
	 * Note that the keymap which the hvr1110 uses is RC5.
	 *
	 * FIXME: start bits could maybe be used...?
	 */
	*protocol = RC_PROTO_RC5;
	*scancode = RC_SCANCODE_RC5(buf[3] & 0x1f, buf[4] >> 2);
	*toggle = !!(buf[3] & 0x40);
	return 1;
}