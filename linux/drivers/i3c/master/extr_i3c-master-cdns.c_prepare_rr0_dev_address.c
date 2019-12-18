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

/* Variables and functions */
 int GENMASK (int,int) ; 
 int hweight8 (int) ; 

__attribute__((used)) static u32 prepare_rr0_dev_address(u32 addr)
{
	u32 ret = (addr << 1) & 0xff;

	/* RR0[7:1] = addr[6:0] */
	ret |= (addr & GENMASK(6, 0)) << 1;

	/* RR0[15:13] = addr[9:7] */
	ret |= (addr & GENMASK(9, 7)) << 6;

	/* RR0[0] = ~XOR(addr[6:0]) */
	if (!(hweight8(addr & 0x7f) & 1))
		ret |= 1;

	return ret;
}