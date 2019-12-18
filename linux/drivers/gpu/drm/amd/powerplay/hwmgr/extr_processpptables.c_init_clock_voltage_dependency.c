#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_16__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_19__ {TYPE_9__* vdd_gfx_dependency_on_sclk; TYPE_9__* mvdd_dependency_on_mclk; TYPE_9__* vddc_dependency_on_sclk; int /*<<< orphan*/  valid_sclk_values; TYPE_9__* vddc_dependency_on_mclk; int /*<<< orphan*/  valid_mclk_values; int /*<<< orphan*/  max_clock_voltage_on_dc; TYPE_9__* vddci_dependency_on_mclk; TYPE_16__* cac_dtp_table; int /*<<< orphan*/ * acp_clock_voltage_dependency_table; int /*<<< orphan*/ * samu_clock_voltage_dependency_table; int /*<<< orphan*/ * uvd_clock_voltage_dependency_table; int /*<<< orphan*/ * vce_clock_voltage_dependency_table; int /*<<< orphan*/ * ppm_parameter_table; int /*<<< orphan*/ * vddc_dep_on_dal_pwrl; } ;
struct pp_hwmgr {TYPE_1__ dyn_state; } ;
typedef  int /*<<< orphan*/  VCEClockInfoArray ;
typedef  int /*<<< orphan*/  UVDClockInfoArray ;
typedef  scalar_t__ UCHAR ;
struct TYPE_24__ {scalar_t__ count; } ;
struct TYPE_23__ {scalar_t__ usTableSize; } ;
struct TYPE_22__ {scalar_t__ usVddcDependencyOnSCLKOffset; scalar_t__ usVddciDependencyOnMCLKOffset; scalar_t__ usVddcDependencyOnMCLKOffset; scalar_t__ usMaxClockVoltageOnDCOffset; scalar_t__ usMvddDependencyOnMCLKOffset; } ;
struct TYPE_21__ {int /*<<< orphan*/  power_tune_table; } ;
struct TYPE_20__ {scalar_t__ usMaximumPowerDeliveryLimit; scalar_t__ usTjMax; int /*<<< orphan*/  power_tune_table; } ;
struct TYPE_18__ {int usDefaultTargetOperatingTemp; } ;
typedef  int /*<<< orphan*/  ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table ;
typedef  int /*<<< orphan*/  ATOM_PPLIB_UVD_Clock_Voltage_Limit_Table ;
typedef  int /*<<< orphan*/  ATOM_PPLIB_SAMClk_Voltage_Limit_Table ;
typedef  TYPE_2__ ATOM_PPLIB_POWERTUNE_Table_V1 ;
typedef  TYPE_3__ ATOM_PPLIB_POWERTUNE_Table ;
typedef  TYPE_4__ ATOM_PPLIB_POWERPLAYTABLE4 ;
typedef  TYPE_5__ ATOM_PPLIB_POWERPLAYTABLE ;
typedef  int /*<<< orphan*/  ATOM_PPLIB_Clock_Voltage_Limit_Table ;
typedef  int /*<<< orphan*/  ATOM_PPLIB_Clock_Voltage_Dependency_Table ;
typedef  int /*<<< orphan*/  ATOM_PPLIB_ACPClk_Voltage_Limit_Table ;

/* Variables and functions */
 int get_acp_clock_voltage_limit_table (struct pp_hwmgr*,int /*<<< orphan*/ **,int /*<<< orphan*/  const*) ; 
 scalar_t__ get_acp_clock_voltage_limit_table_offset (struct pp_hwmgr*,TYPE_5__ const*) ; 
 int get_cac_tdp_table (struct pp_hwmgr*,TYPE_16__**,int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_cacp_tdp_table_offset (struct pp_hwmgr*,TYPE_5__ const*) ; 
 int get_clock_voltage_dependency_table (struct pp_hwmgr*,TYPE_9__**,int /*<<< orphan*/ *) ; 
 int get_clock_voltage_limit (struct pp_hwmgr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_samu_clock_voltage_limit_table (struct pp_hwmgr*,int /*<<< orphan*/ **,int /*<<< orphan*/  const*) ; 
 scalar_t__ get_samu_clock_voltage_limit_table_offset (struct pp_hwmgr*,TYPE_5__ const*) ; 
 scalar_t__ get_sclk_vdd_gfx_clock_voltage_dependency_table_offset (struct pp_hwmgr*,TYPE_5__ const*) ; 
 scalar_t__ get_uvd_clock_info_array_offset (struct pp_hwmgr*,TYPE_5__ const*) ; 
 int get_uvd_clock_voltage_limit_table (struct pp_hwmgr*,int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ get_uvd_clock_voltage_limit_table_offset (struct pp_hwmgr*,TYPE_5__ const*) ; 
 int get_valid_clk (struct pp_hwmgr*,int /*<<< orphan*/ *,TYPE_9__*) ; 
 scalar_t__ get_vce_clock_info_array_offset (struct pp_hwmgr*,TYPE_5__ const*) ; 
 int get_vce_clock_voltage_limit_table (struct pp_hwmgr*,int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ get_vce_clock_voltage_limit_table_offset (struct pp_hwmgr*,TYPE_5__ const*) ; 
 int le16_to_cpu (scalar_t__) ; 

__attribute__((used)) static int init_clock_voltage_dependency(struct pp_hwmgr *hwmgr,
			const ATOM_PPLIB_POWERPLAYTABLE *powerplay_table)
{
	ATOM_PPLIB_Clock_Voltage_Dependency_Table *table;
	ATOM_PPLIB_Clock_Voltage_Limit_Table *limit_table;
	int result = 0;

	uint16_t vce_clock_info_array_offset;
	uint16_t uvd_clock_info_array_offset;
	uint16_t table_offset;

	hwmgr->dyn_state.vddc_dependency_on_sclk = NULL;
	hwmgr->dyn_state.vddci_dependency_on_mclk = NULL;
	hwmgr->dyn_state.vddc_dependency_on_mclk = NULL;
	hwmgr->dyn_state.vddc_dep_on_dal_pwrl = NULL;
	hwmgr->dyn_state.mvdd_dependency_on_mclk = NULL;
	hwmgr->dyn_state.vce_clock_voltage_dependency_table = NULL;
	hwmgr->dyn_state.uvd_clock_voltage_dependency_table = NULL;
	hwmgr->dyn_state.samu_clock_voltage_dependency_table = NULL;
	hwmgr->dyn_state.acp_clock_voltage_dependency_table = NULL;
	hwmgr->dyn_state.ppm_parameter_table = NULL;
	hwmgr->dyn_state.vdd_gfx_dependency_on_sclk = NULL;

	vce_clock_info_array_offset = get_vce_clock_info_array_offset(
						hwmgr, powerplay_table);
	table_offset = get_vce_clock_voltage_limit_table_offset(hwmgr,
						powerplay_table);
	if (vce_clock_info_array_offset > 0 && table_offset > 0) {
		const VCEClockInfoArray *array = (const VCEClockInfoArray *)
				(((unsigned long) powerplay_table) +
				vce_clock_info_array_offset);
		const ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table *table =
				(const ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table *)
				(((unsigned long) powerplay_table) + table_offset);
		result = get_vce_clock_voltage_limit_table(hwmgr,
				&hwmgr->dyn_state.vce_clock_voltage_dependency_table,
				table, array);
	}

	uvd_clock_info_array_offset = get_uvd_clock_info_array_offset(hwmgr, powerplay_table);
	table_offset = get_uvd_clock_voltage_limit_table_offset(hwmgr, powerplay_table);

	if (uvd_clock_info_array_offset > 0 && table_offset > 0) {
		const UVDClockInfoArray *array = (const UVDClockInfoArray *)
				(((unsigned long) powerplay_table) +
				uvd_clock_info_array_offset);
		const ATOM_PPLIB_UVD_Clock_Voltage_Limit_Table *ptable =
				(const ATOM_PPLIB_UVD_Clock_Voltage_Limit_Table *)
				(((unsigned long) powerplay_table) + table_offset);
		result = get_uvd_clock_voltage_limit_table(hwmgr,
				&hwmgr->dyn_state.uvd_clock_voltage_dependency_table, ptable, array);
	}

	table_offset = get_samu_clock_voltage_limit_table_offset(hwmgr,
							    powerplay_table);

	if (table_offset > 0) {
		const ATOM_PPLIB_SAMClk_Voltage_Limit_Table *ptable =
				(const ATOM_PPLIB_SAMClk_Voltage_Limit_Table *)
				(((unsigned long) powerplay_table) + table_offset);
		result = get_samu_clock_voltage_limit_table(hwmgr,
				&hwmgr->dyn_state.samu_clock_voltage_dependency_table, ptable);
	}

	table_offset = get_acp_clock_voltage_limit_table_offset(hwmgr,
							     powerplay_table);

	if (table_offset > 0) {
		const ATOM_PPLIB_ACPClk_Voltage_Limit_Table *ptable =
				(const ATOM_PPLIB_ACPClk_Voltage_Limit_Table *)
				(((unsigned long) powerplay_table) + table_offset);
		result = get_acp_clock_voltage_limit_table(hwmgr,
				&hwmgr->dyn_state.acp_clock_voltage_dependency_table, ptable);
	}

	table_offset = get_cacp_tdp_table_offset(hwmgr, powerplay_table);
	if (table_offset > 0) {
		UCHAR rev_id = *(UCHAR *)(((unsigned long)powerplay_table) + table_offset);

		if (rev_id > 0) {
			const ATOM_PPLIB_POWERTUNE_Table_V1 *tune_table =
				(const ATOM_PPLIB_POWERTUNE_Table_V1 *)
				(((unsigned long) powerplay_table) + table_offset);
			result = get_cac_tdp_table(hwmgr, &hwmgr->dyn_state.cac_dtp_table,
				&tune_table->power_tune_table,
				le16_to_cpu(tune_table->usMaximumPowerDeliveryLimit));
			hwmgr->dyn_state.cac_dtp_table->usDefaultTargetOperatingTemp =
				le16_to_cpu(tune_table->usTjMax);
		} else {
			const ATOM_PPLIB_POWERTUNE_Table *tune_table =
				(const ATOM_PPLIB_POWERTUNE_Table *)
				(((unsigned long) powerplay_table) + table_offset);
			result = get_cac_tdp_table(hwmgr,
				&hwmgr->dyn_state.cac_dtp_table,
				&tune_table->power_tune_table, 255);
		}
	}

	if (le16_to_cpu(powerplay_table->usTableSize) >=
		sizeof(ATOM_PPLIB_POWERPLAYTABLE4)) {
		const ATOM_PPLIB_POWERPLAYTABLE4 *powerplay_table4 =
				(const ATOM_PPLIB_POWERPLAYTABLE4 *)powerplay_table;
		if (0 != powerplay_table4->usVddcDependencyOnSCLKOffset) {
			table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(((unsigned long) powerplay_table4) +
				 le16_to_cpu(powerplay_table4->usVddcDependencyOnSCLKOffset));
			result = get_clock_voltage_dependency_table(hwmgr,
				&hwmgr->dyn_state.vddc_dependency_on_sclk, table);
		}

		if (result == 0 && (0 != powerplay_table4->usVddciDependencyOnMCLKOffset)) {
			table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(((unsigned long) powerplay_table4) +
				 le16_to_cpu(powerplay_table4->usVddciDependencyOnMCLKOffset));
			result = get_clock_voltage_dependency_table(hwmgr,
				&hwmgr->dyn_state.vddci_dependency_on_mclk, table);
		}

		if (result == 0 && (0 != powerplay_table4->usVddcDependencyOnMCLKOffset)) {
			table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(((unsigned long) powerplay_table4) +
				 le16_to_cpu(powerplay_table4->usVddcDependencyOnMCLKOffset));
			result = get_clock_voltage_dependency_table(hwmgr,
				&hwmgr->dyn_state.vddc_dependency_on_mclk, table);
		}

		if (result == 0 && (0 != powerplay_table4->usMaxClockVoltageOnDCOffset)) {
			limit_table = (ATOM_PPLIB_Clock_Voltage_Limit_Table *)
				(((unsigned long) powerplay_table4) +
				 le16_to_cpu(powerplay_table4->usMaxClockVoltageOnDCOffset));
			result = get_clock_voltage_limit(hwmgr,
				&hwmgr->dyn_state.max_clock_voltage_on_dc, limit_table);
		}

		if (result == 0 && (NULL != hwmgr->dyn_state.vddc_dependency_on_mclk) &&
			(0 != hwmgr->dyn_state.vddc_dependency_on_mclk->count))
			result = get_valid_clk(hwmgr, &hwmgr->dyn_state.valid_mclk_values,
					hwmgr->dyn_state.vddc_dependency_on_mclk);

		if(result == 0 && (NULL != hwmgr->dyn_state.vddc_dependency_on_sclk) &&
			(0 != hwmgr->dyn_state.vddc_dependency_on_sclk->count))
			result = get_valid_clk(hwmgr,
				&hwmgr->dyn_state.valid_sclk_values,
				hwmgr->dyn_state.vddc_dependency_on_sclk);

		if (result == 0 && (0 != powerplay_table4->usMvddDependencyOnMCLKOffset)) {
			table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(((unsigned long) powerplay_table4) +
				 le16_to_cpu(powerplay_table4->usMvddDependencyOnMCLKOffset));
			result = get_clock_voltage_dependency_table(hwmgr,
				&hwmgr->dyn_state.mvdd_dependency_on_mclk, table);
		}
	}

	table_offset = get_sclk_vdd_gfx_clock_voltage_dependency_table_offset(hwmgr,
								powerplay_table);

	if (table_offset > 0) {
		table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
			(((unsigned long) powerplay_table) + table_offset);
		result = get_clock_voltage_dependency_table(hwmgr,
			&hwmgr->dyn_state.vdd_gfx_dependency_on_sclk, table);
	}

	return result;
}