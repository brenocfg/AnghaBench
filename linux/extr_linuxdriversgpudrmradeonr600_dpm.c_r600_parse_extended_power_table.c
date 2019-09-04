#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_108__   TYPE_9__ ;
typedef  struct TYPE_107__   TYPE_8__ ;
typedef  struct TYPE_106__   TYPE_7__ ;
typedef  struct TYPE_105__   TYPE_6__ ;
typedef  struct TYPE_104__   TYPE_5__ ;
typedef  struct TYPE_103__   TYPE_54__ ;
typedef  struct TYPE_102__   TYPE_53__ ;
typedef  struct TYPE_101__   TYPE_52__ ;
typedef  struct TYPE_100__   TYPE_51__ ;
typedef  struct TYPE_99__   TYPE_50__ ;
typedef  struct TYPE_98__   TYPE_4__ ;
typedef  struct TYPE_97__   TYPE_49__ ;
typedef  struct TYPE_96__   TYPE_48__ ;
typedef  struct TYPE_95__   TYPE_47__ ;
typedef  struct TYPE_94__   TYPE_46__ ;
typedef  struct TYPE_93__   TYPE_45__ ;
typedef  struct TYPE_92__   TYPE_44__ ;
typedef  struct TYPE_91__   TYPE_43__ ;
typedef  struct TYPE_90__   TYPE_42__ ;
typedef  struct TYPE_89__   TYPE_41__ ;
typedef  struct TYPE_88__   TYPE_40__ ;
typedef  struct TYPE_87__   TYPE_3__ ;
typedef  struct TYPE_86__   TYPE_39__ ;
typedef  struct TYPE_85__   TYPE_38__ ;
typedef  struct TYPE_84__   TYPE_37__ ;
typedef  struct TYPE_83__   TYPE_36__ ;
typedef  struct TYPE_82__   TYPE_35__ ;
typedef  struct TYPE_81__   TYPE_34__ ;
typedef  struct TYPE_80__   TYPE_33__ ;
typedef  struct TYPE_79__   TYPE_32__ ;
typedef  struct TYPE_78__   TYPE_31__ ;
typedef  struct TYPE_77__   TYPE_30__ ;
typedef  struct TYPE_76__   TYPE_2__ ;
typedef  struct TYPE_75__   TYPE_29__ ;
typedef  struct TYPE_74__   TYPE_28__ ;
typedef  struct TYPE_73__   TYPE_27__ ;
typedef  struct TYPE_72__   TYPE_26__ ;
typedef  struct TYPE_71__   TYPE_25__ ;
typedef  struct TYPE_70__   TYPE_24__ ;
typedef  struct TYPE_69__   TYPE_23__ ;
typedef  struct TYPE_68__   TYPE_22__ ;
typedef  struct TYPE_67__   TYPE_21__ ;
typedef  struct TYPE_66__   TYPE_20__ ;
typedef  struct TYPE_65__   TYPE_1__ ;
typedef  struct TYPE_64__   TYPE_19__ ;
typedef  struct TYPE_63__   TYPE_18__ ;
typedef  struct TYPE_62__   TYPE_17__ ;
typedef  struct TYPE_61__   TYPE_16__ ;
typedef  struct TYPE_60__   TYPE_15__ ;
typedef  struct TYPE_59__   TYPE_14__ ;
typedef  struct TYPE_58__   TYPE_13__ ;
typedef  struct TYPE_57__   TYPE_12__ ;
typedef  struct TYPE_56__   TYPE_11__ ;
typedef  struct TYPE_55__   TYPE_10__ ;

/* Type definitions */
struct TYPE_58__ {scalar_t__ usExtendendedHeaderOffset; scalar_t__ usFanTableOffset; } ;
struct TYPE_57__ {scalar_t__ usTableSize; } ;
struct TYPE_108__ {scalar_t__ usCACLeakageTableOffset; scalar_t__ usLoadLineSlope; int /*<<< orphan*/  ulCACLeakage; int /*<<< orphan*/  ulSQRampingThreshold; scalar_t__ usTDPODLimit; int /*<<< orphan*/  ulNearTDPLimit; int /*<<< orphan*/  ulTDPLimit; } ;
struct TYPE_106__ {scalar_t__ usVddcPhaseShedLimitsTableOffset; scalar_t__ usMaxClockVoltageOnDCOffset; scalar_t__ usMvddDependencyOnMCLKOffset; scalar_t__ usVddcDependencyOnMCLKOffset; scalar_t__ usVddciDependencyOnMCLKOffset; scalar_t__ usVddcDependencyOnSCLKOffset; } ;
union power_info {TYPE_13__ pplib3; TYPE_12__ pplib; TYPE_9__ pplib5; TYPE_7__ pplib4; } ;
struct TYPE_87__ {scalar_t__ usFanOutputSensitivity; scalar_t__ usFanPWMMax; int /*<<< orphan*/  ucFanControlMode; } ;
struct TYPE_76__ {int ucFanTableFormat; scalar_t__ usPWMHigh; scalar_t__ usPWMMed; scalar_t__ usPWMMin; scalar_t__ usTHigh; scalar_t__ usTMed; scalar_t__ usTMin; int /*<<< orphan*/  ucTHyst; } ;
struct TYPE_65__ {scalar_t__ usTMax; } ;
union fan_info {TYPE_3__ fan3; TYPE_2__ fan; TYPE_1__ fan2; } ;
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct radeon_vce_clock_voltage_dependency_entry {int dummy; } ;
struct radeon_uvd_clock_voltage_dependency_entry {int dummy; } ;
struct radeon_ppm_table {int dummy; } ;
struct radeon_phase_shedding_limits_entry {int dummy; } ;
struct radeon_mode_info {TYPE_54__* atom_context; } ;
struct TYPE_69__ {int count; TYPE_22__* entries; } ;
struct TYPE_66__ {int count; TYPE_19__* entries; } ;
struct TYPE_63__ {int count; TYPE_17__* entries; } ;
struct TYPE_60__ {int count; TYPE_14__* entries; } ;
struct TYPE_56__ {int count; TYPE_10__* entries; } ;
struct TYPE_107__ {int count; TYPE_53__* entries; } ;
struct TYPE_104__ {int sclk; int mclk; scalar_t__ vddci; scalar_t__ vddc; } ;
struct TYPE_101__ {int /*<<< orphan*/  entries; } ;
struct TYPE_71__ {TYPE_24__* cac_tdp_table; TYPE_23__ acp_clock_voltage_dependency_table; TYPE_21__* ppm_table; TYPE_20__ samu_clock_voltage_dependency_table; TYPE_18__ uvd_clock_voltage_dependency_table; TYPE_15__ vce_clock_voltage_dependency_table; TYPE_11__ cac_leakage_table; TYPE_8__ phase_shedding_limits_table; TYPE_5__ max_clock_voltage_on_dc; TYPE_52__ vddc_dependency_on_mclk; TYPE_52__ vddci_dependency_on_mclk; TYPE_52__ vddc_dependency_on_sclk; TYPE_52__ mvdd_dependency_on_mclk; } ;
struct TYPE_98__ {int t_max; int cycle_delay; int default_fan_output_sensitivity; int ucode_fan_control; scalar_t__ fan_output_sensitivity; scalar_t__ default_max_fan_pwm; int /*<<< orphan*/  control_mode; scalar_t__ pwm_high; scalar_t__ pwm_med; scalar_t__ pwm_min; scalar_t__ t_high; scalar_t__ t_med; scalar_t__ t_min; int /*<<< orphan*/  t_hyst; } ;
struct TYPE_72__ {int tdp_od_limit; int power_control; int platform_caps; TYPE_25__ dyn_state; TYPE_16__* vce_states; scalar_t__ load_line_slope; void* cac_leakage; void* sq_ramping_threshold; scalar_t__ tdp_adjustment; void* near_tdp_limit; void* near_tdp_limit_adjusted; void* tdp_limit; TYPE_4__ fan; } ;
struct TYPE_73__ {TYPE_26__ dpm; } ;
struct radeon_device {TYPE_27__ pm; struct radeon_mode_info mode_info; } ;
struct radeon_clock_voltage_dependency_entry {int dummy; } ;
struct radeon_cac_tdp_table {int dummy; } ;
struct radeon_cac_leakage_table {int dummy; } ;
struct _ATOM_PPLIB_POWERPLAYTABLE5 {int dummy; } ;
struct _ATOM_PPLIB_POWERPLAYTABLE4 {int dummy; } ;
struct _ATOM_PPLIB_POWERPLAYTABLE3 {int dummy; } ;
struct TYPE_74__ {int ucNumEntries; int /*<<< orphan*/ * entries; } ;
typedef  TYPE_28__ VCEClockInfoArray ;
struct TYPE_75__ {int ucEVClkHigh; int ucECClkHigh; scalar_t__ usECClkLow; scalar_t__ usEVClkLow; } ;
typedef  TYPE_29__ VCEClockInfo ;
struct TYPE_77__ {int ucNumEntries; int /*<<< orphan*/ * entries; } ;
typedef  TYPE_30__ UVDClockInfoArray ;
struct TYPE_78__ {int ucVClkHigh; int ucDClkHigh; scalar_t__ usDClkLow; scalar_t__ usVClkLow; } ;
typedef  TYPE_31__ UVDClockInfo ;
struct TYPE_105__ {int ucSclkHigh; int ucMclkHigh; scalar_t__ usVddci; scalar_t__ usVddc; scalar_t__ usMclkLow; scalar_t__ usSclkLow; } ;
struct TYPE_103__ {scalar_t__ bios; } ;
struct TYPE_102__ {int sclk; int mclk; scalar_t__ voltage; } ;
struct TYPE_100__ {int ucACPClockHigh; scalar_t__ usVoltage; scalar_t__ usACPClockLow; } ;
struct TYPE_99__ {int numEntries; TYPE_51__* entries; } ;
struct TYPE_97__ {int /*<<< orphan*/  ulLeakageValue; scalar_t__ usVddc; scalar_t__ usVddc3; scalar_t__ usVddc2; scalar_t__ usVddc1; } ;
struct TYPE_96__ {int ucNumEntries; TYPE_49__* entries; } ;
struct TYPE_95__ {TYPE_6__* entries; scalar_t__ ucNumEntries; } ;
struct TYPE_94__ {scalar_t__ usPowerTuneTableOffset; scalar_t__ usSize; scalar_t__ usACPTableOffset; scalar_t__ usPPMTableOffset; scalar_t__ usSAMUTableOffset; scalar_t__ usUVDTableOffset; scalar_t__ usVCETableOffset; } ;
struct TYPE_79__ {scalar_t__ usHighCACLeakage; scalar_t__ usLowCACLeakage; scalar_t__ usSmallPowerLimit; scalar_t__ usBatteryPowerLimit; scalar_t__ usTDC; scalar_t__ usConfigurableTDP; scalar_t__ usTDP; } ;
struct TYPE_93__ {TYPE_32__ power_tune_table; } ;
struct TYPE_92__ {TYPE_32__ power_tune_table; scalar_t__ usMaximumPowerDeliveryLimit; } ;
struct TYPE_91__ {int /*<<< orphan*/  ulTjmax; int /*<<< orphan*/  ulDGpuUlvPower; int /*<<< orphan*/  ulDGpuTDP; int /*<<< orphan*/  ulApuTDP; int /*<<< orphan*/  ulSmallACPlatformTDC; int /*<<< orphan*/  ulPlatformTDC; int /*<<< orphan*/  ulSmallACPlatformTDP; int /*<<< orphan*/  ulPlatformTDP; scalar_t__ usCpuCoreNumber; int /*<<< orphan*/  ucPpmDesign; } ;
struct TYPE_90__ {int ucSclkHigh; int ucMclkHigh; scalar_t__ usVoltage; scalar_t__ usMclkLow; scalar_t__ usSclkLow; } ;
struct TYPE_89__ {int ucNumEntries; TYPE_42__* entries; } ;
struct TYPE_88__ {int ucSAMClockHigh; scalar_t__ usVoltage; scalar_t__ usSAMClockLow; } ;
struct TYPE_86__ {int numEntries; TYPE_40__* entries; } ;
struct TYPE_85__ {int ucUVDClockInfoIndex; scalar_t__ usVoltage; } ;
struct TYPE_84__ {int numEntries; TYPE_38__* entries; } ;
struct TYPE_83__ {int ucVCEClockInfoIndex; scalar_t__ usVoltage; } ;
struct TYPE_82__ {int numEntries; TYPE_36__* entries; } ;
struct TYPE_81__ {int ucVCEClockInfoIndex; int ucClockInfoIndex; } ;
struct TYPE_80__ {int numEntries; TYPE_34__* entries; } ;
struct TYPE_70__ {int maximum_power_delivery_limit; scalar_t__ high_cac_leakage; scalar_t__ low_cac_leakage; scalar_t__ small_power_limit; scalar_t__ battery_power_limit; scalar_t__ tdc; scalar_t__ configurable_tdp; scalar_t__ tdp; } ;
struct TYPE_68__ {int clk; scalar_t__ v; } ;
struct TYPE_67__ {void* tj_max; void* dgpu_ulv_power; void* dgpu_tdp; void* apu_tdp; void* small_ac_platform_tdc; void* platform_tdc; void* small_ac_platform_tdp; void* platform_tdp; scalar_t__ cpu_core_number; int /*<<< orphan*/  ppm_design; } ;
struct TYPE_64__ {int clk; scalar_t__ v; } ;
struct TYPE_62__ {int vclk; int dclk; scalar_t__ v; } ;
struct TYPE_61__ {int evclk; int ecclk; int clk_idx; int pstate; } ;
struct TYPE_59__ {int evclk; int ecclk; scalar_t__ v; } ;
struct TYPE_55__ {void* leakage; scalar_t__ vddc; scalar_t__ vddc3; scalar_t__ vddc2; scalar_t__ vddc1; } ;
typedef  TYPE_32__ ATOM_PowerTune_Table ;
typedef  TYPE_33__ ATOM_PPLIB_VCE_State_Table ;
typedef  TYPE_34__ ATOM_PPLIB_VCE_State_Record ;
typedef  TYPE_35__ ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table ;
typedef  TYPE_36__ ATOM_PPLIB_VCE_Clock_Voltage_Limit_Record ;
typedef  TYPE_37__ ATOM_PPLIB_UVD_Clock_Voltage_Limit_Table ;
typedef  TYPE_38__ ATOM_PPLIB_UVD_Clock_Voltage_Limit_Record ;
typedef  TYPE_39__ ATOM_PPLIB_SAMClk_Voltage_Limit_Table ;
typedef  TYPE_40__ ATOM_PPLIB_SAMClk_Voltage_Limit_Record ;
typedef  TYPE_41__ ATOM_PPLIB_PhaseSheddingLimits_Table ;
typedef  TYPE_42__ ATOM_PPLIB_PhaseSheddingLimits_Record ;
typedef  TYPE_43__ ATOM_PPLIB_PPM_Table ;
typedef  TYPE_44__ ATOM_PPLIB_POWERTUNE_Table_V1 ;
typedef  TYPE_45__ ATOM_PPLIB_POWERTUNE_Table ;
typedef  TYPE_46__ ATOM_PPLIB_EXTENDEDHEADER ;
typedef  TYPE_47__ ATOM_PPLIB_Clock_Voltage_Limit_Table ;
typedef  int /*<<< orphan*/  ATOM_PPLIB_Clock_Voltage_Dependency_Table ;
typedef  TYPE_48__ ATOM_PPLIB_CAC_Leakage_Table ;
typedef  TYPE_49__ ATOM_PPLIB_CAC_Leakage_Record ;
typedef  TYPE_50__ ATOM_PPLIB_ACPClk_Voltage_Limit_Table ;
typedef  TYPE_51__ ATOM_PPLIB_ACPClk_Voltage_Limit_Record ;

/* Variables and functions */
 int ATOM_PP_PLATFORM_CAP_EVV ; 
 int /*<<< orphan*/  DATA ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PowerPlayInfo ; 
 int RADEON_MAX_VCE_LEVELS ; 
 scalar_t__ SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V2 ; 
 scalar_t__ SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V3 ; 
 scalar_t__ SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V4 ; 
 scalar_t__ SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V5 ; 
 scalar_t__ SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V6 ; 
 scalar_t__ SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V7 ; 
 int /*<<< orphan*/  atom_parse_data_header (TYPE_54__*,int,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 TYPE_53__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_free_extended_power_table (struct radeon_device*) ; 
 int r600_parse_clk_voltage_dep_table (TYPE_52__*,int /*<<< orphan*/ *) ; 

int r600_parse_extended_power_table(struct radeon_device *rdev)
{
	struct radeon_mode_info *mode_info = &rdev->mode_info;
	union power_info *power_info;
	union fan_info *fan_info;
	ATOM_PPLIB_Clock_Voltage_Dependency_Table *dep_table;
	int index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);
	u16 data_offset;
	u8 frev, crev;
	int ret, i;

	if (!atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset))
		return -EINVAL;
	power_info = (union power_info *)(mode_info->atom_context->bios + data_offset);

	/* fan table */
	if (le16_to_cpu(power_info->pplib.usTableSize) >=
	    sizeof(struct _ATOM_PPLIB_POWERPLAYTABLE3)) {
		if (power_info->pplib3.usFanTableOffset) {
			fan_info = (union fan_info *)(mode_info->atom_context->bios + data_offset +
						      le16_to_cpu(power_info->pplib3.usFanTableOffset));
			rdev->pm.dpm.fan.t_hyst = fan_info->fan.ucTHyst;
			rdev->pm.dpm.fan.t_min = le16_to_cpu(fan_info->fan.usTMin);
			rdev->pm.dpm.fan.t_med = le16_to_cpu(fan_info->fan.usTMed);
			rdev->pm.dpm.fan.t_high = le16_to_cpu(fan_info->fan.usTHigh);
			rdev->pm.dpm.fan.pwm_min = le16_to_cpu(fan_info->fan.usPWMMin);
			rdev->pm.dpm.fan.pwm_med = le16_to_cpu(fan_info->fan.usPWMMed);
			rdev->pm.dpm.fan.pwm_high = le16_to_cpu(fan_info->fan.usPWMHigh);
			if (fan_info->fan.ucFanTableFormat >= 2)
				rdev->pm.dpm.fan.t_max = le16_to_cpu(fan_info->fan2.usTMax);
			else
				rdev->pm.dpm.fan.t_max = 10900;
			rdev->pm.dpm.fan.cycle_delay = 100000;
			if (fan_info->fan.ucFanTableFormat >= 3) {
				rdev->pm.dpm.fan.control_mode = fan_info->fan3.ucFanControlMode;
				rdev->pm.dpm.fan.default_max_fan_pwm =
					le16_to_cpu(fan_info->fan3.usFanPWMMax);
				rdev->pm.dpm.fan.default_fan_output_sensitivity = 4836;
				rdev->pm.dpm.fan.fan_output_sensitivity =
					le16_to_cpu(fan_info->fan3.usFanOutputSensitivity);
			}
			rdev->pm.dpm.fan.ucode_fan_control = true;
		}
	}

	/* clock dependancy tables, shedding tables */
	if (le16_to_cpu(power_info->pplib.usTableSize) >=
	    sizeof(struct _ATOM_PPLIB_POWERPLAYTABLE4)) {
		if (power_info->pplib4.usVddcDependencyOnSCLKOffset) {
			dep_table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(power_info->pplib4.usVddcDependencyOnSCLKOffset));
			ret = r600_parse_clk_voltage_dep_table(&rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk,
							       dep_table);
			if (ret)
				return ret;
		}
		if (power_info->pplib4.usVddciDependencyOnMCLKOffset) {
			dep_table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(power_info->pplib4.usVddciDependencyOnMCLKOffset));
			ret = r600_parse_clk_voltage_dep_table(&rdev->pm.dpm.dyn_state.vddci_dependency_on_mclk,
							       dep_table);
			if (ret) {
				kfree(rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries);
				return ret;
			}
		}
		if (power_info->pplib4.usVddcDependencyOnMCLKOffset) {
			dep_table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(power_info->pplib4.usVddcDependencyOnMCLKOffset));
			ret = r600_parse_clk_voltage_dep_table(&rdev->pm.dpm.dyn_state.vddc_dependency_on_mclk,
							       dep_table);
			if (ret) {
				kfree(rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries);
				kfree(rdev->pm.dpm.dyn_state.vddci_dependency_on_mclk.entries);
				return ret;
			}
		}
		if (power_info->pplib4.usMvddDependencyOnMCLKOffset) {
			dep_table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(power_info->pplib4.usMvddDependencyOnMCLKOffset));
			ret = r600_parse_clk_voltage_dep_table(&rdev->pm.dpm.dyn_state.mvdd_dependency_on_mclk,
							       dep_table);
			if (ret) {
				kfree(rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries);
				kfree(rdev->pm.dpm.dyn_state.vddci_dependency_on_mclk.entries);
				kfree(rdev->pm.dpm.dyn_state.vddc_dependency_on_mclk.entries);
				return ret;
			}
		}
		if (power_info->pplib4.usMaxClockVoltageOnDCOffset) {
			ATOM_PPLIB_Clock_Voltage_Limit_Table *clk_v =
				(ATOM_PPLIB_Clock_Voltage_Limit_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(power_info->pplib4.usMaxClockVoltageOnDCOffset));
			if (clk_v->ucNumEntries) {
				rdev->pm.dpm.dyn_state.max_clock_voltage_on_dc.sclk =
					le16_to_cpu(clk_v->entries[0].usSclkLow) |
					(clk_v->entries[0].ucSclkHigh << 16);
				rdev->pm.dpm.dyn_state.max_clock_voltage_on_dc.mclk =
					le16_to_cpu(clk_v->entries[0].usMclkLow) |
					(clk_v->entries[0].ucMclkHigh << 16);
				rdev->pm.dpm.dyn_state.max_clock_voltage_on_dc.vddc =
					le16_to_cpu(clk_v->entries[0].usVddc);
				rdev->pm.dpm.dyn_state.max_clock_voltage_on_dc.vddci =
					le16_to_cpu(clk_v->entries[0].usVddci);
			}
		}
		if (power_info->pplib4.usVddcPhaseShedLimitsTableOffset) {
			ATOM_PPLIB_PhaseSheddingLimits_Table *psl =
				(ATOM_PPLIB_PhaseSheddingLimits_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(power_info->pplib4.usVddcPhaseShedLimitsTableOffset));
			ATOM_PPLIB_PhaseSheddingLimits_Record *entry;

			rdev->pm.dpm.dyn_state.phase_shedding_limits_table.entries =
				kcalloc(psl->ucNumEntries,
					sizeof(struct radeon_phase_shedding_limits_entry),
					GFP_KERNEL);
			if (!rdev->pm.dpm.dyn_state.phase_shedding_limits_table.entries) {
				r600_free_extended_power_table(rdev);
				return -ENOMEM;
			}

			entry = &psl->entries[0];
			for (i = 0; i < psl->ucNumEntries; i++) {
				rdev->pm.dpm.dyn_state.phase_shedding_limits_table.entries[i].sclk =
					le16_to_cpu(entry->usSclkLow) | (entry->ucSclkHigh << 16);
				rdev->pm.dpm.dyn_state.phase_shedding_limits_table.entries[i].mclk =
					le16_to_cpu(entry->usMclkLow) | (entry->ucMclkHigh << 16);
				rdev->pm.dpm.dyn_state.phase_shedding_limits_table.entries[i].voltage =
					le16_to_cpu(entry->usVoltage);
				entry = (ATOM_PPLIB_PhaseSheddingLimits_Record *)
					((u8 *)entry + sizeof(ATOM_PPLIB_PhaseSheddingLimits_Record));
			}
			rdev->pm.dpm.dyn_state.phase_shedding_limits_table.count =
				psl->ucNumEntries;
		}
	}

	/* cac data */
	if (le16_to_cpu(power_info->pplib.usTableSize) >=
	    sizeof(struct _ATOM_PPLIB_POWERPLAYTABLE5)) {
		rdev->pm.dpm.tdp_limit = le32_to_cpu(power_info->pplib5.ulTDPLimit);
		rdev->pm.dpm.near_tdp_limit = le32_to_cpu(power_info->pplib5.ulNearTDPLimit);
		rdev->pm.dpm.near_tdp_limit_adjusted = rdev->pm.dpm.near_tdp_limit;
		rdev->pm.dpm.tdp_od_limit = le16_to_cpu(power_info->pplib5.usTDPODLimit);
		if (rdev->pm.dpm.tdp_od_limit)
			rdev->pm.dpm.power_control = true;
		else
			rdev->pm.dpm.power_control = false;
		rdev->pm.dpm.tdp_adjustment = 0;
		rdev->pm.dpm.sq_ramping_threshold = le32_to_cpu(power_info->pplib5.ulSQRampingThreshold);
		rdev->pm.dpm.cac_leakage = le32_to_cpu(power_info->pplib5.ulCACLeakage);
		rdev->pm.dpm.load_line_slope = le16_to_cpu(power_info->pplib5.usLoadLineSlope);
		if (power_info->pplib5.usCACLeakageTableOffset) {
			ATOM_PPLIB_CAC_Leakage_Table *cac_table =
				(ATOM_PPLIB_CAC_Leakage_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(power_info->pplib5.usCACLeakageTableOffset));
			ATOM_PPLIB_CAC_Leakage_Record *entry;
			u32 size = cac_table->ucNumEntries * sizeof(struct radeon_cac_leakage_table);
			rdev->pm.dpm.dyn_state.cac_leakage_table.entries = kzalloc(size, GFP_KERNEL);
			if (!rdev->pm.dpm.dyn_state.cac_leakage_table.entries) {
				r600_free_extended_power_table(rdev);
				return -ENOMEM;
			}
			entry = &cac_table->entries[0];
			for (i = 0; i < cac_table->ucNumEntries; i++) {
				if (rdev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_EVV) {
					rdev->pm.dpm.dyn_state.cac_leakage_table.entries[i].vddc1 =
						le16_to_cpu(entry->usVddc1);
					rdev->pm.dpm.dyn_state.cac_leakage_table.entries[i].vddc2 =
						le16_to_cpu(entry->usVddc2);
					rdev->pm.dpm.dyn_state.cac_leakage_table.entries[i].vddc3 =
						le16_to_cpu(entry->usVddc3);
				} else {
					rdev->pm.dpm.dyn_state.cac_leakage_table.entries[i].vddc =
						le16_to_cpu(entry->usVddc);
					rdev->pm.dpm.dyn_state.cac_leakage_table.entries[i].leakage =
						le32_to_cpu(entry->ulLeakageValue);
				}
				entry = (ATOM_PPLIB_CAC_Leakage_Record *)
					((u8 *)entry + sizeof(ATOM_PPLIB_CAC_Leakage_Record));
			}
			rdev->pm.dpm.dyn_state.cac_leakage_table.count = cac_table->ucNumEntries;
		}
	}

	/* ext tables */
	if (le16_to_cpu(power_info->pplib.usTableSize) >=
	    sizeof(struct _ATOM_PPLIB_POWERPLAYTABLE3)) {
		ATOM_PPLIB_EXTENDEDHEADER *ext_hdr = (ATOM_PPLIB_EXTENDEDHEADER *)
			(mode_info->atom_context->bios + data_offset +
			 le16_to_cpu(power_info->pplib3.usExtendendedHeaderOffset));
		if ((le16_to_cpu(ext_hdr->usSize) >= SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V2) &&
			ext_hdr->usVCETableOffset) {
			VCEClockInfoArray *array = (VCEClockInfoArray *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usVCETableOffset) + 1);
			ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table *limits =
				(ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usVCETableOffset) + 1 +
				 1 + array->ucNumEntries * sizeof(VCEClockInfo));
			ATOM_PPLIB_VCE_State_Table *states =
				(ATOM_PPLIB_VCE_State_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usVCETableOffset) + 1 +
				 1 + (array->ucNumEntries * sizeof (VCEClockInfo)) +
				 1 + (limits->numEntries * sizeof(ATOM_PPLIB_VCE_Clock_Voltage_Limit_Record)));
			ATOM_PPLIB_VCE_Clock_Voltage_Limit_Record *entry;
			ATOM_PPLIB_VCE_State_Record *state_entry;
			VCEClockInfo *vce_clk;
			u32 size = limits->numEntries *
				sizeof(struct radeon_vce_clock_voltage_dependency_entry);
			rdev->pm.dpm.dyn_state.vce_clock_voltage_dependency_table.entries =
				kzalloc(size, GFP_KERNEL);
			if (!rdev->pm.dpm.dyn_state.vce_clock_voltage_dependency_table.entries) {
				r600_free_extended_power_table(rdev);
				return -ENOMEM;
			}
			rdev->pm.dpm.dyn_state.vce_clock_voltage_dependency_table.count =
				limits->numEntries;
			entry = &limits->entries[0];
			state_entry = &states->entries[0];
			for (i = 0; i < limits->numEntries; i++) {
				vce_clk = (VCEClockInfo *)
					((u8 *)&array->entries[0] +
					 (entry->ucVCEClockInfoIndex * sizeof(VCEClockInfo)));
				rdev->pm.dpm.dyn_state.vce_clock_voltage_dependency_table.entries[i].evclk =
					le16_to_cpu(vce_clk->usEVClkLow) | (vce_clk->ucEVClkHigh << 16);
				rdev->pm.dpm.dyn_state.vce_clock_voltage_dependency_table.entries[i].ecclk =
					le16_to_cpu(vce_clk->usECClkLow) | (vce_clk->ucECClkHigh << 16);
				rdev->pm.dpm.dyn_state.vce_clock_voltage_dependency_table.entries[i].v =
					le16_to_cpu(entry->usVoltage);
				entry = (ATOM_PPLIB_VCE_Clock_Voltage_Limit_Record *)
					((u8 *)entry + sizeof(ATOM_PPLIB_VCE_Clock_Voltage_Limit_Record));
			}
			for (i = 0; i < states->numEntries; i++) {
				if (i >= RADEON_MAX_VCE_LEVELS)
					break;
				vce_clk = (VCEClockInfo *)
					((u8 *)&array->entries[0] +
					 (state_entry->ucVCEClockInfoIndex * sizeof(VCEClockInfo)));
				rdev->pm.dpm.vce_states[i].evclk =
					le16_to_cpu(vce_clk->usEVClkLow) | (vce_clk->ucEVClkHigh << 16);
				rdev->pm.dpm.vce_states[i].ecclk =
					le16_to_cpu(vce_clk->usECClkLow) | (vce_clk->ucECClkHigh << 16);
				rdev->pm.dpm.vce_states[i].clk_idx =
					state_entry->ucClockInfoIndex & 0x3f;
				rdev->pm.dpm.vce_states[i].pstate =
					(state_entry->ucClockInfoIndex & 0xc0) >> 6;
				state_entry = (ATOM_PPLIB_VCE_State_Record *)
					((u8 *)state_entry + sizeof(ATOM_PPLIB_VCE_State_Record));
			}
		}
		if ((le16_to_cpu(ext_hdr->usSize) >= SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V3) &&
			ext_hdr->usUVDTableOffset) {
			UVDClockInfoArray *array = (UVDClockInfoArray *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usUVDTableOffset) + 1);
			ATOM_PPLIB_UVD_Clock_Voltage_Limit_Table *limits =
				(ATOM_PPLIB_UVD_Clock_Voltage_Limit_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usUVDTableOffset) + 1 +
				 1 + (array->ucNumEntries * sizeof (UVDClockInfo)));
			ATOM_PPLIB_UVD_Clock_Voltage_Limit_Record *entry;
			u32 size = limits->numEntries *
				sizeof(struct radeon_uvd_clock_voltage_dependency_entry);
			rdev->pm.dpm.dyn_state.uvd_clock_voltage_dependency_table.entries =
				kzalloc(size, GFP_KERNEL);
			if (!rdev->pm.dpm.dyn_state.uvd_clock_voltage_dependency_table.entries) {
				r600_free_extended_power_table(rdev);
				return -ENOMEM;
			}
			rdev->pm.dpm.dyn_state.uvd_clock_voltage_dependency_table.count =
				limits->numEntries;
			entry = &limits->entries[0];
			for (i = 0; i < limits->numEntries; i++) {
				UVDClockInfo *uvd_clk = (UVDClockInfo *)
					((u8 *)&array->entries[0] +
					 (entry->ucUVDClockInfoIndex * sizeof(UVDClockInfo)));
				rdev->pm.dpm.dyn_state.uvd_clock_voltage_dependency_table.entries[i].vclk =
					le16_to_cpu(uvd_clk->usVClkLow) | (uvd_clk->ucVClkHigh << 16);
				rdev->pm.dpm.dyn_state.uvd_clock_voltage_dependency_table.entries[i].dclk =
					le16_to_cpu(uvd_clk->usDClkLow) | (uvd_clk->ucDClkHigh << 16);
				rdev->pm.dpm.dyn_state.uvd_clock_voltage_dependency_table.entries[i].v =
					le16_to_cpu(entry->usVoltage);
				entry = (ATOM_PPLIB_UVD_Clock_Voltage_Limit_Record *)
					((u8 *)entry + sizeof(ATOM_PPLIB_UVD_Clock_Voltage_Limit_Record));
			}
		}
		if ((le16_to_cpu(ext_hdr->usSize) >= SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V4) &&
			ext_hdr->usSAMUTableOffset) {
			ATOM_PPLIB_SAMClk_Voltage_Limit_Table *limits =
				(ATOM_PPLIB_SAMClk_Voltage_Limit_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usSAMUTableOffset) + 1);
			ATOM_PPLIB_SAMClk_Voltage_Limit_Record *entry;
			u32 size = limits->numEntries *
				sizeof(struct radeon_clock_voltage_dependency_entry);
			rdev->pm.dpm.dyn_state.samu_clock_voltage_dependency_table.entries =
				kzalloc(size, GFP_KERNEL);
			if (!rdev->pm.dpm.dyn_state.samu_clock_voltage_dependency_table.entries) {
				r600_free_extended_power_table(rdev);
				return -ENOMEM;
			}
			rdev->pm.dpm.dyn_state.samu_clock_voltage_dependency_table.count =
				limits->numEntries;
			entry = &limits->entries[0];
			for (i = 0; i < limits->numEntries; i++) {
				rdev->pm.dpm.dyn_state.samu_clock_voltage_dependency_table.entries[i].clk =
					le16_to_cpu(entry->usSAMClockLow) | (entry->ucSAMClockHigh << 16);
				rdev->pm.dpm.dyn_state.samu_clock_voltage_dependency_table.entries[i].v =
					le16_to_cpu(entry->usVoltage);
				entry = (ATOM_PPLIB_SAMClk_Voltage_Limit_Record *)
					((u8 *)entry + sizeof(ATOM_PPLIB_SAMClk_Voltage_Limit_Record));
			}
		}
		if ((le16_to_cpu(ext_hdr->usSize) >= SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V5) &&
		    ext_hdr->usPPMTableOffset) {
			ATOM_PPLIB_PPM_Table *ppm = (ATOM_PPLIB_PPM_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usPPMTableOffset));
			rdev->pm.dpm.dyn_state.ppm_table =
				kzalloc(sizeof(struct radeon_ppm_table), GFP_KERNEL);
			if (!rdev->pm.dpm.dyn_state.ppm_table) {
				r600_free_extended_power_table(rdev);
				return -ENOMEM;
			}
			rdev->pm.dpm.dyn_state.ppm_table->ppm_design = ppm->ucPpmDesign;
			rdev->pm.dpm.dyn_state.ppm_table->cpu_core_number =
				le16_to_cpu(ppm->usCpuCoreNumber);
			rdev->pm.dpm.dyn_state.ppm_table->platform_tdp =
				le32_to_cpu(ppm->ulPlatformTDP);
			rdev->pm.dpm.dyn_state.ppm_table->small_ac_platform_tdp =
				le32_to_cpu(ppm->ulSmallACPlatformTDP);
			rdev->pm.dpm.dyn_state.ppm_table->platform_tdc =
				le32_to_cpu(ppm->ulPlatformTDC);
			rdev->pm.dpm.dyn_state.ppm_table->small_ac_platform_tdc =
				le32_to_cpu(ppm->ulSmallACPlatformTDC);
			rdev->pm.dpm.dyn_state.ppm_table->apu_tdp =
				le32_to_cpu(ppm->ulApuTDP);
			rdev->pm.dpm.dyn_state.ppm_table->dgpu_tdp =
				le32_to_cpu(ppm->ulDGpuTDP);
			rdev->pm.dpm.dyn_state.ppm_table->dgpu_ulv_power =
				le32_to_cpu(ppm->ulDGpuUlvPower);
			rdev->pm.dpm.dyn_state.ppm_table->tj_max =
				le32_to_cpu(ppm->ulTjmax);
		}
		if ((le16_to_cpu(ext_hdr->usSize) >= SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V6) &&
			ext_hdr->usACPTableOffset) {
			ATOM_PPLIB_ACPClk_Voltage_Limit_Table *limits =
				(ATOM_PPLIB_ACPClk_Voltage_Limit_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usACPTableOffset) + 1);
			ATOM_PPLIB_ACPClk_Voltage_Limit_Record *entry;
			u32 size = limits->numEntries *
				sizeof(struct radeon_clock_voltage_dependency_entry);
			rdev->pm.dpm.dyn_state.acp_clock_voltage_dependency_table.entries =
				kzalloc(size, GFP_KERNEL);
			if (!rdev->pm.dpm.dyn_state.acp_clock_voltage_dependency_table.entries) {
				r600_free_extended_power_table(rdev);
				return -ENOMEM;
			}
			rdev->pm.dpm.dyn_state.acp_clock_voltage_dependency_table.count =
				limits->numEntries;
			entry = &limits->entries[0];
			for (i = 0; i < limits->numEntries; i++) {
				rdev->pm.dpm.dyn_state.acp_clock_voltage_dependency_table.entries[i].clk =
					le16_to_cpu(entry->usACPClockLow) | (entry->ucACPClockHigh << 16);
				rdev->pm.dpm.dyn_state.acp_clock_voltage_dependency_table.entries[i].v =
					le16_to_cpu(entry->usVoltage);
				entry = (ATOM_PPLIB_ACPClk_Voltage_Limit_Record *)
					((u8 *)entry + sizeof(ATOM_PPLIB_ACPClk_Voltage_Limit_Record));
			}
		}
		if ((le16_to_cpu(ext_hdr->usSize) >= SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V7) &&
			ext_hdr->usPowerTuneTableOffset) {
			u8 rev = *(u8 *)(mode_info->atom_context->bios + data_offset +
					 le16_to_cpu(ext_hdr->usPowerTuneTableOffset));
			ATOM_PowerTune_Table *pt;
			rdev->pm.dpm.dyn_state.cac_tdp_table =
				kzalloc(sizeof(struct radeon_cac_tdp_table), GFP_KERNEL);
			if (!rdev->pm.dpm.dyn_state.cac_tdp_table) {
				r600_free_extended_power_table(rdev);
				return -ENOMEM;
			}
			if (rev > 0) {
				ATOM_PPLIB_POWERTUNE_Table_V1 *ppt = (ATOM_PPLIB_POWERTUNE_Table_V1 *)
					(mode_info->atom_context->bios + data_offset +
					 le16_to_cpu(ext_hdr->usPowerTuneTableOffset));
				rdev->pm.dpm.dyn_state.cac_tdp_table->maximum_power_delivery_limit =
					le16_to_cpu(ppt->usMaximumPowerDeliveryLimit);
				pt = &ppt->power_tune_table;
			} else {
				ATOM_PPLIB_POWERTUNE_Table *ppt = (ATOM_PPLIB_POWERTUNE_Table *)
					(mode_info->atom_context->bios + data_offset +
					 le16_to_cpu(ext_hdr->usPowerTuneTableOffset));
				rdev->pm.dpm.dyn_state.cac_tdp_table->maximum_power_delivery_limit = 255;
				pt = &ppt->power_tune_table;
			}
			rdev->pm.dpm.dyn_state.cac_tdp_table->tdp = le16_to_cpu(pt->usTDP);
			rdev->pm.dpm.dyn_state.cac_tdp_table->configurable_tdp =
				le16_to_cpu(pt->usConfigurableTDP);
			rdev->pm.dpm.dyn_state.cac_tdp_table->tdc = le16_to_cpu(pt->usTDC);
			rdev->pm.dpm.dyn_state.cac_tdp_table->battery_power_limit =
				le16_to_cpu(pt->usBatteryPowerLimit);
			rdev->pm.dpm.dyn_state.cac_tdp_table->small_power_limit =
				le16_to_cpu(pt->usSmallPowerLimit);
			rdev->pm.dpm.dyn_state.cac_tdp_table->low_cac_leakage =
				le16_to_cpu(pt->usLowCACLeakage);
			rdev->pm.dpm.dyn_state.cac_tdp_table->high_cac_leakage =
				le16_to_cpu(pt->usHighCACLeakage);
		}
	}

	return 0;
}