#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ mclk; scalar_t__ vddc; } ;
struct si_ulv_param {TYPE_3__ pl; } ;
struct si_power_info {struct si_ulv_param ulv; } ;
struct radeon_ps {scalar_t__ vclk; scalar_t__ dclk; } ;
struct TYPE_13__ {int count; TYPE_4__* entries; } ;
struct TYPE_14__ {TYPE_5__ vddc_dependency_on_dispclk; } ;
struct TYPE_15__ {TYPE_6__ dyn_state; } ;
struct TYPE_16__ {TYPE_7__ dpm; } ;
struct TYPE_10__ {scalar_t__ current_dispclk; } ;
struct radeon_device {TYPE_8__ pm; TYPE_2__ clock; } ;
struct ni_ps {TYPE_1__* performance_levels; } ;
struct TYPE_12__ {scalar_t__ clk; scalar_t__ v; } ;
struct TYPE_9__ {scalar_t__ mclk; } ;

/* Variables and functions */
 struct ni_ps* ni_get_ps (struct radeon_ps*) ; 
 struct si_power_info* si_get_pi (struct radeon_device*) ; 

__attribute__((used)) static bool si_is_state_ulv_compatible(struct radeon_device *rdev,
				       struct radeon_ps *radeon_state)
{
	const struct si_power_info *si_pi = si_get_pi(rdev);
	const struct si_ulv_param *ulv = &si_pi->ulv;
	const struct ni_ps *state = ni_get_ps(radeon_state);
	int i;

	if (state->performance_levels[0].mclk != ulv->pl.mclk)
		return false;

	/* XXX validate against display requirements! */

	for (i = 0; i < rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.count; i++) {
		if (rdev->clock.current_dispclk <=
		    rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[i].clk) {
			if (ulv->pl.vddc <
			    rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[i].v)
				return false;
		}
	}

	if ((radeon_state->vclk != 0) || (radeon_state->dclk != 0))
		return false;

	return true;
}