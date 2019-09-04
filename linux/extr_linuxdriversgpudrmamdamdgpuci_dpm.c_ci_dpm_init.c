#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_16__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_22__ {int VRHotGpio; int AcDcGpio; } ;
struct TYPE_32__ {int temperature_low; int temperature_high; int temperature_shutdown; } ;
struct TYPE_27__ {int min; scalar_t__ max; } ;
struct TYPE_26__ {int min; scalar_t__ max; } ;
struct TYPE_25__ {void* min; void* max; } ;
struct TYPE_24__ {void* min; void* max; } ;
struct ci_power_info {int sys_pcie_mask; int dll_default_on; int caps_sclk_ds; int mclk_strobe_mode_threshold; int mclk_stutter_mode_threshold; int mclk_edc_enable_threshold; int mclk_edc_wr_enable_threshold; int caps_fps; int caps_sclk_throttle_low_notification; int caps_uvd_dpm; int caps_vce_dpm; int uvd_enabled; int vddc_phase_shed_control; int pcie_performance_request; int caps_sclk_ss_support; int caps_mclk_ss_support; int dynamic_ss; int thermal_protection; int caps_dynamic_ac_timing; int uvd_power_gated; int fan_ctrl_is_in_default_mode; void* mvdd_control; void* vddci_control; void* voltage_control; TYPE_15__ smc_state_table; TYPE_9__ thermal_temp_setting; scalar_t__ thermal_sclk_dpm_enabled; scalar_t__ pcie_dpm_key_disabled; scalar_t__ mclk_dpm_key_disabled; scalar_t__ sclk_dpm_key_disabled; int /*<<< orphan*/  mclk_activity_target; void** activity_target; int /*<<< orphan*/  sram_end; int /*<<< orphan*/  vbios_boot_state; TYPE_4__ pcie_lane_powersaving; TYPE_3__ pcie_lane_performance; TYPE_2__ pcie_gen_powersaving; TYPE_1__ pcie_gen_performance; int /*<<< orphan*/  force_pcie_gen; } ;
struct amdgpu_gpio_rec {int shift; scalar_t__ valid; } ;
struct TYPE_18__ {scalar_t__ sclk; scalar_t__ mclk; } ;
struct TYPE_31__ {int /*<<< orphan*/ * values; scalar_t__ count; } ;
struct TYPE_30__ {int /*<<< orphan*/ * values; scalar_t__ count; } ;
struct TYPE_29__ {int count; TYPE_16__* entries; } ;
struct TYPE_19__ {int mclk_sclk_ratio; int sclk_mclk_delta; int vddc_vddci_delta; TYPE_11__ max_clock_voltage_on_ac; TYPE_11__ max_clock_voltage_on_dc; TYPE_8__ valid_mclk_values; TYPE_7__ valid_sclk_values; TYPE_6__ vddc_dependency_on_dispclk; } ;
struct TYPE_20__ {int platform_caps; TYPE_12__ dyn_state; struct ci_power_info* priv; } ;
struct TYPE_21__ {int pcie_gen_mask; scalar_t__ int_thermal_type; TYPE_13__ dpm; } ;
struct TYPE_17__ {int /*<<< orphan*/  atom_context; } ;
struct TYPE_28__ {int pp_feature; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_14__ pm; TYPE_10__ mode_info; TYPE_5__ powerplay; } ;
struct amdgpu_clock_voltage_dependency_entry {int dummy; } ;
struct TYPE_23__ {int clk; int v; } ;
typedef  TYPE_15__ SMU7_Discrete_DpmTable ;

/* Variables and functions */
 void* AMDGPU_PCIE_GEN1 ; 
 void* AMDGPU_PCIE_GEN3 ; 
 int /*<<< orphan*/  AMDGPU_PCIE_GEN_INVALID ; 
 int /*<<< orphan*/  ASIC_InternalSS_Info ; 
 int ATOM_PP_PLATFORM_CAP_HARDWAREDC ; 
 int ATOM_PP_PLATFORM_CAP_MVDDCONTROL ; 
 int ATOM_PP_PLATFORM_CAP_REGULATOR_HOT ; 
 int ATOM_PP_PLATFORM_CAP_VDDCI_CONTROL ; 
 int CAIL_PCIE_LINK_SPEED_SUPPORT_MASK ; 
 scalar_t__ CHIP_HAWAII ; 
 void* CISLANDS_UNUSED_GPIO_PIN ; 
 void* CISLANDS_VOLTAGE_CONTROL_BY_GPIO ; 
 void* CISLANDS_VOLTAGE_CONTROL_BY_SVID2 ; 
 void* CISLANDS_VOLTAGE_CONTROL_NONE ; 
 int /*<<< orphan*/  CISLAND_MCLK_TARGETACTIVITY_DFLT ; 
 void* CISLAND_TARGETACTIVITY_DFLT ; 
 int CNB_PWRMGT_CNTL__DPM_ENABLED_MASK ; 
 int CNB_PWRMGT_CNTL__FORCE_NB_PS1_MASK ; 
 int CNB_PWRMGT_CNTL__GNB_SLOW_MASK ; 
 int CNB_PWRMGT_CNTL__GNB_SLOW_MODE_MASK ; 
 int CNB_PWRMGT_CNTL__GNB_SLOW_MODE__SHIFT ; 
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  DRM_INFO (char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PP_AC_DC_SWITCH_GPIO_PINID ; 
 int PP_SCLK_DEEP_SLEEP_MASK ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_RAM_END ; 
 scalar_t__ THERMAL_TYPE_NONE ; 
 int /*<<< orphan*/  VDDC_PCC_GPIO_PINID ; 
 int /*<<< orphan*/  VDDC_VRHOT_GPIO_PINID ; 
 int /*<<< orphan*/  VOLTAGE_OBJ_GPIO_LUT ; 
 int /*<<< orphan*/  VOLTAGE_OBJ_SVID2 ; 
 int /*<<< orphan*/  VOLTAGE_TYPE_MVDDC ; 
 int /*<<< orphan*/  VOLTAGE_TYPE_VDDC ; 
 int /*<<< orphan*/  VOLTAGE_TYPE_VDDCI ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 scalar_t__ amdgpu_atom_parse_data_header (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ amdgpu_atombios_is_voltage_gpio (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct amdgpu_gpio_rec amdgpu_atombios_lookup_gpio (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int amdgpu_get_platform_caps (struct amdgpu_device*) ; 
 int amdgpu_parse_extended_power_table (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_dpm_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_get_leakage_voltages (struct amdgpu_device*) ; 
 int ci_get_vbios_boot_values (struct amdgpu_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ci_initialize_powertune_defaults (struct amdgpu_device*) ; 
 int ci_parse_power_table (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_patch_dependency_tables_with_leakage (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_set_private_data_variables_based_on_pptable (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ixCNB_PWRMGT_CNTL ; 
 TYPE_16__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct ci_power_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_dpm_init(struct amdgpu_device *adev)
{
	int index = GetIndexIntoMasterTable(DATA, ASIC_InternalSS_Info);
	SMU7_Discrete_DpmTable *dpm_table;
	struct amdgpu_gpio_rec gpio;
	u16 data_offset, size;
	u8 frev, crev;
	struct ci_power_info *pi;
	int ret;

	pi = kzalloc(sizeof(struct ci_power_info), GFP_KERNEL);
	if (pi == NULL)
		return -ENOMEM;
	adev->pm.dpm.priv = pi;

	pi->sys_pcie_mask =
		adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_MASK;

	pi->force_pcie_gen = AMDGPU_PCIE_GEN_INVALID;

	pi->pcie_gen_performance.max = AMDGPU_PCIE_GEN1;
	pi->pcie_gen_performance.min = AMDGPU_PCIE_GEN3;
	pi->pcie_gen_powersaving.max = AMDGPU_PCIE_GEN1;
	pi->pcie_gen_powersaving.min = AMDGPU_PCIE_GEN3;

	pi->pcie_lane_performance.max = 0;
	pi->pcie_lane_performance.min = 16;
	pi->pcie_lane_powersaving.max = 0;
	pi->pcie_lane_powersaving.min = 16;

	ret = ci_get_vbios_boot_values(adev, &pi->vbios_boot_state);
	if (ret) {
		ci_dpm_fini(adev);
		return ret;
	}

	ret = amdgpu_get_platform_caps(adev);
	if (ret) {
		ci_dpm_fini(adev);
		return ret;
	}

	ret = amdgpu_parse_extended_power_table(adev);
	if (ret) {
		ci_dpm_fini(adev);
		return ret;
	}

	ret = ci_parse_power_table(adev);
	if (ret) {
		ci_dpm_fini(adev);
		return ret;
	}

	pi->dll_default_on = false;
	pi->sram_end = SMC_RAM_END;

	pi->activity_target[0] = CISLAND_TARGETACTIVITY_DFLT;
	pi->activity_target[1] = CISLAND_TARGETACTIVITY_DFLT;
	pi->activity_target[2] = CISLAND_TARGETACTIVITY_DFLT;
	pi->activity_target[3] = CISLAND_TARGETACTIVITY_DFLT;
	pi->activity_target[4] = CISLAND_TARGETACTIVITY_DFLT;
	pi->activity_target[5] = CISLAND_TARGETACTIVITY_DFLT;
	pi->activity_target[6] = CISLAND_TARGETACTIVITY_DFLT;
	pi->activity_target[7] = CISLAND_TARGETACTIVITY_DFLT;

	pi->mclk_activity_target = CISLAND_MCLK_TARGETACTIVITY_DFLT;

	pi->sclk_dpm_key_disabled = 0;
	pi->mclk_dpm_key_disabled = 0;
	pi->pcie_dpm_key_disabled = 0;
	pi->thermal_sclk_dpm_enabled = 0;

	if (adev->powerplay.pp_feature & PP_SCLK_DEEP_SLEEP_MASK)
		pi->caps_sclk_ds = true;
	else
		pi->caps_sclk_ds = false;

	pi->mclk_strobe_mode_threshold = 40000;
	pi->mclk_stutter_mode_threshold = 40000;
	pi->mclk_edc_enable_threshold = 40000;
	pi->mclk_edc_wr_enable_threshold = 40000;

	ci_initialize_powertune_defaults(adev);

	pi->caps_fps = false;

	pi->caps_sclk_throttle_low_notification = false;

	pi->caps_uvd_dpm = true;
	pi->caps_vce_dpm = true;

	ci_get_leakage_voltages(adev);
	ci_patch_dependency_tables_with_leakage(adev);
	ci_set_private_data_variables_based_on_pptable(adev);

	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries =
		kcalloc(4,
			sizeof(struct amdgpu_clock_voltage_dependency_entry),
			GFP_KERNEL);
	if (!adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries) {
		ci_dpm_fini(adev);
		return -ENOMEM;
	}
	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.count = 4;
	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[0].clk = 0;
	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[0].v = 0;
	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[1].clk = 36000;
	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[1].v = 720;
	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[2].clk = 54000;
	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[2].v = 810;
	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[3].clk = 72000;
	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries[3].v = 900;

	adev->pm.dpm.dyn_state.mclk_sclk_ratio = 4;
	adev->pm.dpm.dyn_state.sclk_mclk_delta = 15000;
	adev->pm.dpm.dyn_state.vddc_vddci_delta = 200;

	adev->pm.dpm.dyn_state.valid_sclk_values.count = 0;
	adev->pm.dpm.dyn_state.valid_sclk_values.values = NULL;
	adev->pm.dpm.dyn_state.valid_mclk_values.count = 0;
	adev->pm.dpm.dyn_state.valid_mclk_values.values = NULL;

	if (adev->asic_type == CHIP_HAWAII) {
		pi->thermal_temp_setting.temperature_low = 94500;
		pi->thermal_temp_setting.temperature_high = 95000;
		pi->thermal_temp_setting.temperature_shutdown = 104000;
	} else {
		pi->thermal_temp_setting.temperature_low = 99500;
		pi->thermal_temp_setting.temperature_high = 100000;
		pi->thermal_temp_setting.temperature_shutdown = 104000;
	}

	pi->uvd_enabled = false;

	dpm_table = &pi->smc_state_table;

	gpio = amdgpu_atombios_lookup_gpio(adev, VDDC_VRHOT_GPIO_PINID);
	if (gpio.valid) {
		dpm_table->VRHotGpio = gpio.shift;
		adev->pm.dpm.platform_caps |= ATOM_PP_PLATFORM_CAP_REGULATOR_HOT;
	} else {
		dpm_table->VRHotGpio = CISLANDS_UNUSED_GPIO_PIN;
		adev->pm.dpm.platform_caps &= ~ATOM_PP_PLATFORM_CAP_REGULATOR_HOT;
	}

	gpio = amdgpu_atombios_lookup_gpio(adev, PP_AC_DC_SWITCH_GPIO_PINID);
	if (gpio.valid) {
		dpm_table->AcDcGpio = gpio.shift;
		adev->pm.dpm.platform_caps |= ATOM_PP_PLATFORM_CAP_HARDWAREDC;
	} else {
		dpm_table->AcDcGpio = CISLANDS_UNUSED_GPIO_PIN;
		adev->pm.dpm.platform_caps &= ~ATOM_PP_PLATFORM_CAP_HARDWAREDC;
	}

	gpio = amdgpu_atombios_lookup_gpio(adev, VDDC_PCC_GPIO_PINID);
	if (gpio.valid) {
		u32 tmp = RREG32_SMC(ixCNB_PWRMGT_CNTL);

		switch (gpio.shift) {
		case 0:
			tmp &= ~CNB_PWRMGT_CNTL__GNB_SLOW_MODE_MASK;
			tmp |= 1 << CNB_PWRMGT_CNTL__GNB_SLOW_MODE__SHIFT;
			break;
		case 1:
			tmp &= ~CNB_PWRMGT_CNTL__GNB_SLOW_MODE_MASK;
			tmp |= 2 << CNB_PWRMGT_CNTL__GNB_SLOW_MODE__SHIFT;
			break;
		case 2:
			tmp |= CNB_PWRMGT_CNTL__GNB_SLOW_MASK;
			break;
		case 3:
			tmp |= CNB_PWRMGT_CNTL__FORCE_NB_PS1_MASK;
			break;
		case 4:
			tmp |= CNB_PWRMGT_CNTL__DPM_ENABLED_MASK;
			break;
		default:
			DRM_INFO("Invalid PCC GPIO: %u!\n", gpio.shift);
			break;
		}
		WREG32_SMC(ixCNB_PWRMGT_CNTL, tmp);
	}

	pi->voltage_control = CISLANDS_VOLTAGE_CONTROL_NONE;
	pi->vddci_control = CISLANDS_VOLTAGE_CONTROL_NONE;
	pi->mvdd_control = CISLANDS_VOLTAGE_CONTROL_NONE;
	if (amdgpu_atombios_is_voltage_gpio(adev, VOLTAGE_TYPE_VDDC, VOLTAGE_OBJ_GPIO_LUT))
		pi->voltage_control = CISLANDS_VOLTAGE_CONTROL_BY_GPIO;
	else if (amdgpu_atombios_is_voltage_gpio(adev, VOLTAGE_TYPE_VDDC, VOLTAGE_OBJ_SVID2))
		pi->voltage_control = CISLANDS_VOLTAGE_CONTROL_BY_SVID2;

	if (adev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_VDDCI_CONTROL) {
		if (amdgpu_atombios_is_voltage_gpio(adev, VOLTAGE_TYPE_VDDCI, VOLTAGE_OBJ_GPIO_LUT))
			pi->vddci_control = CISLANDS_VOLTAGE_CONTROL_BY_GPIO;
		else if (amdgpu_atombios_is_voltage_gpio(adev, VOLTAGE_TYPE_VDDCI, VOLTAGE_OBJ_SVID2))
			pi->vddci_control = CISLANDS_VOLTAGE_CONTROL_BY_SVID2;
		else
			adev->pm.dpm.platform_caps &= ~ATOM_PP_PLATFORM_CAP_VDDCI_CONTROL;
	}

	if (adev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_MVDDCONTROL) {
		if (amdgpu_atombios_is_voltage_gpio(adev, VOLTAGE_TYPE_MVDDC, VOLTAGE_OBJ_GPIO_LUT))
			pi->mvdd_control = CISLANDS_VOLTAGE_CONTROL_BY_GPIO;
		else if (amdgpu_atombios_is_voltage_gpio(adev, VOLTAGE_TYPE_MVDDC, VOLTAGE_OBJ_SVID2))
			pi->mvdd_control = CISLANDS_VOLTAGE_CONTROL_BY_SVID2;
		else
			adev->pm.dpm.platform_caps &= ~ATOM_PP_PLATFORM_CAP_MVDDCONTROL;
	}

	pi->vddc_phase_shed_control = true;

#if defined(CONFIG_ACPI)
	pi->pcie_performance_request =
		amdgpu_acpi_is_pcie_performance_request_supported(adev);
#else
	pi->pcie_performance_request = false;
#endif

	if (amdgpu_atom_parse_data_header(adev->mode_info.atom_context, index, &size,
				   &frev, &crev, &data_offset)) {
		pi->caps_sclk_ss_support = true;
		pi->caps_mclk_ss_support = true;
		pi->dynamic_ss = true;
	} else {
		pi->caps_sclk_ss_support = false;
		pi->caps_mclk_ss_support = false;
		pi->dynamic_ss = true;
	}

	if (adev->pm.int_thermal_type != THERMAL_TYPE_NONE)
		pi->thermal_protection = true;
	else
		pi->thermal_protection = false;

	pi->caps_dynamic_ac_timing = true;

	pi->uvd_power_gated = true;

	/* make sure dc limits are valid */
	if ((adev->pm.dpm.dyn_state.max_clock_voltage_on_dc.sclk == 0) ||
	    (adev->pm.dpm.dyn_state.max_clock_voltage_on_dc.mclk == 0))
		adev->pm.dpm.dyn_state.max_clock_voltage_on_dc =
			adev->pm.dpm.dyn_state.max_clock_voltage_on_ac;

	pi->fan_ctrl_is_in_default_mode = true;

	return 0;
}