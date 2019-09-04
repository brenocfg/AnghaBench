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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  fixed_msr_to_seg_unit (int /*<<< orphan*/ ,int*,int*) ; 
 int fixed_mtrr_seg_unit_range_index (int,int) ; 

__attribute__((used)) static int fixed_msr_to_range_index(u32 msr)
{
	int seg, unit;

	if (!fixed_msr_to_seg_unit(msr, &seg, &unit))
		return -1;

	return fixed_mtrr_seg_unit_range_index(seg, unit);
}