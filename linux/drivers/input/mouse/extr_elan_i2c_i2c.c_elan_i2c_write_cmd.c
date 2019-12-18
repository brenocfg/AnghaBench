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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i2c_msg {int flags; int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  addr; } ;
struct i2c_client {int flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EIO ; 
 int I2C_M_TEN ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int elan_i2c_write_cmd(struct i2c_client *client, u16 reg, u16 cmd)
{
	__le16 buf[] = {
		cpu_to_le16(reg),
		cpu_to_le16(cmd),
	};
	struct i2c_msg msg = {
		.addr = client->addr,
		.flags = client->flags & I2C_M_TEN,
		.len = sizeof(buf),
		.buf = (u8 *)buf,
	};
	int ret;

	ret = i2c_transfer(client->adapter, &msg, 1);
	if (ret != 1) {
		if (ret >= 0)
			ret = -EIO;
		dev_err(&client->dev, "writing cmd (0x%04x) failed: %d\n",
			reg, ret);
		return ret;
	}

	return 0;
}