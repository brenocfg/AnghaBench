#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct radeon_ps {scalar_t__ vce_active; scalar_t__ dclk; scalar_t__ vclk; scalar_t__ ecclk; scalar_t__ evclk; } ;
struct radeon_clock_and_voltage_limits {int mclk; int sclk; scalar_t__ vddc; scalar_t__ vddci; } ;
struct TYPE_11__ {struct radeon_clock_and_voltage_limits max_clock_voltage_on_dc; int /*<<< orphan*/  vddc_dependency_on_dispclk; int /*<<< orphan*/  vddc_dependency_on_mclk; int /*<<< orphan*/  vddci_dependency_on_mclk; int /*<<< orphan*/  vddc_dependency_on_sclk; struct radeon_clock_and_voltage_limits max_clock_voltage_on_ac; } ;
struct TYPE_12__ {size_t vce_level; int new_active_crtc_count; int ac_power; TYPE_4__ dyn_state; TYPE_2__* vce_states; } ;
struct TYPE_13__ {TYPE_5__ dpm; } ;
struct TYPE_10__ {int current_dispclk; } ;
struct radeon_device {scalar_t__ family; TYPE_6__ pm; TYPE_3__ clock; TYPE_1__* pdev; } ;
struct ni_ps {int performance_level_count; int dc_compatible; TYPE_7__* performance_levels; } ;
struct TYPE_14__ {scalar_t__ vddc; int mclk; int sclk; scalar_t__ vddci; } ;
struct TYPE_9__ {int sclk; int mclk; scalar_t__ ecclk; scalar_t__ evclk; } ;
struct TYPE_8__ {int revision; int device; } ;

/* Variables and functions */
 scalar_t__ CHIP_HAINAN ; 
 scalar_t__ CHIP_OLAND ; 
 int /*<<< orphan*/  btc_adjust_clock_combinations (struct radeon_device*,struct radeon_clock_and_voltage_limits*,TYPE_7__*) ; 
 int /*<<< orphan*/  btc_apply_voltage_delta_rules (struct radeon_device*,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  btc_apply_voltage_dependency_rules (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  btc_get_max_clock_from_voltage_dependency_table (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ ni_dpm_vblank_too_short (struct radeon_device*) ; 
 struct ni_ps* ni_get_ps (struct radeon_ps*) ; 
 int /*<<< orphan*/  si_get_vce_clock_voltage (struct radeon_device*,scalar_t__,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static void si_apply_state_adjust_rules(struct radeon_device *rdev,
					struct radeon_ps *rps)
{
	struct ni_ps *ps = ni_get_ps(rps);
	struct radeon_clock_and_voltage_limits *max_limits;
	bool disable_mclk_switching = false;
	bool disable_sclk_switching = false;
	u32 mclk, sclk;
	u16 vddc, vddci, min_vce_voltage = 0;
	u32 max_sclk_vddc, max_mclk_vddci, max_mclk_vddc;
	u32 max_sclk = 0, max_mclk = 0;
	int i;

	if (rdev->family == CHIP_HAINAN) {
		if ((rdev->pdev->revision == 0x81) ||
		    (rdev->pdev->revision == 0x83) ||
		    (rdev->pdev->revision == 0xC3) ||
		    (rdev->pdev->device == 0x6664) ||
		    (rdev->pdev->device == 0x6665) ||
		    (rdev->pdev->device == 0x6667)) {
			max_sclk = 75000;
		}
		if ((rdev->pdev->revision == 0xC3) ||
		    (rdev->pdev->device == 0x6665)) {
			max_sclk = 60000;
			max_mclk = 80000;
		}
	} else if (rdev->family == CHIP_OLAND) {
		if ((rdev->pdev->revision == 0xC7) ||
		    (rdev->pdev->revision == 0x80) ||
		    (rdev->pdev->revision == 0x81) ||
		    (rdev->pdev->revision == 0x83) ||
		    (rdev->pdev->revision == 0x87) ||
		    (rdev->pdev->device == 0x6604) ||
		    (rdev->pdev->device == 0x6605)) {
			max_sclk = 75000;
		}
	}

	if (rps->vce_active) {
		rps->evclk = rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].evclk;
		rps->ecclk = rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].ecclk;
		si_get_vce_clock_voltage(rdev, rps->evclk, rps->ecclk,
					 &min_vce_voltage);
	} else {
		rps->evclk = 0;
		rps->ecclk = 0;
	}

	if ((rdev->pm.dpm.new_active_crtc_count > 1) ||
	    ni_dpm_vblank_too_short(rdev))
		disable_mclk_switching = true;

	if (rps->vclk || rps->dclk) {
		disable_mclk_switching = true;
		disable_sclk_switching = true;
	}

	if (rdev->pm.dpm.ac_power)
		max_limits = &rdev->pm.dpm.dyn_state.max_clock_voltage_on_ac;
	else
		max_limits = &rdev->pm.dpm.dyn_state.max_clock_voltage_on_dc;

	for (i = ps->performance_level_count - 2; i >= 0; i--) {
		if (ps->performance_levels[i].vddc > ps->performance_levels[i+1].vddc)
			ps->performance_levels[i].vddc = ps->performance_levels[i+1].vddc;
	}
	if (rdev->pm.dpm.ac_power == false) {
		for (i = 0; i < ps->performance_level_count; i++) {
			if (ps->performance_levels[i].mclk > max_limits->mclk)
				ps->performance_levels[i].mclk = max_limits->mclk;
			if (ps->performance_levels[i].sclk > max_limits->sclk)
				ps->performance_levels[i].sclk = max_limits->sclk;
			if (ps->performance_levels[i].vddc > max_limits->vddc)
				ps->performance_levels[i].vddc = max_limits->vddc;
			if (ps->performance_levels[i].vddci > max_limits->vddci)
				ps->performance_levels[i].vddci = max_limits->vddci;
		}
	}

	/* limit clocks to max supported clocks based on voltage dependency tables */
	btc_get_max_clock_from_voltage_dependency_table(&rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk,
							&max_sclk_vddc);
	btc_get_max_clock_from_voltage_dependency_table(&rdev->pm.dpm.dyn_state.vddci_dependency_on_mclk,
							&max_mclk_vddci);
	btc_get_max_clock_from_voltage_dependency_table(&rdev->pm.dpm.dyn_state.vddc_dependency_on_mclk,
							&max_mclk_vddc);

	for (i = 0; i < ps->performance_level_count; i++) {
		if (max_sclk_vddc) {
			if (ps->performance_levels[i].sclk > max_sclk_vddc)
				ps->performance_levels[i].sclk = max_sclk_vddc;
		}
		if (max_mclk_vddci) {
			if (ps->performance_levels[i].mclk > max_mclk_vddci)
				ps->performance_levels[i].mclk = max_mclk_vddci;
		}
		if (max_mclk_vddc) {
			if (ps->performance_levels[i].mclk > max_mclk_vddc)
				ps->performance_levels[i].mclk = max_mclk_vddc;
		}
		if (max_mclk) {
			if (ps->performance_levels[i].mclk > max_mclk)
				ps->performance_levels[i].mclk = max_mclk;
		}
		if (max_sclk) {
			if (ps->performance_levels[i].sclk > max_sclk)
				ps->performance_levels[i].sclk = max_sclk;
		}
	}

	/* XXX validate the min clocks required for display */

	if (disable_mclk_switching) {
		mclk  = ps->performance_levels[ps->performance_level_count - 1].mclk;
		vddci = ps->performance_levels[ps->performance_level_count - 1].vddci;
	} else {
		mclk = ps->performance_levels[0].mclk;
		vddci = ps->performance_levels[0].vddci;
	}

	if (disable_sclk_switching) {
		sclk = ps->performance_levels[ps->performance_level_count - 1].sclk;
		vddc = ps->performance_levels[ps->performance_level_count - 1].vddc;
	} else {
		sclk = ps->performance_levels[0].sclk;
		vddc = ps->performance_levels[0].vddc;
	}

	if (rps->vce_active) {
		if (sclk < rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].sclk)
			sclk = rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].sclk;
		if (mclk < rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].mclk)
			mclk = rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].mclk;
	}

	/* adjusted low state */
	ps->performance_levels[0].sclk = sclk;
	ps->performance_levels[0].mclk = mclk;
	ps->performance_levels[0].vddc = vddc;
	ps->performance_levels[0].vddci = vddci;

	if (disable_sclk_switching) {
		sclk = ps->performance_levels[0].sclk;
		for (i = 1; i < ps->performance_level_count; i++) {
			if (sclk < ps->performance_levels[i].sclk)
				sclk = ps->performance_levels[i].sclk;
		}
		for (i = 0; i < ps->performance_level_count; i++) {
			ps->performance_levels[i].sclk = sclk;
			ps->performance_levels[i].vddc = vddc;
		}
	} else {
		for (i = 1; i < ps->performance_level_count; i++) {
			if (ps->performance_levels[i].sclk < ps->performance_levels[i - 1].sclk)
				ps->performance_levels[i].sclk = ps->performance_levels[i - 1].sclk;
			if (ps->performance_levels[i].vddc < ps->performance_levels[i - 1].vddc)
				ps->performance_levels[i].vddc = ps->performance_levels[i - 1].vddc;
		}
	}

	if (disable_mclk_switching) {
		mclk = ps->performance_levels[0].mclk;
		for (i = 1; i < ps->performance_level_count; i++) {
			if (mclk < ps->performance_levels[i].mclk)
				mclk = ps->performance_levels[i].mclk;
		}
		for (i = 0; i < ps->performance_level_count; i++) {
			ps->performance_levels[i].mclk = mclk;
			ps->performance_levels[i].vddci = vddci;
		}
	} else {
		for (i = 1; i < ps->performance_level_count; i++) {
			if (ps->performance_levels[i].mclk < ps->performance_levels[i - 1].mclk)
				ps->performance_levels[i].mclk = ps->performance_levels[i - 1].mclk;
			if (ps->performance_levels[i].vddci < ps->performance_levels[i - 1].vddci)
				ps->performance_levels[i].vddci = ps->performance_levels[i - 1].vddci;
		}
	}

	for (i = 0; i < ps->performance_level_count; i++)
		btc_adjust_clock_combinations(rdev, max_limits,
					      &ps->performance_levels[i]);

	for (i = 0; i < ps->performance_level_count; i++) {
		if (ps->performance_levels[i].vddc < min_vce_voltage)
			ps->performance_levels[i].vddc = min_vce_voltage;
		btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk,
						   ps->performance_levels[i].sclk,
						   max_limits->vddc,  &ps->performance_levels[i].vddc);
		btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddci_dependency_on_mclk,
						   ps->performance_levels[i].mclk,
						   max_limits->vddci, &ps->performance_levels[i].vddci);
		btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_mclk,
						   ps->performance_levels[i].mclk,
						   max_limits->vddc,  &ps->performance_levels[i].vddc);
		btc_apply_voltage_dependency_rules(&rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk,
						   rdev->clock.current_dispclk,
						   max_limits->vddc,  &ps->performance_levels[i].vddc);
	}

	for (i = 0; i < ps->performance_level_count; i++) {
		btc_apply_voltage_delta_rules(rdev,
					      max_limits->vddc, max_limits->vddci,
					      &ps->performance_levels[i].vddc,
					      &ps->performance_levels[i].vddci);
	}

	ps->dc_compatible = true;
	for (i = 0; i < ps->performance_level_count; i++) {
		if (ps->performance_levels[i].vddc > rdev->pm.dpm.dyn_state.max_clock_voltage_on_dc.vddc)
			ps->dc_compatible = false;
	}
}