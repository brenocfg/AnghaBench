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
struct i2c_msg {int len; int* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  I2C_LOCK_SEGMENT ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int __i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  i2c_lock_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_unlock_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int af9013_rregs(struct i2c_client *client, u8 cmd, u16 reg,
			u8 *val, int len, u8 lock)
{
	int ret;
	u8 buf[3];
	struct i2c_msg msg[2] = {
		{
			.addr = client->addr,
			.flags = 0,
			.len = 3,
			.buf = buf,
		}, {
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = len,
			.buf = val,
		}
	};

	buf[0] = (reg >> 8) & 0xff;
	buf[1] = (reg >> 0) & 0xff;
	buf[2] = cmd;

	if (lock)
		i2c_lock_bus(client->adapter, I2C_LOCK_SEGMENT);
	ret = __i2c_transfer(client->adapter, msg, 2);
	if (lock)
		i2c_unlock_bus(client->adapter, I2C_LOCK_SEGMENT);
	if (ret < 0) {
		goto err;
	} else if (ret != 2) {
		ret = -EREMOTEIO;
		goto err;
	}

	return 0;
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	return ret;
}