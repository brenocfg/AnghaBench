#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct reg_val {int dummy; } ;
struct pt3_adapter {TYPE_1__* i2c_demod; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EREMOTE ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int
pt3_demod_write(struct pt3_adapter *adap, const struct reg_val *data, int num)
{
	struct i2c_msg msg;
	int i, ret;

	ret = 0;
	msg.addr = adap->i2c_demod->addr;
	msg.flags = 0;
	msg.len = 2;
	for (i = 0; i < num; i++) {
		msg.buf = (u8 *)&data[i];
		ret = i2c_transfer(adap->i2c_demod->adapter, &msg, 1);
		if (ret == 0)
			ret = -EREMOTE;
		if (ret < 0)
			return ret;
	}
	return 0;
}