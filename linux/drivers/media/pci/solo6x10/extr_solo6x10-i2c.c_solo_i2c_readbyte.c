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
typedef  void* u8 ;
struct solo_dev {int /*<<< orphan*/ * i2c_adap; } ;
struct i2c_msg {int len; void** buf; void* addr; scalar_t__ flags; } ;

/* Variables and functions */
 scalar_t__ I2C_M_RD ; 
 int /*<<< orphan*/  i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 

u8 solo_i2c_readbyte(struct solo_dev *solo_dev, int id, u8 addr, u8 off)
{
	struct i2c_msg msgs[2];
	u8 data;

	msgs[0].flags = 0;
	msgs[0].addr = addr;
	msgs[0].len = 1;
	msgs[0].buf = &off;

	msgs[1].flags = I2C_M_RD;
	msgs[1].addr = addr;
	msgs[1].len = 1;
	msgs[1].buf = &data;

	i2c_transfer(&solo_dev->i2c_adap[id], msgs, 2);

	return data;
}