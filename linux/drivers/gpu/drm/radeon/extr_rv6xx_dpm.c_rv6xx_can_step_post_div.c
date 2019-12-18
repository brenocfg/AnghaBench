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
struct rv6xx_sclk_stepping {int post_divider; int vco_frequency; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool rv6xx_can_step_post_div(struct radeon_device *rdev,
				    struct rv6xx_sclk_stepping *cur,
				    struct rv6xx_sclk_stepping *target)
{
	return (cur->post_divider > target->post_divider) &&
		((cur->vco_frequency * target->post_divider) <=
		 (target->vco_frequency * (cur->post_divider - 1)));
}