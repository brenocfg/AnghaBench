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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;

/* Variables and functions */
 int FIELD_GET (int,int /*<<< orphan*/ ) ; 
 int OP_BR_ADDR_HI ; 
 int OP_BR_ADDR_LO ; 
 int __bf_shf (int) ; 

u16 br_get_offset(u64 instr)
{
	u16 addr_lo, addr_hi;

	addr_lo = FIELD_GET(OP_BR_ADDR_LO, instr);
	addr_hi = FIELD_GET(OP_BR_ADDR_HI, instr);

	return (addr_hi * ((OP_BR_ADDR_LO >> __bf_shf(OP_BR_ADDR_LO)) + 1)) |
		addr_lo;
}