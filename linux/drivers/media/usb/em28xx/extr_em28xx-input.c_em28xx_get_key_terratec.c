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
typedef  unsigned char u32 ;
struct i2c_client {int dummy; } ;
typedef  enum rc_proto { ____Placeholder_rc_proto } rc_proto ;

/* Variables and functions */
 int EIO ; 
 int RC_PROTO_UNKNOWN ; 
 int i2c_master_recv (struct i2c_client*,unsigned char*,int) ; 

__attribute__((used)) static int em28xx_get_key_terratec(struct i2c_client *i2c_dev,
				   enum rc_proto *protocol, u32 *scancode)
{
	int rc;
	unsigned char b;

	/* poll IR chip */
	rc = i2c_master_recv(i2c_dev, &b, 1);
	if (rc != 1) {
		if (rc < 0)
			return rc;
		return -EIO;
	}

	/*
	 * it seems that 0xFE indicates that a button is still hold
	 * down, while 0xff indicates that no button is hold down.
	 */

	if (b == 0xff)
		return 0;

	if (b == 0xfe)
		/* keep old data */
		return 1;

	*protocol = RC_PROTO_UNKNOWN;
	*scancode = b;
	return 1;
}