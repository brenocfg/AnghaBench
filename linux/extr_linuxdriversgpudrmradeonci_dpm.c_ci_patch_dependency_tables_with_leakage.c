#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cac_leakage_table; int /*<<< orphan*/  max_clock_voltage_on_dc; int /*<<< orphan*/  max_clock_voltage_on_ac; int /*<<< orphan*/  phase_shedding_limits_table; int /*<<< orphan*/  acp_clock_voltage_dependency_table; int /*<<< orphan*/  samu_clock_voltage_dependency_table; int /*<<< orphan*/  uvd_clock_voltage_dependency_table; int /*<<< orphan*/  vce_clock_voltage_dependency_table; int /*<<< orphan*/  vddci_dependency_on_mclk; int /*<<< orphan*/  vddc_dependency_on_dispclk; int /*<<< orphan*/  vddc_dependency_on_mclk; int /*<<< orphan*/  vddc_dependency_on_sclk; } ;
struct TYPE_5__ {TYPE_1__ dyn_state; } ;
struct TYPE_6__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_3__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ci_patch_cac_leakage_table_with_vddc_leakage (struct radeon_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ci_patch_clock_voltage_dependency_table_with_vddc_leakage (struct radeon_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ci_patch_clock_voltage_dependency_table_with_vddci_leakage (struct radeon_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ci_patch_clock_voltage_limits_with_vddc_leakage (struct radeon_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ci_patch_uvd_clock_voltage_dependency_table_with_vddc_leakage (struct radeon_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ci_patch_vce_clock_voltage_dependency_table_with_vddc_leakage (struct radeon_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ci_patch_vddc_phase_shed_limit_table_with_vddc_leakage (struct radeon_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ci_patch_dependency_tables_with_leakage(struct radeon_device *rdev)
{

	ci_patch_clock_voltage_dependency_table_with_vddc_leakage(rdev,
								  &rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk);
	ci_patch_clock_voltage_dependency_table_with_vddc_leakage(rdev,
								  &rdev->pm.dpm.dyn_state.vddc_dependency_on_mclk);
	ci_patch_clock_voltage_dependency_table_with_vddc_leakage(rdev,
								  &rdev->pm.dpm.dyn_state.vddc_dependency_on_dispclk);
	ci_patch_clock_voltage_dependency_table_with_vddci_leakage(rdev,
								   &rdev->pm.dpm.dyn_state.vddci_dependency_on_mclk);
	ci_patch_vce_clock_voltage_dependency_table_with_vddc_leakage(rdev,
								      &rdev->pm.dpm.dyn_state.vce_clock_voltage_dependency_table);
	ci_patch_uvd_clock_voltage_dependency_table_with_vddc_leakage(rdev,
								      &rdev->pm.dpm.dyn_state.uvd_clock_voltage_dependency_table);
	ci_patch_clock_voltage_dependency_table_with_vddc_leakage(rdev,
								  &rdev->pm.dpm.dyn_state.samu_clock_voltage_dependency_table);
	ci_patch_clock_voltage_dependency_table_with_vddc_leakage(rdev,
								  &rdev->pm.dpm.dyn_state.acp_clock_voltage_dependency_table);
	ci_patch_vddc_phase_shed_limit_table_with_vddc_leakage(rdev,
							       &rdev->pm.dpm.dyn_state.phase_shedding_limits_table);
	ci_patch_clock_voltage_limits_with_vddc_leakage(rdev,
							&rdev->pm.dpm.dyn_state.max_clock_voltage_on_ac);
	ci_patch_clock_voltage_limits_with_vddc_leakage(rdev,
							&rdev->pm.dpm.dyn_state.max_clock_voltage_on_dc);
	ci_patch_cac_leakage_table_with_vddc_leakage(rdev,
						     &rdev->pm.dpm.dyn_state.cac_leakage_table);

}