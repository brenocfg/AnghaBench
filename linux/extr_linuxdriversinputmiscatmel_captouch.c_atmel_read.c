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
typedef  size_t u8 ;
struct i2c_msg {size_t* buf; int len; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; struct device dev; } ;
struct atmel_captouch_device {size_t* xfer_buf; struct i2c_client* client; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct i2c_msg*) ; 
 int ECOMM ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ I2C_M_RD ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,size_t,size_t) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,size_t) ; 

__attribute__((used)) static int atmel_read(struct atmel_captouch_device *capdev,
			 u8 reg, u8 *data, size_t len)
{
	struct i2c_client *client = capdev->client;
	struct device *dev = &client->dev;
	struct i2c_msg msg[2];
	int err;

	if (len > sizeof(capdev->xfer_buf) - 2)
		return -EINVAL;

	capdev->xfer_buf[0] = reg;
	capdev->xfer_buf[1] = len;

	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].buf = capdev->xfer_buf;
	msg[0].len = 2;

	msg[1].addr = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].buf = capdev->xfer_buf;
	msg[1].len = len + 2;

	err = i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg));
	if (err != ARRAY_SIZE(msg))
		return err < 0 ? err : -EIO;

	if (capdev->xfer_buf[0] != reg) {
		dev_err(dev,
			"I2C read error: register address does not match (%#02x vs %02x)\n",
			capdev->xfer_buf[0], reg);
		return -ECOMM;
	}

	memcpy(data, &capdev->xfer_buf[2], len);

	return 0;
}