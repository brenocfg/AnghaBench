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
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
struct cx231xx {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int read_eeprom(struct cx231xx *dev, struct i2c_client *client,
		       u8 *eedata, int len)
{
	int ret;
	u8 start_offset = 0;
	int len_todo = len;
	u8 *eedata_cur = eedata;
	int i;
	struct i2c_msg msg_write = { .addr = client->addr, .flags = 0,
		.buf = &start_offset, .len = 1 };
	struct i2c_msg msg_read = { .addr = client->addr, .flags = I2C_M_RD };

	/* start reading at offset 0 */
	ret = i2c_transfer(client->adapter, &msg_write, 1);
	if (ret < 0) {
		dev_err(dev->dev, "Can't read eeprom\n");
		return ret;
	}

	while (len_todo > 0) {
		msg_read.len = (len_todo > 64) ? 64 : len_todo;
		msg_read.buf = eedata_cur;

		ret = i2c_transfer(client->adapter, &msg_read, 1);
		if (ret < 0) {
			dev_err(dev->dev, "Can't read eeprom\n");
			return ret;
		}
		eedata_cur += msg_read.len;
		len_todo -= msg_read.len;
	}

	for (i = 0; i + 15 < len; i += 16)
		dev_dbg(dev->dev, "i2c eeprom %02x: %*ph\n",
			i, 16, &eedata[i]);

	return 0;
}