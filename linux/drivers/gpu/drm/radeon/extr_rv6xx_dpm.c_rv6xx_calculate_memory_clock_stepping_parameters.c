#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ mclk; } ;
struct TYPE_6__ {scalar_t__ mclk; } ;
struct TYPE_5__ {scalar_t__ mclk; } ;
struct rv6xx_ps {TYPE_3__ low; TYPE_2__ medium; TYPE_1__ high; } ;
struct TYPE_8__ {scalar_t__* mclks; size_t high_mclk_index; size_t medium_mclk_index; size_t low_mclk_index; } ;
struct rv6xx_power_info {TYPE_4__ hw; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 size_t R600_POWER_LEVEL_CTXSW ; 
 size_t R600_POWER_LEVEL_HIGH ; 
 size_t R600_POWER_LEVEL_LOW ; 
 size_t R600_POWER_LEVEL_MEDIUM ; 
 struct rv6xx_power_info* rv6xx_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void rv6xx_calculate_memory_clock_stepping_parameters(struct radeon_device *rdev,
							     struct rv6xx_ps *state)
{
	struct rv6xx_power_info *pi = rv6xx_get_pi(rdev);

	pi->hw.mclks[R600_POWER_LEVEL_CTXSW] =
		state->high.mclk;
	pi->hw.mclks[R600_POWER_LEVEL_HIGH] =
		state->high.mclk;
	pi->hw.mclks[R600_POWER_LEVEL_MEDIUM] =
		state->medium.mclk;
	pi->hw.mclks[R600_POWER_LEVEL_LOW] =
		state->low.mclk;

	pi->hw.high_mclk_index = R600_POWER_LEVEL_HIGH;

	if (state->high.mclk == state->medium.mclk)
		pi->hw.medium_mclk_index =
			pi->hw.high_mclk_index;
	else
		pi->hw.medium_mclk_index = R600_POWER_LEVEL_MEDIUM;


	if (state->medium.mclk == state->low.mclk)
		pi->hw.low_mclk_index =
			pi->hw.medium_mclk_index;
	else
		pi->hw.low_mclk_index = R600_POWER_LEVEL_LOW;
}