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
struct fixed_mtrr_segment {scalar_t__ start; scalar_t__ end; int range_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int fixed_mtrr_seg_unit_size (int) ; 
 struct fixed_mtrr_segment* fixed_seg_table ; 

__attribute__((used)) static int fixed_mtrr_seg_unit_range_index(int seg, int unit)
{
	struct fixed_mtrr_segment *mtrr_seg = &fixed_seg_table[seg];

	WARN_ON(mtrr_seg->start + unit * fixed_mtrr_seg_unit_size(seg)
		> mtrr_seg->end);

	/* each unit has 8 ranges. */
	return mtrr_seg->range_start + 8 * unit;
}