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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static bool valid_l4_mask(u32 mask)
{
	u16 hi, lo;

	/* Either the upper 16-bits (SPORT) OR the lower
	 * 16-bits (DPORT) can be set, but NOT BOTH.
	 */
	hi = (mask >> 16) & 0xFFFF;
	lo = mask & 0xFFFF;

	return hi && lo ? false : true;
}