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
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 

__attribute__((used)) static int i2c_readreg(struct i2c_adapter *i2c, u8 adr, u8 reg)
{
	u8 val;
	struct i2c_msg msg[] = {
		{ .addr = adr, .flags = 0, .buf = &reg, .len = 1 },
		{ .addr = adr, .flags = I2C_M_RD, .buf = &val, .len = 1 }
	};

	return (i2c_transfer(i2c, msg, 2) != 2) ? -EIO : val;
}