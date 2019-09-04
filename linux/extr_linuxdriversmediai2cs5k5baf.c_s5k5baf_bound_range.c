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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ S5K5BAF_WIN_WIDTH_MIN ; 

__attribute__((used)) static void s5k5baf_bound_range(u32 *start, u32 *len, u32 max)
{
	if (*len > max)
		*len = max;
	if (*start + *len > max)
		*start = max - *len;
	*start &= ~1;
	*len &= ~1;
	if (*len < S5K5BAF_WIN_WIDTH_MIN)
		*len = S5K5BAF_WIN_WIDTH_MIN;
}