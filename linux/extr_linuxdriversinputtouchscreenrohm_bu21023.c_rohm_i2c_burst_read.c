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
struct i2c_msg {int len; int /*<<< orphan*/ * buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  addr; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  I2C_LOCK_SEGMENT ; 
 scalar_t__ I2C_M_RD ; 
 scalar_t__ __i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  i2c_lock_bus (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_unlock_bus (struct i2c_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rohm_i2c_burst_read(struct i2c_client *client, u8 start, void *buf,
			       size_t len)
{
	struct i2c_adapter *adap = client->adapter;
	struct i2c_msg msg[2];
	int i, ret = 0;

	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].len = 1;
	msg[0].buf = &start;

	msg[1].addr = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len = len;
	msg[1].buf = buf;

	i2c_lock_bus(adap, I2C_LOCK_SEGMENT);

	for (i = 0; i < 2; i++) {
		if (__i2c_transfer(adap, &msg[i], 1) < 0) {
			ret = -EIO;
			break;
		}
	}

	i2c_unlock_bus(adap, I2C_LOCK_SEGMENT);

	return ret;
}