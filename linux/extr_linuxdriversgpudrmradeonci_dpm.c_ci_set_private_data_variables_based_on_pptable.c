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
struct TYPE_6__ {int /*<<< orphan*/  vddci; int /*<<< orphan*/  vddc; int /*<<< orphan*/  mclk; int /*<<< orphan*/  sclk; } ;
struct radeon_clock_voltage_dependency_table {int count; TYPE_5__* entries; } ;
struct TYPE_7__ {TYPE_1__ max_clock_voltage_on_ac; struct radeon_clock_voltage_dependency_table vddci_dependency_on_mclk; struct radeon_clock_voltage_dependency_table vddc_dependency_on_mclk; struct radeon_clock_voltage_dependency_table vddc_dependency_on_sclk; } ;
struct TYPE_8__ {TYPE_2__ dyn_state; } ;
struct TYPE_9__ {TYPE_3__ dpm; } ;
struct radeon_device {TYPE_4__ pm; } ;
struct ci_power_info {int /*<<< orphan*/  max_vddci_in_pp_table; int /*<<< orphan*/  min_vddci_in_pp_table; int /*<<< orphan*/  max_vddc_in_pp_table; int /*<<< orphan*/  min_vddc_in_pp_table; } ;
struct TYPE_10__ {int /*<<< orphan*/  v; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int ci_set_private_data_variables_based_on_pptable(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	struct radeon_clock_voltage_dependency_table *allowed_sclk_vddc_table =
		&rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk;
	struct radeon_clock_voltage_dependency_table *allowed_mclk_vddc_table =
		&rdev->pm.dpm.dyn_state.vddc_dependency_on_mclk;
	struct radeon_clock_voltage_dependency_table *allowed_mclk_vddci_table =
		&rdev->pm.dpm.dyn_state.vddci_dependency_on_mclk;

	if (allowed_sclk_vddc_table == NULL)
		return -EINVAL;
	if (allowed_sclk_vddc_table->count < 1)
		return -EINVAL;
	if (allowed_mclk_vddc_table == NULL)
		return -EINVAL;
	if (allowed_mclk_vddc_table->count < 1)
		return -EINVAL;
	if (allowed_mclk_vddci_table == NULL)
		return -EINVAL;
	if (allowed_mclk_vddci_table->count < 1)
		return -EINVAL;

	pi->min_vddc_in_pp_table = allowed_sclk_vddc_table->entries[0].v;
	pi->max_vddc_in_pp_table =
		allowed_sclk_vddc_table->entries[allowed_sclk_vddc_table->count - 1].v;

	pi->min_vddci_in_pp_table = allowed_mclk_vddci_table->entries[0].v;
	pi->max_vddci_in_pp_table =
		allowed_mclk_vddci_table->entries[allowed_mclk_vddci_table->count - 1].v;

	rdev->pm.dpm.dyn_state.max_clock_voltage_on_ac.sclk =
		allowed_sclk_vddc_table->entries[allowed_sclk_vddc_table->count - 1].clk;
	rdev->pm.dpm.dyn_state.max_clock_voltage_on_ac.mclk =
		allowed_mclk_vddc_table->entries[allowed_sclk_vddc_table->count - 1].clk;
	rdev->pm.dpm.dyn_state.max_clock_voltage_on_ac.vddc =
		allowed_sclk_vddc_table->entries[allowed_sclk_vddc_table->count - 1].v;
	rdev->pm.dpm.dyn_state.max_clock_voltage_on_ac.vddci =
		allowed_mclk_vddci_table->entries[allowed_mclk_vddci_table->count - 1].v;

	return 0;
}