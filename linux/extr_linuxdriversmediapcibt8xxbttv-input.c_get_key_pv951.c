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
typedef  enum rc_proto { ____Placeholder_rc_proto } rc_proto ;

/* Variables and functions */
 int EIO ; 
 int RC_PROTO_UNKNOWN ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int i2c_master_recv (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int get_key_pv951(struct IR_i2c *ir, enum rc_proto *protocol,
			 u32 *scancode, u8 *toggle)
{
	int rc;
	unsigned char b;

	/* poll IR chip */
	rc = i2c_master_recv(ir->c, &b, 1);
	if (rc != 1) {
		dprintk("read error\n");
		if (rc < 0)
			return rc;
		return -EIO;
	}

	/* ignore 0xaa */
	if (b==0xaa)
		return 0;
	dprintk("key %02x\n", b);

	/*
	 * NOTE:
	 * lirc_i2c maps the pv951 code as:
	 *	addr = 0x61D6
	 *	cmd = bit_reverse (b)
	 * So, it seems that this device uses NEC extended
	 * I decided to not fix the table, due to two reasons:
	 *	1) Without the actual device, this is only a guess;
	 *	2) As the addr is not reported via I2C, nor can be changed,
	 *	   the device is bound to the vendor-provided RC.
	 */

	*protocol = RC_PROTO_UNKNOWN;
	*scancode = b;
	*toggle = 0;
	return 1;
}