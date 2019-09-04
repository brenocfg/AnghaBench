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
 int RECEIVE_OBJECT_BITS ; 
 int fls (int) ; 
 int hweight32 (int) ; 

__attribute__((used)) static u32 c_can_adjust_pending(u32 pend)
{
	u32 weight, lasts;

	if (pend == RECEIVE_OBJECT_BITS)
		return pend;

	/*
	 * If the last set bit is larger than the number of pending
	 * bits we have a gap.
	 */
	weight = hweight32(pend);
	lasts = fls(pend);

	/* If the bits are linear, nothing to do */
	if (lasts == weight)
		return pend;

	/*
	 * Find the first set bit after the gap. We walk backwards
	 * from the last set bit.
	 */
	for (lasts--; pend & (1 << (lasts - 1)); lasts--);

	return pend & ~((1 << lasts) - 1);
}