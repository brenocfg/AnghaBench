#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int VidMaxLimit; int VidStep; int /*<<< orphan*/  platformCaps; void* TDPODLimit; scalar_t__ VidMinLimit; scalar_t__ VidAdjustmentPolarity; scalar_t__ VidAdjustment; scalar_t__ TDPAdjustment; } ;
struct pp_hwmgr {TYPE_1__ platform_descriptor; scalar_t__ pptable; } ;
struct phm_ppt_v2_information {int /*<<< orphan*/ * vddci_lookup_table; int /*<<< orphan*/ * vddmem_lookup_table; int /*<<< orphan*/ * vddc_lookup_table; int /*<<< orphan*/ * ppm_parameter_table; void* uc_dcef_dpm_voltage_mode; void* uc_mp0_dpm_voltage_mode; void* uc_vce_dpm_voltage_mode; void* uc_uvd_dpm_voltage_mode; void* uc_uclk_dpm_voltage_mode; void* uc_soc_dpm_voltage_mode; void* uc_gfx_dpm_voltage_mode; void* us_gfxclk_slew_rate; void* us_ulv_gfxclk_bypass; void* us_ulv_mp1clk_did; void* us_ulv_smnclk_did; void* us_ulv_voltage_offset; } ;
struct TYPE_5__ {scalar_t__ usVddciLookupTableOffset; scalar_t__ usVddmemLookupTableOffset; scalar_t__ usVddcLookupTableOffset; scalar_t__ usPowerControlLimit; scalar_t__ ucDcefVoltageMode; scalar_t__ ucMp0VoltageMode; scalar_t__ ucVceVoltageMode; scalar_t__ ucUvdVoltageMode; scalar_t__ ucUclkVoltageMode; scalar_t__ ucSocVoltageMode; scalar_t__ ucGfxVoltageMode; scalar_t__ usGfxclkSlewRate; scalar_t__ usUlvGfxclkBypass; scalar_t__ usUlvMp1clkDid; scalar_t__ usUlvSmnclkDid; scalar_t__ usUlvVoltageOffset; } ;
typedef  int /*<<< orphan*/  ATOM_Vega10_Voltage_Lookup_Table ;
typedef  TYPE_2__ ATOM_Vega10_POWERPLAYTABLE ;

/* Variables and functions */
 int /*<<< orphan*/  PHM_PlatformCaps_PowerControl ; 
 int get_vddc_lookup_table (struct pp_hwmgr*,int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int) ; 
 void* le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  phm_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_dpm_2_parameters(
		struct pp_hwmgr *hwmgr,
		const ATOM_Vega10_POWERPLAYTABLE *powerplay_table)
{
	int result = 0;
	struct phm_ppt_v2_information *pp_table_info =
			(struct phm_ppt_v2_information *)(hwmgr->pptable);
	uint32_t disable_power_control = 0;

	pp_table_info->us_ulv_voltage_offset =
		le16_to_cpu(powerplay_table->usUlvVoltageOffset);

	pp_table_info->us_ulv_smnclk_did =
			le16_to_cpu(powerplay_table->usUlvSmnclkDid);
	pp_table_info->us_ulv_mp1clk_did =
			le16_to_cpu(powerplay_table->usUlvMp1clkDid);
	pp_table_info->us_ulv_gfxclk_bypass =
			le16_to_cpu(powerplay_table->usUlvGfxclkBypass);
	pp_table_info->us_gfxclk_slew_rate =
			le16_to_cpu(powerplay_table->usGfxclkSlewRate);
	pp_table_info->uc_gfx_dpm_voltage_mode  =
			le16_to_cpu(powerplay_table->ucGfxVoltageMode);
	pp_table_info->uc_soc_dpm_voltage_mode  =
			le16_to_cpu(powerplay_table->ucSocVoltageMode);
	pp_table_info->uc_uclk_dpm_voltage_mode =
			le16_to_cpu(powerplay_table->ucUclkVoltageMode);
	pp_table_info->uc_uvd_dpm_voltage_mode  =
			le16_to_cpu(powerplay_table->ucUvdVoltageMode);
	pp_table_info->uc_vce_dpm_voltage_mode  =
			le16_to_cpu(powerplay_table->ucVceVoltageMode);
	pp_table_info->uc_mp0_dpm_voltage_mode  =
			le16_to_cpu(powerplay_table->ucMp0VoltageMode);
	pp_table_info->uc_dcef_dpm_voltage_mode =
			le16_to_cpu(powerplay_table->ucDcefVoltageMode);

	pp_table_info->ppm_parameter_table = NULL;
	pp_table_info->vddc_lookup_table = NULL;
	pp_table_info->vddmem_lookup_table = NULL;
	pp_table_info->vddci_lookup_table = NULL;

	/* TDP limits */
	hwmgr->platform_descriptor.TDPODLimit =
		le16_to_cpu(powerplay_table->usPowerControlLimit);
	hwmgr->platform_descriptor.TDPAdjustment = 0;
	hwmgr->platform_descriptor.VidAdjustment = 0;
	hwmgr->platform_descriptor.VidAdjustmentPolarity = 0;
	hwmgr->platform_descriptor.VidMinLimit = 0;
	hwmgr->platform_descriptor.VidMaxLimit = 1500000;
	hwmgr->platform_descriptor.VidStep = 6250;

	disable_power_control = 0;
	if (!disable_power_control) {
		/* enable TDP overdrive (PowerControl) feature as well if supported */
		if (hwmgr->platform_descriptor.TDPODLimit)
			phm_cap_set(hwmgr->platform_descriptor.platformCaps,
			PHM_PlatformCaps_PowerControl);
	}

	if (powerplay_table->usVddcLookupTableOffset) {
		const ATOM_Vega10_Voltage_Lookup_Table *vddc_table =
				(ATOM_Vega10_Voltage_Lookup_Table *)
				(((unsigned long)powerplay_table) +
				le16_to_cpu(powerplay_table->usVddcLookupTableOffset));
		result = get_vddc_lookup_table(hwmgr,
				&pp_table_info->vddc_lookup_table, vddc_table, 8);
	}

	if (powerplay_table->usVddmemLookupTableOffset) {
		const ATOM_Vega10_Voltage_Lookup_Table *vdd_mem_table =
				(ATOM_Vega10_Voltage_Lookup_Table *)
				(((unsigned long)powerplay_table) +
				le16_to_cpu(powerplay_table->usVddmemLookupTableOffset));
		result = get_vddc_lookup_table(hwmgr,
				&pp_table_info->vddmem_lookup_table, vdd_mem_table, 4);
	}

	if (powerplay_table->usVddciLookupTableOffset) {
		const ATOM_Vega10_Voltage_Lookup_Table *vddci_table =
				(ATOM_Vega10_Voltage_Lookup_Table *)
				(((unsigned long)powerplay_table) +
				le16_to_cpu(powerplay_table->usVddciLookupTableOffset));
		result = get_vddc_lookup_table(hwmgr,
				&pp_table_info->vddci_lookup_table, vddci_table, 4);
	}

	return result;
}