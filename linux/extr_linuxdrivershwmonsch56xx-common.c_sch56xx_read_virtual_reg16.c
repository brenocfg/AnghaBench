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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int sch56xx_read_virtual_reg (scalar_t__,scalar_t__) ; 

int sch56xx_read_virtual_reg16(u16 addr, u16 reg)
{
	int lsb, msb;

	/* Read LSB first, this will cause the matching MSB to be latched */
	lsb = sch56xx_read_virtual_reg(addr, reg);
	if (lsb < 0)
		return lsb;

	msb = sch56xx_read_virtual_reg(addr, reg + 1);
	if (msb < 0)
		return msb;

	return lsb | (msb << 8);
}