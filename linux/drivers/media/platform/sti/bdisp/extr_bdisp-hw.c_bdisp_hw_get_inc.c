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
typedef  int u16 ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int bdisp_hw_get_inc(u32 from, u32 to, u16 *inc)
{
	u32 tmp;

	if (!to)
		return -EINVAL;

	if (to == from) {
		*inc = 1 << 10;
		return 0;
	}

	tmp = (from << 10) / to;
	if ((tmp > 0xFFFF) || (!tmp))
		/* overflow (downscale x 63) or too small (upscale x 1024) */
		return -EINVAL;

	*inc = (u16)tmp;

	return 0;
}