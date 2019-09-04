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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  fixed_msr_to_seg_unit (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  fixed_mtrr_seg_unit_range (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool fixed_msr_to_range(u32 msr, u64 *start, u64 *end)
{
	int seg, unit;

	if (!fixed_msr_to_seg_unit(msr, &seg, &unit))
		return false;

	fixed_mtrr_seg_unit_range(seg, unit, start, end);
	return true;
}