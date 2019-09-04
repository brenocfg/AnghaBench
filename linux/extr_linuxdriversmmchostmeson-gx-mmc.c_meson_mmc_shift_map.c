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
 scalar_t__ CLK_PHASE_POINT_NUM ; 
 int /*<<< orphan*/  DECLARE_BITMAP (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bitmap_or (unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bitmap_shift_left (int /*<<< orphan*/ ,unsigned long*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bitmap_shift_right (int /*<<< orphan*/ ,unsigned long*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  left ; 
 int /*<<< orphan*/  right ; 

__attribute__((used)) static void meson_mmc_shift_map(unsigned long *map, unsigned long shift)
{
	DECLARE_BITMAP(left, CLK_PHASE_POINT_NUM);
	DECLARE_BITMAP(right, CLK_PHASE_POINT_NUM);

	/*
	 * shift the bitmap right and reintroduce the dropped bits on the left
	 * of the bitmap
	 */
	bitmap_shift_right(right, map, shift, CLK_PHASE_POINT_NUM);
	bitmap_shift_left(left, map, CLK_PHASE_POINT_NUM - shift,
			  CLK_PHASE_POINT_NUM);
	bitmap_or(map, left, right, CLK_PHASE_POINT_NUM);
}