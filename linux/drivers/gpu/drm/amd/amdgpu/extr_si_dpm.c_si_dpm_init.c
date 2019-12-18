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
struct rv7xx_power_info {int mclk_strobe_mode_threshold; int mclk_stutter_mode_threshold; int mclk_edc_enable_threshold; int gfx_clock_gating; int thermal_protection; int /*<<< orphan*/  vrc; int /*<<< orphan*/  pasi; int /*<<< orphan*/  asi; void* mvdd_control; void* voltage_control; scalar_t__ ref_div; scalar_t__ max_vddc_in_table; scalar_t__ min_vddc_in_table; scalar_t__ acpi_vddc; } ;
struct evergreen_power_info {int smu_uvd_hs; int mclk_edc_wr_enable_threshold; int sclk_deep_sleep; int dynamic_ac_timing; int light_sleep; int pcie_performance_request; void* vddci_control; scalar_t__ acpi_vddci; struct rv7xx_power_info rv7xx; } ;
struct ni_power_info {int mclk_rtt_mode_threshold; struct evergreen_power_info eg; } ;
struct si_power_info {int sys_pcie_mask; int sclk_deep_sleep_above_low; int fan_ctrl_is_in_default_mode; int /*<<< orphan*/  sram_end; void* vddc_phase_shed_control; void* vddci_control_svi2; int /*<<< orphan*/  svc_gpio_id; int /*<<< orphan*/  svd_gpio_id; void* voltage_control_svi2; int /*<<< orphan*/  boot_pcie_gen; int /*<<< orphan*/  force_pcie_gen; struct ni_power_info ni; } ;
struct atom_clock_dividers {scalar_t__ ref_div; } ;
struct TYPE_11__ {scalar_t__ sclk; scalar_t__ mclk; } ;
struct TYPE_10__ {int /*<<< orphan*/ * values; scalar_t__ count; } ;
struct TYPE_9__ {int /*<<< orphan*/ * values; scalar_t__ count; } ;
struct TYPE_12__ {int count; TYPE_8__* entries; } ;
struct TYPE_14__ {int mclk_sclk_ratio; int sclk_mclk_delta; int vddc_vddci_delta; TYPE_3__ max_clock_voltage_on_ac; TYPE_3__ max_clock_voltage_on_dc; TYPE_2__ valid_mclk_values; TYPE_1__ valid_sclk_values; TYPE_4__ vddc_dependency_on_dispclk; } ;
struct TYPE_13__ {scalar_t__ voltage_response_time; scalar_t__ backbias_response_time; TYPE_6__ dyn_state; struct si_power_info* priv; } ;
struct TYPE_15__ {int pcie_gen_mask; scalar_t__ int_thermal_type; TYPE_5__ dpm; } ;
struct amdgpu_device {TYPE_7__ pm; } ;
struct amdgpu_clock_voltage_dependency_entry {int dummy; } ;
struct TYPE_16__ {int clk; int v; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_PCIE_GEN_INVALID ; 
 int CAIL_PCIE_LINK_SPEED_SUPPORT_MASK ; 
 int /*<<< orphan*/  COMPUTE_ENGINE_PLL_PARAM ; 
 int /*<<< orphan*/  CYPRESS_HASI_DFLT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ R600_BACKBIASRESPONSETIME_DFLT ; 
 scalar_t__ R600_REFERENCEDIVIDER_DFLT ; 
 scalar_t__ R600_VOLTAGERESPONSETIME_DFLT ; 
 int /*<<< orphan*/  RV770_ASI_DFLT ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_MVDDC ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_VDDC ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_VDDCI ; 
 int /*<<< orphan*/  SISLANDS_VRC_DFLT ; 
 int /*<<< orphan*/  SMC_RAM_END ; 
 scalar_t__ THERMAL_TYPE_NONE ; 
 int /*<<< orphan*/  VOLTAGE_OBJ_GPIO_LUT ; 
 int /*<<< orphan*/  VOLTAGE_OBJ_PHASE_LUT ; 
 int /*<<< orphan*/  VOLTAGE_OBJ_SVID2 ; 
 int amdgpu_acpi_is_pcie_performance_request_supported (struct amdgpu_device*) ; 
 int amdgpu_atombios_get_clock_dividers (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct atom_clock_dividers*) ; 
 int /*<<< orphan*/  amdgpu_atombios_get_svi2_info (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* amdgpu_atombios_is_voltage_gpio (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_free_extended_power_table (struct amdgpu_device*) ; 
 int amdgpu_get_platform_caps (struct amdgpu_device*) ; 
 int amdgpu_parse_extended_power_table (struct amdgpu_device*) ; 
 TYPE_8__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct si_power_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv770_get_engine_memory_ss (struct amdgpu_device*) ; 
 int /*<<< orphan*/  rv770_get_max_vddc (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_get_current_pcie_speed (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_get_leakage_vddc (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_initialize_powertune_defaults (struct amdgpu_device*) ; 
 scalar_t__ si_is_special_1gb_platform (struct amdgpu_device*) ; 
 int si_parse_power_table (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_patch_dependency_tables_based_on_leakage (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_set_max_cu_value (struct amdgpu_device*) ; 

__attribute__((used)) static int si_dpm_init(struct amdgpu_device *adev)
{
	struct rv7xx_power_info *pi;
	struct evergreen_power_info *eg_pi;
	struct ni_power_info *ni_pi;
	struct si_power_info *si_pi;
	struct atom_clock_dividers dividers;
	int ret;

	si_pi = kzalloc(sizeof(struct si_power_info), GFP_KERNEL);
	if (si_pi == NULL)
		return -ENOMEM;
	adev->pm.dpm.priv = si_pi;
	ni_pi = &si_pi->ni;
	eg_pi = &ni_pi->eg;
	pi = &eg_pi->rv7xx;

	si_pi->sys_pcie_mask =
		adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_MASK;
	si_pi->force_pcie_gen = AMDGPU_PCIE_GEN_INVALID;
	si_pi->boot_pcie_gen = si_get_current_pcie_speed(adev);

	si_set_max_cu_value(adev);

	rv770_get_max_vddc(adev);
	si_get_leakage_vddc(adev);
	si_patch_dependency_tables_based_on_leakage(adev);

	pi->acpi_vddc = 0;
	eg_pi->acpi_vddci = 0;
	pi->min_vddc_in_table = 0;
	pi->max_vddc_in_table = 0;

	ret = amdgpu_get_platform_caps(adev);
	if (ret)
		return ret;

	ret = amdgpu_parse_extended_power_table(adev);
	if (ret)
		return ret;

	ret = si_parse_power_table(adev);
	if (ret)
		return ret;

	adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries =
		kcalloc(4,
			sizeof(struct amdgpu_clock_voltage_dependency_entry),
			GFP_KERNEL);
	if (!adev->pm.dpm.dyn_state.vddc_dependency_on_dispclk.entries) {
		amdgpu_free_extended_power_table(adev);
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

	if (adev->pm.dpm.voltage_response_time == 0)
		adev->pm.dpm.voltage_response_time = R600_VOLTAGERESPONSETIME_DFLT;
	if (adev->pm.dpm.backbias_response_time == 0)
		adev->pm.dpm.backbias_response_time = R600_BACKBIASRESPONSETIME_DFLT;

	ret = amdgpu_atombios_get_clock_dividers(adev, COMPUTE_ENGINE_PLL_PARAM,
					     0, false, &dividers);
	if (ret)
		pi->ref_div = dividers.ref_div + 1;
	else
		pi->ref_div = R600_REFERENCEDIVIDER_DFLT;

	eg_pi->smu_uvd_hs = false;

	pi->mclk_strobe_mode_threshold = 40000;
	if (si_is_special_1gb_platform(adev))
		pi->mclk_stutter_mode_threshold = 0;
	else
		pi->mclk_stutter_mode_threshold = pi->mclk_strobe_mode_threshold;
	pi->mclk_edc_enable_threshold = 40000;
	eg_pi->mclk_edc_wr_enable_threshold = 40000;

	ni_pi->mclk_rtt_mode_threshold = eg_pi->mclk_edc_wr_enable_threshold;

	pi->voltage_control =
		amdgpu_atombios_is_voltage_gpio(adev, SET_VOLTAGE_TYPE_ASIC_VDDC,
					    VOLTAGE_OBJ_GPIO_LUT);
	if (!pi->voltage_control) {
		si_pi->voltage_control_svi2 =
			amdgpu_atombios_is_voltage_gpio(adev, SET_VOLTAGE_TYPE_ASIC_VDDC,
						    VOLTAGE_OBJ_SVID2);
		if (si_pi->voltage_control_svi2)
			amdgpu_atombios_get_svi2_info(adev, SET_VOLTAGE_TYPE_ASIC_VDDC,
						  &si_pi->svd_gpio_id, &si_pi->svc_gpio_id);
	}

	pi->mvdd_control =
		amdgpu_atombios_is_voltage_gpio(adev, SET_VOLTAGE_TYPE_ASIC_MVDDC,
					    VOLTAGE_OBJ_GPIO_LUT);

	eg_pi->vddci_control =
		amdgpu_atombios_is_voltage_gpio(adev, SET_VOLTAGE_TYPE_ASIC_VDDCI,
					    VOLTAGE_OBJ_GPIO_LUT);
	if (!eg_pi->vddci_control)
		si_pi->vddci_control_svi2 =
			amdgpu_atombios_is_voltage_gpio(adev, SET_VOLTAGE_TYPE_ASIC_VDDCI,
						    VOLTAGE_OBJ_SVID2);

	si_pi->vddc_phase_shed_control =
		amdgpu_atombios_is_voltage_gpio(adev, SET_VOLTAGE_TYPE_ASIC_VDDC,
					    VOLTAGE_OBJ_PHASE_LUT);

	rv770_get_engine_memory_ss(adev);

	pi->asi = RV770_ASI_DFLT;
	pi->pasi = CYPRESS_HASI_DFLT;
	pi->vrc = SISLANDS_VRC_DFLT;

	pi->gfx_clock_gating = true;

	eg_pi->sclk_deep_sleep = true;
	si_pi->sclk_deep_sleep_above_low = false;

	if (adev->pm.int_thermal_type != THERMAL_TYPE_NONE)
		pi->thermal_protection = true;
	else
		pi->thermal_protection = false;

	eg_pi->dynamic_ac_timing = true;

	eg_pi->light_sleep = true;
#if defined(CONFIG_ACPI)
	eg_pi->pcie_performance_request =
		amdgpu_acpi_is_pcie_performance_request_supported(adev);
#else
	eg_pi->pcie_performance_request = false;
#endif

	si_pi->sram_end = SMC_RAM_END;

	adev->pm.dpm.dyn_state.mclk_sclk_ratio = 4;
	adev->pm.dpm.dyn_state.sclk_mclk_delta = 15000;
	adev->pm.dpm.dyn_state.vddc_vddci_delta = 200;
	adev->pm.dpm.dyn_state.valid_sclk_values.count = 0;
	adev->pm.dpm.dyn_state.valid_sclk_values.values = NULL;
	adev->pm.dpm.dyn_state.valid_mclk_values.count = 0;
	adev->pm.dpm.dyn_state.valid_mclk_values.values = NULL;

	si_initialize_powertune_defaults(adev);

	/* make sure dc limits are valid */
	if ((adev->pm.dpm.dyn_state.max_clock_voltage_on_dc.sclk == 0) ||
	    (adev->pm.dpm.dyn_state.max_clock_voltage_on_dc.mclk == 0))
		adev->pm.dpm.dyn_state.max_clock_voltage_on_dc =
			adev->pm.dpm.dyn_state.max_clock_voltage_on_ac;

	si_pi->fan_ctrl_is_in_default_mode = true;

	return 0;
}