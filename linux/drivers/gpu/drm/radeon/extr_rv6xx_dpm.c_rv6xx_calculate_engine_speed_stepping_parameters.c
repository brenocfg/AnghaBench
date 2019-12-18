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
struct TYPE_7__ {int /*<<< orphan*/  sclk; } ;
struct TYPE_6__ {int /*<<< orphan*/  sclk; } ;
struct TYPE_5__ {int /*<<< orphan*/  sclk; } ;
struct rv6xx_ps {TYPE_3__ high; TYPE_2__ medium; TYPE_1__ low; } ;
struct TYPE_8__ {size_t low_sclk_index; size_t medium_sclk_index; size_t high_sclk_index; int /*<<< orphan*/ * sclks; } ;
struct rv6xx_power_info {TYPE_4__ hw; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 size_t R600_POWER_LEVEL_HIGH ; 
 size_t R600_POWER_LEVEL_LOW ; 
 size_t R600_POWER_LEVEL_MEDIUM ; 
 struct rv6xx_power_info* rv6xx_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void rv6xx_calculate_engine_speed_stepping_parameters(struct radeon_device *rdev,
							     struct rv6xx_ps *state)
{
	struct rv6xx_power_info *pi = rv6xx_get_pi(rdev);

	pi->hw.sclks[R600_POWER_LEVEL_LOW] =
		state->low.sclk;
	pi->hw.sclks[R600_POWER_LEVEL_MEDIUM] =
		state->medium.sclk;
	pi->hw.sclks[R600_POWER_LEVEL_HIGH] =
		state->high.sclk;

	pi->hw.low_sclk_index = R600_POWER_LEVEL_LOW;
	pi->hw.medium_sclk_index = R600_POWER_LEVEL_MEDIUM;
	pi->hw.high_sclk_index = R600_POWER_LEVEL_HIGH;
}