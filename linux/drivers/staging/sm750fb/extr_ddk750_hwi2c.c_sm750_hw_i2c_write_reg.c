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
 int hw_i2c_write_data (unsigned char,int,unsigned char*) ; 

int sm750_hw_i2c_write_reg(unsigned char addr,
			   unsigned char reg,
			   unsigned char data)
{
	unsigned char value[2];

	value[0] = reg;
	value[1] = data;
	if (hw_i2c_write_data(addr, 2, value) == 2)
		return 0;

	return -1;
}