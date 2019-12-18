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
struct i2c_client {int flags; int addr; } ;

/* Variables and functions */
 int I2C_CLIENT_TEN ; 

__attribute__((used)) static bool stm32f7_i2c_is_addr_match(struct i2c_client *slave, u32 addcode)
{
	u32 addr;

	if (!slave)
		return false;

	if (slave->flags & I2C_CLIENT_TEN) {
		/*
		 * For 10-bit addr, addcode = 11110XY with
		 * X = Bit 9 of slave address
		 * Y = Bit 8 of slave address
		 */
		addr = slave->addr >> 8;
		addr |= 0x78;
		if (addr == addcode)
			return true;
	} else {
		addr = slave->addr & 0x7f;
		if (addr == addcode)
			return true;
	}

	return false;
}