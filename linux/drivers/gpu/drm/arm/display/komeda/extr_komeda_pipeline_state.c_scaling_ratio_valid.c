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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static bool scaling_ratio_valid(u32 size_in, u32 size_out,
				u32 max_upscaling, u32 max_downscaling)
{
	if (size_out > size_in * max_upscaling)
		return false;
	else if (size_in > size_out * max_downscaling)
		return false;
	return true;
}