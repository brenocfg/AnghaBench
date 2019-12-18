#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  size_t u32 ;
struct trinity_ps {int num_levels; TYPE_1__* levels; } ;
struct radeon_device {int dummy; } ;
struct TYPE_2__ {int sclk; } ;

/* Variables and functions */

__attribute__((used)) static u8 trinity_calculate_display_wm(struct radeon_device *rdev,
				       struct trinity_ps *ps, u32 index)
{
	if (ps == NULL || ps->num_levels <= 1)
		return 0;
	else if (ps->num_levels == 2) {
		if (index == 0)
			return 0;
		else
			return 1;
	} else {
		if (index == 0)
			return 0;
		else if (ps->levels[index].sclk < 30000)
			return 0;
		else
			return 1;
	}
}