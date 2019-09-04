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
typedef  scalar_t__ u32 ;
struct sumo_sclk_voltage_mapping_table {TYPE_1__* entries; } ;
struct radeon_ps {int class; scalar_t__ ecclk; scalar_t__ evclk; scalar_t__ vclk; scalar_t__ dclk; scalar_t__ vce_active; } ;
struct radeon_clock_and_voltage_limits {scalar_t__ mclk; int sclk; } ;
struct radeon_clock_voltage_dependency_table {int count; TYPE_6__* entries; } ;
struct TYPE_10__ {struct radeon_clock_and_voltage_limits max_clock_voltage_on_ac; struct radeon_clock_voltage_dependency_table vddc_dependency_on_sclk; } ;
struct TYPE_12__ {size_t vce_level; int new_active_crtc_count; TYPE_3__* vce_states; TYPE_2__ dyn_state; } ;
struct TYPE_13__ {TYPE_4__ dpm; } ;
struct radeon_device {scalar_t__ family; TYPE_5__ pm; } ;
struct kv_ps {int need_dfs_bypass; int num_levels; int dpm0_pg_nb_ps_lo; int dpm0_pg_nb_ps_hi; int dpmx_nb_ps_lo; int dpmx_nb_ps_hi; TYPE_8__* levels; } ;
struct TYPE_15__ {scalar_t__* nbp_memory_clock; scalar_t__ nb_dpm_enable; struct sumo_sclk_voltage_mapping_table sclk_voltage_mapping_table; } ;
struct kv_power_info {scalar_t__ high_voltage_t; int video_start; int battery_state; scalar_t__ disable_nb_ps3_in_battery; TYPE_7__ sys_info; scalar_t__ caps_stable_p_state; } ;
struct TYPE_16__ {scalar_t__ sclk; int /*<<< orphan*/  vddc_index; } ;
struct TYPE_14__ {scalar_t__ clk; } ;
struct TYPE_11__ {scalar_t__ sclk; scalar_t__ ecclk; scalar_t__ evclk; } ;
struct TYPE_9__ {scalar_t__ sclk_frequency; } ;

/* Variables and functions */
 int ATOM_PPLIB_CLASSIFICATION_UI_BATTERY ; 
 int ATOM_PPLIB_CLASSIFICATION_UI_MASK ; 
 scalar_t__ CHIP_KABINI ; 
 scalar_t__ CHIP_MULLINS ; 
 scalar_t__ kv_convert_8bit_index_to_voltage (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kv_get_high_voltage_limit (struct radeon_device*,int*) ; 
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 
 struct kv_ps* kv_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static void kv_apply_state_adjust_rules(struct radeon_device *rdev,
					struct radeon_ps *new_rps,
					struct radeon_ps *old_rps)
{
	struct kv_ps *ps = kv_get_ps(new_rps);
	struct kv_power_info *pi = kv_get_pi(rdev);
	u32 min_sclk = 10000; /* ??? */
	u32 sclk, mclk = 0;
	int i, limit;
	bool force_high;
	struct radeon_clock_voltage_dependency_table *table =
		&rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk;
	u32 stable_p_state_sclk = 0;
	struct radeon_clock_and_voltage_limits *max_limits =
		&rdev->pm.dpm.dyn_state.max_clock_voltage_on_ac;

	if (new_rps->vce_active) {
		new_rps->evclk = rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].evclk;
		new_rps->ecclk = rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].ecclk;
	} else {
		new_rps->evclk = 0;
		new_rps->ecclk = 0;
	}

	mclk = max_limits->mclk;
	sclk = min_sclk;

	if (pi->caps_stable_p_state) {
		stable_p_state_sclk = (max_limits->sclk * 75) / 100;

		for (i = table->count - 1; i >= 0; i--) {
			if (stable_p_state_sclk >= table->entries[i].clk) {
				stable_p_state_sclk = table->entries[i].clk;
				break;
			}
		}

		if (i > 0)
			stable_p_state_sclk = table->entries[0].clk;

		sclk = stable_p_state_sclk;
	}

	if (new_rps->vce_active) {
		if (sclk < rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].sclk)
			sclk = rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].sclk;
	}

	ps->need_dfs_bypass = true;

	for (i = 0; i < ps->num_levels; i++) {
		if (ps->levels[i].sclk < sclk)
			ps->levels[i].sclk = sclk;
	}

	if (table && table->count) {
		for (i = 0; i < ps->num_levels; i++) {
			if (pi->high_voltage_t &&
			    (pi->high_voltage_t <
			     kv_convert_8bit_index_to_voltage(rdev, ps->levels[i].vddc_index))) {
				kv_get_high_voltage_limit(rdev, &limit);
				ps->levels[i].sclk = table->entries[limit].clk;
			}
		}
	} else {
		struct sumo_sclk_voltage_mapping_table *table =
			&pi->sys_info.sclk_voltage_mapping_table;

		for (i = 0; i < ps->num_levels; i++) {
			if (pi->high_voltage_t &&
			    (pi->high_voltage_t <
			     kv_convert_8bit_index_to_voltage(rdev, ps->levels[i].vddc_index))) {
				kv_get_high_voltage_limit(rdev, &limit);
				ps->levels[i].sclk = table->entries[limit].sclk_frequency;
			}
		}
	}

	if (pi->caps_stable_p_state) {
		for (i = 0; i < ps->num_levels; i++) {
			ps->levels[i].sclk = stable_p_state_sclk;
		}
	}

	pi->video_start = new_rps->dclk || new_rps->vclk ||
		new_rps->evclk || new_rps->ecclk;

	if ((new_rps->class & ATOM_PPLIB_CLASSIFICATION_UI_MASK) ==
	    ATOM_PPLIB_CLASSIFICATION_UI_BATTERY)
		pi->battery_state = true;
	else
		pi->battery_state = false;

	if (rdev->family == CHIP_KABINI || rdev->family == CHIP_MULLINS) {
		ps->dpm0_pg_nb_ps_lo = 0x1;
		ps->dpm0_pg_nb_ps_hi = 0x0;
		ps->dpmx_nb_ps_lo = 0x1;
		ps->dpmx_nb_ps_hi = 0x0;
	} else {
		ps->dpm0_pg_nb_ps_lo = 0x3;
		ps->dpm0_pg_nb_ps_hi = 0x0;
		ps->dpmx_nb_ps_lo = 0x3;
		ps->dpmx_nb_ps_hi = 0x0;

		if (pi->sys_info.nb_dpm_enable) {
			force_high = (mclk >= pi->sys_info.nbp_memory_clock[3]) ||
				pi->video_start || (rdev->pm.dpm.new_active_crtc_count >= 3) ||
				pi->disable_nb_ps3_in_battery;
			ps->dpm0_pg_nb_ps_lo = force_high ? 0x2 : 0x3;
			ps->dpm0_pg_nb_ps_hi = 0x2;
			ps->dpmx_nb_ps_lo = force_high ? 0x2 : 0x3;
			ps->dpmx_nb_ps_hi = 0x2;
		}
	}
}