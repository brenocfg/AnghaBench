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
typedef  int u8 ;
struct i2c_msg {int addr; int len; int* buf; scalar_t__ flags; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ I2C_M_RD ; 
 int /*<<< orphan*/  i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 

__attribute__((used)) static u8 i2c_readreg(struct i2c_adapter *i2c, u8 id, u8 reg)
{
	u8 mm1[] = { 0x00 };
	u8 mm2[] = { 0x00 };
	struct i2c_msg msgs[2];

	msgs[0].flags = 0;
	msgs[1].flags = I2C_M_RD;
	msgs[0].addr = msgs[1].addr = id / 2;
	mm1[0] = reg;
	msgs[0].len = 1;
	msgs[1].len = 1;
	msgs[0].buf = mm1;
	msgs[1].buf = mm2;

	i2c_transfer(i2c, msgs, 2);

	return mm2[0];
}