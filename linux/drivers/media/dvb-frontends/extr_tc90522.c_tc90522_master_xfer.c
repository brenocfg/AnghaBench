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
typedef  int /*<<< orphan*/  wbuf ;
typedef  int u8 ;
struct tc90522_state {TYPE_1__* i2c_client; } ;
struct i2c_msg {int flags; int addr; int* buf; int len; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {int addr; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_M_RD ; 
 int TC90522_I2C_THRU_REG ; 
 struct tc90522_state* i2c_get_adapdata (struct i2c_adapter*) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  kfree (struct i2c_msg*) ; 
 struct i2c_msg* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static int
tc90522_master_xfer(struct i2c_adapter *adap, struct i2c_msg *msgs, int num)
{
	struct tc90522_state *state;
	struct i2c_msg *new_msgs;
	int i, j;
	int ret, rd_num;
	u8 wbuf[256];
	u8 *p, *bufend;

	if (num <= 0)
		return -EINVAL;

	rd_num = 0;
	for (i = 0; i < num; i++)
		if (msgs[i].flags & I2C_M_RD)
			rd_num++;
	new_msgs = kmalloc_array(num + rd_num, sizeof(*new_msgs), GFP_KERNEL);
	if (!new_msgs)
		return -ENOMEM;

	state = i2c_get_adapdata(adap);
	p = wbuf;
	bufend = wbuf + sizeof(wbuf);
	for (i = 0, j = 0; i < num; i++, j++) {
		new_msgs[j].addr = state->i2c_client->addr;
		new_msgs[j].flags = msgs[i].flags;

		if (msgs[i].flags & I2C_M_RD) {
			new_msgs[j].flags &= ~I2C_M_RD;
			if (p + 2 > bufend)
				break;
			p[0] = TC90522_I2C_THRU_REG;
			p[1] = msgs[i].addr << 1 | 0x01;
			new_msgs[j].buf = p;
			new_msgs[j].len = 2;
			p += 2;
			j++;
			new_msgs[j].addr = state->i2c_client->addr;
			new_msgs[j].flags = msgs[i].flags;
			new_msgs[j].buf = msgs[i].buf;
			new_msgs[j].len = msgs[i].len;
			continue;
		}

		if (p + msgs[i].len + 2 > bufend)
			break;
		p[0] = TC90522_I2C_THRU_REG;
		p[1] = msgs[i].addr << 1;
		memcpy(p + 2, msgs[i].buf, msgs[i].len);
		new_msgs[j].buf = p;
		new_msgs[j].len = msgs[i].len + 2;
		p += new_msgs[j].len;
	}

	if (i < num)
		ret = -ENOMEM;
	else
		ret = i2c_transfer(state->i2c_client->adapter, new_msgs, j);
	if (ret >= 0 && ret < j)
		ret = -EIO;
	kfree(new_msgs);
	return (ret == j) ? num : ret;
}