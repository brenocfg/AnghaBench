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
typedef  scalar_t__ u8 ;
struct i2c_msg {int len; scalar_t__* buf; scalar_t__ flags; scalar_t__ addr; } ;
struct i2c_client {scalar_t__ addr; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static int ps8622_set(struct i2c_client *client, u8 page, u8 reg, u8 val)
{
	int ret;
	struct i2c_adapter *adap = client->adapter;
	struct i2c_msg msg;
	u8 data[] = {reg, val};

	msg.addr = client->addr + page;
	msg.flags = 0;
	msg.len = sizeof(data);
	msg.buf = data;

	ret = i2c_transfer(adap, &msg, 1);
	if (ret != 1)
		pr_warn("PS8622 I2C write (0x%02x,0x%02x,0x%02x) failed: %d\n",
			client->addr + page, reg, val, ret);
	return !(ret == 1);
}