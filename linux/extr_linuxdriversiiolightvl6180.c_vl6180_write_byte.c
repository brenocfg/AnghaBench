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
typedef  int u16 ;
struct i2c_msg {int len; int* buf; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct i2c_msg*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vl6180_write_byte(struct i2c_client *client, u16 cmd, u8 val)
{
	u8 buf[3];
	struct i2c_msg msgs[1] = {
		{ .addr = client->addr, .len = sizeof(buf), .buf = (u8 *) &buf } };
	int ret;

	buf[0] = cmd >> 8;
	buf[1] = cmd & 0xff;
	buf[2] = val;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	if (ret < 0) {
		dev_err(&client->dev, "failed writing register 0x%04x\n", cmd);
		return ret;
	}

	return 0;
}