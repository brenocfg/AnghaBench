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

/* Variables and functions */
 int ENOSPC ; 
 unsigned long bitmap_find_next_zero_area (unsigned long*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  bitmap_set (unsigned long*,unsigned long,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ppm_find_unused_entries(unsigned long *bmap,
				   unsigned int max_ppods,
				   unsigned int start,
				   unsigned int nr,
				   unsigned int align_mask)
{
	unsigned long i;

	i = bitmap_find_next_zero_area(bmap, max_ppods, start, nr, align_mask);

	if (unlikely(i >= max_ppods) && (start > nr))
		i = bitmap_find_next_zero_area(bmap, max_ppods, 0, start - 1,
					       align_mask);
	if (unlikely(i >= max_ppods))
		return -ENOSPC;

	bitmap_set(bmap, i, nr);
	return (int)i;
}