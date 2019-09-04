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
struct rv6xx_sclk_stepping {int post_divider; int vco_frequency; } ;
struct radeon_device {int dummy; } ;
struct atom_clock_dividers {int post_div; scalar_t__ enable_post_div; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPUTE_ENGINE_PLL_PARAM ; 
 int radeon_atom_get_clock_dividers (struct radeon_device*,int /*<<< orphan*/ ,int,int,struct atom_clock_dividers*) ; 

__attribute__((used)) static int rv6xx_convert_clock_to_stepping(struct radeon_device *rdev,
					   u32 clock, struct rv6xx_sclk_stepping *step)
{
	int ret;
	struct atom_clock_dividers dividers;

	ret = radeon_atom_get_clock_dividers(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     clock, false, &dividers);
	if (ret)
		return ret;

	if (dividers.enable_post_div)
		step->post_divider = 2 + (dividers.post_div & 0xF) + (dividers.post_div >> 4);
	else
		step->post_divider = 1;

	step->vco_frequency = clock * step->post_divider;

	return 0;
}