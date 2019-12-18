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
 int DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static int drm_calc_scale(int src, int dst)
{
	int scale = 0;

	if (WARN_ON(src < 0 || dst < 0))
		return -EINVAL;

	if (dst == 0)
		return 0;

	if (src > (dst << 16))
		return DIV_ROUND_UP(src, dst);
	else
		scale = src / dst;

	return scale;
}