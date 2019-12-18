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
typedef  int u32 ;
struct IR_i2c {int /*<<< orphan*/  c; } ;
typedef  enum rc_proto { ____Placeholder_rc_proto } rc_proto ;

/* Variables and functions */
 int RC_PROTO_UNKNOWN ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_key_pvr2000(struct IR_i2c *ir, enum rc_proto *protocol,
			   u32 *scancode, u8 *toggle)
{
	int flags, code;

	/* poll IR chip */
	flags = i2c_smbus_read_byte_data(ir->c, 0x10);
	if (flags < 0) {
		dprintk("read error\n");
		return 0;
	}
	/* key pressed ? */
	if (0 == (flags & 0x80))
		return 0;

	/* read actual key code */
	code = i2c_smbus_read_byte_data(ir->c, 0x00);
	if (code < 0) {
		dprintk("read error\n");
		return 0;
	}

	dprintk("IR Key/Flags: (0x%02x/0x%02x)\n",
		code & 0xff, flags & 0xff);

	*protocol = RC_PROTO_UNKNOWN;
	*scancode = code & 0xff;
	*toggle = 0;
	return 1;
}