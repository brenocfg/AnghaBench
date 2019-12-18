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
typedef  int u8 ;
struct i2c_msg {int addr; int len; int* buf; scalar_t__ flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  adapter; int /*<<< orphan*/  is_active; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 scalar_t__ I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 TYPE_1__* via_i2c_par ; 

int viafb_i2c_readbytes(u8 adap, u8 slave_addr, u8 index, u8 *buff, int buff_len)
{
	int ret;
	u8 mm1[] = {0x00};
	struct i2c_msg msgs[2];

	if (!via_i2c_par[adap].is_active)
		return -ENODEV;
	msgs[0].flags = 0;
	msgs[1].flags = I2C_M_RD;
	msgs[0].addr = msgs[1].addr = slave_addr / 2;
	mm1[0] = index;
	msgs[0].len = 1; msgs[1].len = buff_len;
	msgs[0].buf = mm1; msgs[1].buf = buff;
	ret = i2c_transfer(&via_i2c_par[adap].adapter, msgs, 2);
	if (ret == 2)
		ret = 0;
	else if (ret >= 0)
		ret = -EIO;

	return ret;
}