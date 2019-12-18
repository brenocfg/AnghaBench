#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * vdd_gfx_dependency_on_sclk; int /*<<< orphan*/ * ppm_parameter_table; int /*<<< orphan*/ * cac_dtp_table; int /*<<< orphan*/ * acp_clock_voltage_dependency_table; int /*<<< orphan*/ * samu_clock_voltage_dependency_table; int /*<<< orphan*/ * uvd_clock_voltage_dependency_table; int /*<<< orphan*/ * vce_clock_voltage_dependency_table; int /*<<< orphan*/ * vddc_phase_shed_limits_table; int /*<<< orphan*/ * cac_leakage_table; int /*<<< orphan*/ * valid_sclk_values; int /*<<< orphan*/ * valid_mclk_values; int /*<<< orphan*/ * mvdd_dependency_on_mclk; int /*<<< orphan*/ * vddc_dependency_on_mclk; int /*<<< orphan*/ * vddci_dependency_on_mclk; int /*<<< orphan*/ * vddc_dependency_on_sclk; } ;
struct pp_hwmgr {scalar_t__ chip_id; TYPE_1__ dyn_state; } ;

/* Variables and functions */
 scalar_t__ CHIP_RAVEN ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pp_tables_uninitialize(struct pp_hwmgr *hwmgr)
{
	if (hwmgr->chip_id == CHIP_RAVEN)
		return 0;

	kfree(hwmgr->dyn_state.vddc_dependency_on_sclk);
	hwmgr->dyn_state.vddc_dependency_on_sclk = NULL;

	kfree(hwmgr->dyn_state.vddci_dependency_on_mclk);
	hwmgr->dyn_state.vddci_dependency_on_mclk = NULL;

	kfree(hwmgr->dyn_state.vddc_dependency_on_mclk);
	hwmgr->dyn_state.vddc_dependency_on_mclk = NULL;

	kfree(hwmgr->dyn_state.mvdd_dependency_on_mclk);
	hwmgr->dyn_state.mvdd_dependency_on_mclk = NULL;

	kfree(hwmgr->dyn_state.valid_mclk_values);
	hwmgr->dyn_state.valid_mclk_values = NULL;

	kfree(hwmgr->dyn_state.valid_sclk_values);
	hwmgr->dyn_state.valid_sclk_values = NULL;

	kfree(hwmgr->dyn_state.cac_leakage_table);
	hwmgr->dyn_state.cac_leakage_table = NULL;

	kfree(hwmgr->dyn_state.vddc_phase_shed_limits_table);
	hwmgr->dyn_state.vddc_phase_shed_limits_table = NULL;

	kfree(hwmgr->dyn_state.vce_clock_voltage_dependency_table);
	hwmgr->dyn_state.vce_clock_voltage_dependency_table = NULL;

	kfree(hwmgr->dyn_state.uvd_clock_voltage_dependency_table);
	hwmgr->dyn_state.uvd_clock_voltage_dependency_table = NULL;

	kfree(hwmgr->dyn_state.samu_clock_voltage_dependency_table);
	hwmgr->dyn_state.samu_clock_voltage_dependency_table = NULL;

	kfree(hwmgr->dyn_state.acp_clock_voltage_dependency_table);
	hwmgr->dyn_state.acp_clock_voltage_dependency_table = NULL;

	kfree(hwmgr->dyn_state.cac_dtp_table);
	hwmgr->dyn_state.cac_dtp_table = NULL;

	kfree(hwmgr->dyn_state.ppm_parameter_table);
	hwmgr->dyn_state.ppm_parameter_table = NULL;

	kfree(hwmgr->dyn_state.vdd_gfx_dependency_on_sclk);
	hwmgr->dyn_state.vdd_gfx_dependency_on_sclk = NULL;

	return 0;
}