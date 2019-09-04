#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  unsigned char u32 ;
struct IR_i2c {TYPE_1__* rc; int /*<<< orphan*/  c; } ;
typedef  enum rc_proto { ____Placeholder_rc_proto } rc_proto ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int RC_PROTO_UNKNOWN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int i2c_master_recv (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int get_key_knc1(struct IR_i2c *ir, enum rc_proto *protocol,
			u32 *scancode, u8 *toggle)
{
	int rc;
	unsigned char b;

	/* poll IR chip */
	rc = i2c_master_recv(ir->c, &b, 1);
	if (rc != 1) {
		dev_dbg(&ir->rc->dev, "read error\n");
		if (rc < 0)
			return rc;
		return -EIO;
	}

	/* it seems that 0xFE indicates that a button is still hold
	   down, while 0xff indicates that no button is hold
	   down. 0xfe sequences are sometimes interrupted by 0xFF */

	dev_dbg(&ir->rc->dev, "key %02x\n", b);

	if (b == 0xff)
		return 0;

	if (b == 0xfe)
		/* keep old data */
		return 1;

	*protocol = RC_PROTO_UNKNOWN;
	*scancode = b;
	*toggle = 0;
	return 1;
}