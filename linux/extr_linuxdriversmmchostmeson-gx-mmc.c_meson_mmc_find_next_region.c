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
 int /*<<< orphan*/  CLK_PHASE_POINT_NUM ; 
 unsigned long find_next_bit (unsigned long*,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long find_next_zero_bit (unsigned long*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void meson_mmc_find_next_region(unsigned long *map,
				       unsigned long *start,
				       unsigned long *stop)
{
	*start = find_next_bit(map, CLK_PHASE_POINT_NUM, *start);
	*stop = find_next_zero_bit(map, CLK_PHASE_POINT_NUM, *start);
}