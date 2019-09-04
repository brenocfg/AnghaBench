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
typedef  size_t u32 ;
struct radeon_clock_voltage_dependency_table {int count; TYPE_5__* entries; } ;
struct radeon_cac_leakage_table {TYPE_1__* entries; } ;
struct TYPE_10__ {struct radeon_clock_voltage_dependency_table mvdd_dependency_on_mclk; struct radeon_clock_voltage_dependency_table vddci_dependency_on_mclk; struct radeon_cac_leakage_table cac_leakage_table; struct radeon_clock_voltage_dependency_table vddc_dependency_on_mclk; struct radeon_clock_voltage_dependency_table vddc_dependency_on_sclk; } ;
struct TYPE_11__ {TYPE_2__ dyn_state; } ;
struct TYPE_12__ {TYPE_3__ dpm; } ;
struct radeon_device {TYPE_4__ pm; } ;
struct TYPE_16__ {size_t count; TYPE_6__* dpm_levels; } ;
struct TYPE_15__ {TYPE_8__ mvdd_table; TYPE_8__ vddci_table; TYPE_8__ vddc_table; TYPE_8__ mclk_table; TYPE_8__ sclk_table; } ;
struct ci_power_info {TYPE_7__ dpm_table; } ;
struct ci_dpm_table {int dummy; } ;
struct TYPE_14__ {scalar_t__ value; int enabled; int /*<<< orphan*/  param1; } ;
struct TYPE_13__ {scalar_t__ clk; scalar_t__ v; } ;
struct TYPE_9__ {int /*<<< orphan*/  leakage; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SMU7_MAX_LEVELS_GRAPHICS ; 
 int /*<<< orphan*/  SMU7_MAX_LEVELS_MEMORY ; 
 int /*<<< orphan*/  SMU7_MAX_LEVELS_MVDD ; 
 int /*<<< orphan*/  SMU7_MAX_LEVELS_VDDC ; 
 int /*<<< orphan*/  SMU7_MAX_LEVELS_VDDCI ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_reset_single_dpm_table (struct radeon_device*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ci_setup_default_pcie_tables (struct radeon_device*) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ci_setup_default_dpm_tables(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	struct radeon_clock_voltage_dependency_table *allowed_sclk_vddc_table =
		&rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk;
	struct radeon_clock_voltage_dependency_table *allowed_mclk_table =
		&rdev->pm.dpm.dyn_state.vddc_dependency_on_mclk;
	struct radeon_cac_leakage_table *std_voltage_table =
		&rdev->pm.dpm.dyn_state.cac_leakage_table;
	u32 i;

	if (allowed_sclk_vddc_table == NULL)
		return -EINVAL;
	if (allowed_sclk_vddc_table->count < 1)
		return -EINVAL;
	if (allowed_mclk_table == NULL)
		return -EINVAL;
	if (allowed_mclk_table->count < 1)
		return -EINVAL;

	memset(&pi->dpm_table, 0, sizeof(struct ci_dpm_table));

	ci_reset_single_dpm_table(rdev,
				  &pi->dpm_table.sclk_table,
				  SMU7_MAX_LEVELS_GRAPHICS);
	ci_reset_single_dpm_table(rdev,
				  &pi->dpm_table.mclk_table,
				  SMU7_MAX_LEVELS_MEMORY);
	ci_reset_single_dpm_table(rdev,
				  &pi->dpm_table.vddc_table,
				  SMU7_MAX_LEVELS_VDDC);
	ci_reset_single_dpm_table(rdev,
				  &pi->dpm_table.vddci_table,
				  SMU7_MAX_LEVELS_VDDCI);
	ci_reset_single_dpm_table(rdev,
				  &pi->dpm_table.mvdd_table,
				  SMU7_MAX_LEVELS_MVDD);

	pi->dpm_table.sclk_table.count = 0;
	for (i = 0; i < allowed_sclk_vddc_table->count; i++) {
		if ((i == 0) ||
		    (pi->dpm_table.sclk_table.dpm_levels[pi->dpm_table.sclk_table.count-1].value !=
		     allowed_sclk_vddc_table->entries[i].clk)) {
			pi->dpm_table.sclk_table.dpm_levels[pi->dpm_table.sclk_table.count].value =
				allowed_sclk_vddc_table->entries[i].clk;
			pi->dpm_table.sclk_table.dpm_levels[pi->dpm_table.sclk_table.count].enabled =
				(i == 0) ? true : false;
			pi->dpm_table.sclk_table.count++;
		}
	}

	pi->dpm_table.mclk_table.count = 0;
	for (i = 0; i < allowed_mclk_table->count; i++) {
		if ((i == 0) ||
		    (pi->dpm_table.mclk_table.dpm_levels[pi->dpm_table.mclk_table.count-1].value !=
		     allowed_mclk_table->entries[i].clk)) {
			pi->dpm_table.mclk_table.dpm_levels[pi->dpm_table.mclk_table.count].value =
				allowed_mclk_table->entries[i].clk;
			pi->dpm_table.mclk_table.dpm_levels[pi->dpm_table.mclk_table.count].enabled =
				(i == 0) ? true : false;
			pi->dpm_table.mclk_table.count++;
		}
	}

	for (i = 0; i < allowed_sclk_vddc_table->count; i++) {
		pi->dpm_table.vddc_table.dpm_levels[i].value =
			allowed_sclk_vddc_table->entries[i].v;
		pi->dpm_table.vddc_table.dpm_levels[i].param1 =
			std_voltage_table->entries[i].leakage;
		pi->dpm_table.vddc_table.dpm_levels[i].enabled = true;
	}
	pi->dpm_table.vddc_table.count = allowed_sclk_vddc_table->count;

	allowed_mclk_table = &rdev->pm.dpm.dyn_state.vddci_dependency_on_mclk;
	if (allowed_mclk_table) {
		for (i = 0; i < allowed_mclk_table->count; i++) {
			pi->dpm_table.vddci_table.dpm_levels[i].value =
				allowed_mclk_table->entries[i].v;
			pi->dpm_table.vddci_table.dpm_levels[i].enabled = true;
		}
		pi->dpm_table.vddci_table.count = allowed_mclk_table->count;
	}

	allowed_mclk_table = &rdev->pm.dpm.dyn_state.mvdd_dependency_on_mclk;
	if (allowed_mclk_table) {
		for (i = 0; i < allowed_mclk_table->count; i++) {
			pi->dpm_table.mvdd_table.dpm_levels[i].value =
				allowed_mclk_table->entries[i].v;
			pi->dpm_table.mvdd_table.dpm_levels[i].enabled = true;
		}
		pi->dpm_table.mvdd_table.count = allowed_mclk_table->count;
	}

	ci_setup_default_pcie_tables(rdev);

	return 0;
}