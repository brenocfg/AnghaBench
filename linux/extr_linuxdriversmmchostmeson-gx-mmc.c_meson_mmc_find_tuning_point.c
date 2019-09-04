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
 unsigned long CLK_PHASE_POINT_NUM ; 
 int EIO ; 
 scalar_t__ bitmap_empty (unsigned long*,unsigned long) ; 
 scalar_t__ bitmap_full (unsigned long*,unsigned long) ; 
 unsigned long find_first_zero_bit (unsigned long*,unsigned long) ; 
 int /*<<< orphan*/  meson_mmc_find_next_region (unsigned long*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  meson_mmc_shift_map (unsigned long*,unsigned long) ; 

__attribute__((used)) static int meson_mmc_find_tuning_point(unsigned long *test)
{
	unsigned long shift, stop, offset = 0, start = 0, size = 0;

	/* Get the all good/all bad situation out the way */
	if (bitmap_full(test, CLK_PHASE_POINT_NUM))
		return 0; /* All points are good so point 0 will do */
	else if (bitmap_empty(test, CLK_PHASE_POINT_NUM))
		return -EIO; /* No successful tuning point */

	/*
	 * Now we know there is a least one region find. Make sure it does
	 * not wrap by the shifting the bitmap if necessary
	 */
	shift = find_first_zero_bit(test, CLK_PHASE_POINT_NUM);
	if (shift != 0)
		meson_mmc_shift_map(test, shift);

	while (start < CLK_PHASE_POINT_NUM) {
		meson_mmc_find_next_region(test, &start, &stop);

		if ((stop - start) > size) {
			offset = start;
			size = stop - start;
		}

		start = stop;
	}

	/* Get the center point of the region */
	offset += (size / 2);

	/* Shift the result back */
	offset = (offset + shift) % CLK_PHASE_POINT_NUM;

	return offset;
}