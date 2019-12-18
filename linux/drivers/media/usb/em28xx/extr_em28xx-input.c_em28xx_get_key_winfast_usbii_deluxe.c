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
struct i2c_msg {unsigned char* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
typedef  enum rc_proto { ____Placeholder_rc_proto } rc_proto ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int RC_PROTO_UNKNOWN ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int em28xx_get_key_winfast_usbii_deluxe(struct i2c_client *i2c_dev,
					       enum rc_proto *protocol,
					       u32 *scancode)
{
	unsigned char subaddr, keydetect, key;

	struct i2c_msg msg[] = {
		{
			.addr = i2c_dev->addr,
			.flags = 0,
			.buf = &subaddr, .len = 1
		}, {
			.addr = i2c_dev->addr,
			.flags = I2C_M_RD,
			.buf = &keydetect,
			.len = 1
		}
	};

	subaddr = 0x10;
	if (i2c_transfer(i2c_dev->adapter, msg, 2) != 2)
		return -EIO;
	if (keydetect == 0x00)
		return 0;

	subaddr = 0x00;
	msg[1].buf = &key;
	if (i2c_transfer(i2c_dev->adapter, msg, 2) != 2)
		return -EIO;
	if (key == 0x00)
		return 0;

	*protocol = RC_PROTO_UNKNOWN;
	*scancode = key;
	return 1;
}