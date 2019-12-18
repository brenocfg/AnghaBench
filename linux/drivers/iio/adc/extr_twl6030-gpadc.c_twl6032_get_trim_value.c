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
typedef  unsigned int u8 ;

/* Variables and functions */

__attribute__((used)) static int twl6032_get_trim_value(u8 *trim_regs, unsigned int reg0,
		unsigned int reg1, unsigned int mask0, unsigned int mask1,
		unsigned int shift0)
{
	int val;

	val = (trim_regs[reg0] & mask0) << shift0;
	val |= (trim_regs[reg1] & mask1) >> 1;
	if (trim_regs[reg1] & 0x01)
		val = -val;

	return val;
}