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
struct sp2 {struct i2c_client* client; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  addr; int /*<<< orphan*/  dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sp2_write_i2c(struct sp2 *s, u8 reg, u8 *buf, int len)
{
	int ret;
	u8 buffer[35];
	struct i2c_client *client = s->client;
	struct i2c_adapter *adap = client->adapter;
	struct i2c_msg msg = {
		.addr = client->addr,
		.flags = 0,
		.buf = &buffer[0],
		.len = len + 1
	};

	if ((len + 1) > sizeof(buffer)) {
		dev_err(&client->dev, "i2c wr reg=%02x: len=%d is too big!\n",
				reg, len);
		return -EINVAL;
	}

	buffer[0] = reg;
	memcpy(&buffer[1], buf, len);

	ret = i2c_transfer(adap, &msg, 1);

	if (ret != 1) {
		dev_err(&client->dev, "i2c write error, reg = 0x%02x, status = %d\n",
				reg, ret);
		if (ret < 0)
			return ret;
		else
			return -EIO;
	}

	dev_dbg(&s->client->dev, "addr=0x%04x, reg = 0x%02x, data = %*ph\n",
				client->addr, reg, len, buf);

	return 0;
}