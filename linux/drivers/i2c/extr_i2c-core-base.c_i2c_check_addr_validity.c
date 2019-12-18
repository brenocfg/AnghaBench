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

/* Variables and functions */
 int EINVAL ; 
 unsigned short I2C_CLIENT_TEN ; 

__attribute__((used)) static int i2c_check_addr_validity(unsigned int addr, unsigned short flags)
{
	if (flags & I2C_CLIENT_TEN) {
		/* 10-bit address, all values are valid */
		if (addr > 0x3ff)
			return -EINVAL;
	} else {
		/* 7-bit address, reject the general call address */
		if (addr == 0x00 || addr > 0x7f)
			return -EINVAL;
	}
	return 0;
}