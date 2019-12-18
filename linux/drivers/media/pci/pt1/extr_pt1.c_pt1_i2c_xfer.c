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
typedef  int u32 ;
typedef  int u16 ;
struct pt1 {int dummy; } ;
struct i2c_msg {int flags; int len; int* buf; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int I2C_M_RD ; 
 struct pt1* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  pt1_i2c_begin (struct pt1*,int*) ; 
 int pt1_i2c_end (struct pt1*,int) ; 
 int /*<<< orphan*/  pt1_i2c_read_msg (struct pt1*,int,int*,struct i2c_msg*) ; 
 int /*<<< orphan*/  pt1_i2c_write_msg (struct pt1*,int,int*,struct i2c_msg*) ; 
 int pt1_read_reg (struct pt1*,int) ; 

__attribute__((used)) static int pt1_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg *msgs, int num)
{
	struct pt1 *pt1;
	int i;
	struct i2c_msg *msg, *next_msg;
	int addr, ret;
	u16 len;
	u32 word;

	pt1 = i2c_get_adapdata(adap);

	for (i = 0; i < num; i++) {
		msg = &msgs[i];
		if (msg->flags & I2C_M_RD)
			return -ENOTSUPP;

		if (i + 1 < num)
			next_msg = &msgs[i + 1];
		else
			next_msg = NULL;

		if (next_msg && next_msg->flags & I2C_M_RD) {
			i++;

			len = next_msg->len;
			if (len > 4)
				return -ENOTSUPP;

			pt1_i2c_begin(pt1, &addr);
			pt1_i2c_write_msg(pt1, addr, &addr, msg);
			pt1_i2c_read_msg(pt1, addr, &addr, next_msg);
			ret = pt1_i2c_end(pt1, addr);
			if (ret < 0)
				return ret;

			word = pt1_read_reg(pt1, 2);
			while (len--) {
				next_msg->buf[len] = word;
				word >>= 8;
			}
		} else {
			pt1_i2c_begin(pt1, &addr);
			pt1_i2c_write_msg(pt1, addr, &addr, msg);
			ret = pt1_i2c_end(pt1, addr);
			if (ret < 0)
				return ret;
		}
	}

	return num;
}