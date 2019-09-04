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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 scalar_t__ __be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cpu_to_be64 (scalar_t__) ; 

void add_to_ctr(u8 *ctr_pos, unsigned int increment)
{
	__be64 *high_be = (__be64 *)ctr_pos;
	__be64 *low_be = high_be + 1;
	u64 orig_low = __be64_to_cpu(*low_be);
	u64 new_low = orig_low + (u64)increment;

	*low_be = __cpu_to_be64(new_low);
	if (new_low < orig_low)
		/* there was a carry from the low 8 bytes */
		*high_be = __cpu_to_be64(__be64_to_cpu(*high_be) + 1);
}