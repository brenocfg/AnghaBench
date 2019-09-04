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
struct fixed_mtrr_segment {int end; int start; int range_shift; int range_start; } ;

/* Variables and functions */
 struct fixed_mtrr_segment* fixed_seg_table ; 

__attribute__((used)) static int fixed_mtrr_seg_end_range_index(int seg)
{
	struct fixed_mtrr_segment *mtrr_seg = &fixed_seg_table[seg];
	int n;

	n = (mtrr_seg->end - mtrr_seg->start) >> mtrr_seg->range_shift;
	return mtrr_seg->range_start + n - 1;
}