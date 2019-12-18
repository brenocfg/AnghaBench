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
struct TYPE_8__ {int* rp; scalar_t__* lp; } ;
struct rv6xx_power_info {TYPE_4__ hw; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R600_AH_DFLT ; 
 int /*<<< orphan*/  R600_LHP_DFLT ; 
 int /*<<< orphan*/  R600_LMP_DFLT ; 
 int R600_PM_NUMBER_OF_ACTIVITY_LEVELS ; 
 int /*<<< orphan*/  R600_RLP_DFLT ; 
 int /*<<< orphan*/  R600_RMP_DFLT ; 
 int /*<<< orphan*/  rv6xx_calculate_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 struct rv6xx_power_info* rv6xx_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void rv6xx_calculate_ap(struct radeon_device *rdev,
			       struct rv6xx_ps *state)
{
	struct rv6xx_power_info *pi = rv6xx_get_pi(rdev);

	pi->hw.lp[0] = 0;
	pi->hw.rp[R600_PM_NUMBER_OF_ACTIVITY_LEVELS - 1]
		= 100;

	rv6xx_calculate_t(state->low.sclk,
			  state->medium.sclk,
			  R600_AH_DFLT,
			  R600_LMP_DFLT,
			  R600_RLP_DFLT,
			  &pi->hw.lp[1],
			  &pi->hw.rp[0]);

	rv6xx_calculate_t(state->medium.sclk,
			  state->high.sclk,
			  R600_AH_DFLT,
			  R600_LHP_DFLT,
			  R600_RMP_DFLT,
			  &pi->hw.lp[2],
			  &pi->hw.rp[1]);

}