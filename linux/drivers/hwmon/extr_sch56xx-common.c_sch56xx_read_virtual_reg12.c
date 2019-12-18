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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int sch56xx_read_virtual_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sch56xx_read_virtual_reg12(u16 addr, u16 msb_reg, u16 lsn_reg,
			       int high_nibble)
{
	int msb, lsn;

	/* Read MSB first, this will cause the matching LSN to be latched */
	msb = sch56xx_read_virtual_reg(addr, msb_reg);
	if (msb < 0)
		return msb;

	lsn = sch56xx_read_virtual_reg(addr, lsn_reg);
	if (lsn < 0)
		return lsn;

	if (high_nibble)
		return (msb << 4) | (lsn >> 4);
	else
		return (msb << 4) | (lsn & 0x0f);
}