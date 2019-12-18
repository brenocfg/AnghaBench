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

__attribute__((used)) static u32 reg_write(u32 old, u32 new, u32 rsvd)
{
	if (rsvd == 0x0000ffff) {
		old &= ~(new >> 16);
		old |= new & (new >> 16);
	} else {
		old &= ~rsvd;
		old |= new & rsvd;
	}

	return old;
}