#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  void* u16 ;
struct TYPE_10__ {scalar_t__ mclk; scalar_t__ sclk; scalar_t__ vddc; scalar_t__ vddci; int /*<<< orphan*/  flags; } ;
struct rv7xx_ps {int dc_compatible; TYPE_5__ high; TYPE_5__ medium; TYPE_5__ low; } ;
struct radeon_ps {int dummy; } ;
struct radeon_clock_and_voltage_limits {scalar_t__ mclk; scalar_t__ sclk; scalar_t__ vddc; scalar_t__ vddci; } ;
struct TYPE_7__ {scalar_t__ min_vddc_for_pcie_gen2; struct radeon_clock_and_voltage_limits max_clock_voltage_on_dc; int /*<<< orphan*/  vddc_dependency_on_dispclk; int /*<<< orphan*/  vddc_dependency_on_mclk; int /*<<< orphan*/  vddci_dependency_on_mclk; int /*<<< orphan*/  vddc_dependency_on_sclk; struct radeon_clock_and_voltage_limits max_clock_voltage_on_ac; } ;
struct TYPE_8__ {int new_active_crtc_count; int ac_power; TYPE_2__ dyn_state; } ;
struct TYPE_9__ {TYPE_3__ dpm; } ;
struct TYPE_6__ {scalar_t__ current_dispclk; } ;
struct radeon_device {TYPE_4__ pm; TYPE_1__ clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_PPLIB_R600_FLAGS_PCIEGEN2 ; 
 int /*<<< orphan*/  btc_adjust_clock_combinations (struct radeon_device*,struct radeon_clock_and_voltage_limits*,TYPE_5__*) ; 
 int /*<<< orphan*/  btc_apply_voltage_delta_rules (struct radeon_device*,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  btc_apply_voltage_dependency_rules (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__ btc_dpm_vblank_too_short (struct radeon_device*) ; 
 int /*<<< orphan*/  btc_skip_blacklist_clocks (struct radeon_device*,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 
 struct rv7xx_ps* rv770_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static void btc_apply_state_adjust_rules(struct radeon_device *rdev,
					 struct radeon_ps *rps)
{
	struct rv7xx_ps *ps = rv770_get_ps(rps);
	struct radeon_clock_and_voltage_limits *max_limits;
	bool disable_mclk_switching;
	u32 mclk, sclk;
	u16 vddc, vddci;

	if ((rdev->pm.dpm.new_active_crtc_count > 1) ||
	    btc_dpm_vblank_too_short(rdev))
		disable_mclk_switching = true;
	else
		disable_mclk_switching = false;

	if (rdev->pm.dpm.ac_power)
		max_limits = &rdev->pm.dpm.dyn_state.max_clock_voltage_on_ac;
	else
		max_limits = &rdev->pm.dpm.dyn_state.max_clock_voltage_on_dc;

	if (rdev->pm.dpm.ac_power == false) {
		if (ps->high.mclk > max_limits->mclk)
			ps->high.mclk = max_limits->mclk;
		if (ps->high.sclk > max_limits->sclk)
			ps->high.sclk = max_limits->sclk;
		if (ps->high.vddc > max_limits->vddc)
			ps->high.vddc = max_limits->vddc;
		if (ps->high.vddci > max_limits->vddci)
			ps->high.vddci = max_limits->vddci;

		if (ps->medium.mclk > max_limits->mclk)
			ps->medium.mclk = max_limits->mclk;
		if (ps->medium.sclk > max_limits->sclk)
			ps->medium.sclk = max_limits->sclk;
		if (ps->medium.vddc > max_limits->vddc)
			ps->medium.vddc = max_limits->vddc;
		if (ps->medium.vddci > max_limits->vddci)
			ps->medium.vddci = max_limits->vddci;

		if (ps->low.mclk > max_limits->mclk)
			ps->low.mclk = max_limits->mclk;
		if (ps->low.sclk > max_limits->sclk)
			ps->low.sclk = max_limits->sclk;
		if (ps->low.vddc > max_limits->vddc)
			ps->low.vddc = max_limits->vddc;
		if (ps->low.vddci > max_limits->vddci)
			ps->low.vddci = max_limits->vddci;
	}

	/* XXX validate the min clocks required for display */

	if (disable_mclk_switching) {
		sclk = ps->low.sclk;
		mclk = ps->high.mclk;
		vddc = ps->low.vddc;
		vddci = ps->high.vddci;
	} else {
		sclk = ps->low.sclk;
		mclk = ps->low.mclk;
		vddc = ps->low.vddc;
		vddci = ps->low.vddci;
	}

	/* adjusted low state */
	ps->low.sclk = sclk;
	ps->low.mclk = mclk;
	ps->low.vddc = vddc;
	ps->low.vddci = vddci;

	btc_skip_blacklist_clocks(rdev, max_limits->sclk, max_limits->mclk,
				  &ps->low.sclk, &ps->low.mclk);

	/* adjusted medium, high states */
	if (ps->medium.sclk < ps->low.sclk)
		ps->medium.sclk = ps->low.sclk;
	if (ps->medium.vddc < ps->low.vddc)
		ps->medium.vddc = ps->low.vddc;
	if (ps->high.sclk < ps->medium.sclk)
		ps->high.sclk = ps->medium.sclk;
	if (ps->high.vddc < ps->medium.vddc)
		ps->high.vddc = ps->medium.vddc;

	if (disable_mclk_switching) {
		mclk = ps->low.mclk;
		if (mclk < ps->medium.mclk)
			mclk = ps->medium.mclk;
		if (mclk < ps->high.mclk)
			mclk = ps->high.mclk;
		ps->low.mclk = mclk;
		ps->low.vddci = vddci;
		ps->medium.mclk = mclk;
		ps->medium.vddci = vddci;
		ps->high.mclk = mclk;
		ps->high.vddci = vddci;
	} else {
		if (ps->medium.mclk < ps->low.mclk)
			ps->medium.mclk = ps->low.mclk;
		if (ps->medium.vddci < ps->low.vddci)
			ps->medium.vddci = ps->low.vddci;
		if (ps->high.mclk < ps->medium.mclk)
			ps->high.mclk = ps->medium.mclk;
		if (ps->high.vddci < ps->medium.vddci)
			ps->high.vddci = ps->medium.vddci;
	}

	btc_skip_blacklist_clocks(rdev, max_limits->sclk, max_limits->mclk,
				  &ps->medium.sclk, &ps->medium.mclk);
	btc_skip_blacklist_clocks(rdev, max_limits->sclk, max_limits->mclk,
				  &ps->high.sclk, &ps->high.mclk);

	btc_adjust_clock_combinations(rdev, max_limits, &ps->low);
	btc_adjust_clock_combinations(rdev, max_limits, &ps->medium);
	btc_adjust_clock_combinations(rdev, max_limits, &ps->high);

	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk,
					   ps->low.sclk, max_limits->vddc, &ps->low.vddc);
	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddci_dependency_on_mclk,
					   ps->low.mclk, max_limits->vddci, &ps->low.vddci);
	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_mclk,
					   ps->low.mclk, max_limits->vddc, &ps->low.vddc);
	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk,
					   rdev->clock.current_dispclk, max_limits->vddc, &ps->low.vddc);

	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk,
					   ps->medium.sclk, max_limits->vddc, &ps->medium.vddc);
	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddci_dependency_on_mclk,
					   ps->medium.mclk, max_limits->vddci, &ps->medium.vddci);
	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_mclk,
					   ps->medium.mclk, max_limits->vddc, &ps->medium.vddc);
	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk,
					   rdev->clock.current_dispclk, max_limits->vddc, &ps->medium.vddc);

	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk,
					   ps->high.sclk, max_limits->vddc, &ps->high.vddc);
	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddci_dependency_on_mclk,
					   ps->high.mclk, max_limits->vddci, &ps->high.vddci);
	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_mclk,
					   ps->high.mclk, max_limits->vddc, &ps->high.vddc);
	btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk,
					   rdev->clock.current_dispclk, max_limits->vddc, &ps->high.vddc);

	btc_apply_voltage_delta_rules(rdev, max_limits->vddc, max_limits->vddci,
				      &ps->low.vddc, &ps->low.vddci);
	btc_apply_voltage_delta_rules(rdev, max_limits->vddc, max_limits->vddci,
				      &ps->medium.vddc, &ps->medium.vddci);
	btc_apply_voltage_delta_rules(rdev, max_limits->vddc, max_limits->vddci,
				      &ps->high.vddc, &ps->high.vddci);

	if ((ps->high.vddc <= rdev->pm.dpm.dyn_state.max_clock_voltage_on_dc.vddc) &&
	    (ps->medium.vddc <= rdev->pm.dpm.dyn_state.max_clock_voltage_on_dc.vddc) &&
	    (ps->low.vddc <= rdev->pm.dpm.dyn_state.max_clock_voltage_on_dc.vddc))
		ps->dc_compatible = true;
	else
		ps->dc_compatible = false;

	if (ps->low.vddc < rdev->pm.dpm.dyn_state.min_vddc_for_pcie_gen2)
		ps->low.flags &= ~ATOM_PPLIB_R600_FLAGS_PCIEGEN2;
	if (ps->medium.vddc < rdev->pm.dpm.dyn_state.min_vddc_for_pcie_gen2)
		ps->medium.flags &= ~ATOM_PPLIB_R600_FLAGS_PCIEGEN2;
	if (ps->high.vddc < rdev->pm.dpm.dyn_state.min_vddc_for_pcie_gen2)
		ps->high.flags &= ~ATOM_PPLIB_R600_FLAGS_PCIEGEN2;
}