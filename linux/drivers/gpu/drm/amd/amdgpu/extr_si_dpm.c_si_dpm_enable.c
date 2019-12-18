#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct si_power_info {scalar_t__ voltage_control_svi2; } ;
struct rv7xx_power_info {scalar_t__ thermal_protection; scalar_t__ dynamic_ss; scalar_t__ voltage_control; scalar_t__ mvdd_control; } ;
struct evergreen_power_info {int dynamic_ac_timing; } ;
struct amdgpu_ps {int dummy; } ;
struct TYPE_3__ {struct amdgpu_ps* boot_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct amdgpu_device {TYPE_2__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_DPM_AUTO_THROTTLE_SRC_THERMAL ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 scalar_t__ amdgpu_si_is_smc_running (struct amdgpu_device*) ; 
 struct evergreen_power_info* evergreen_get_pi (struct amdgpu_device*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct amdgpu_device*) ; 
 int si_construct_voltage_tables (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_dpm_start_smc (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_enable_auto_throttle_source (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  si_enable_display_gap (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_enable_sclk_control (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  si_enable_spread_spectrum (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  si_enable_thermal_protection (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  si_enable_voltage_control (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  si_get_mvdd_configuration (struct amdgpu_device*) ; 
 struct si_power_info* si_get_pi (struct amdgpu_device*) ; 
 int si_init_arb_table_index (struct amdgpu_device*) ; 
 int si_init_smc_spll_table (struct amdgpu_device*) ; 
 int si_init_smc_table (struct amdgpu_device*) ; 
 int si_initial_switch_from_arb_f0_to_f1 (struct amdgpu_device*) ; 
 int si_initialize_hardware_cac_manager (struct amdgpu_device*) ; 
 int si_initialize_mc_reg_table (struct amdgpu_device*) ; 
 int si_initialize_smc_cac_tables (struct amdgpu_device*) ; 
 int si_initialize_smc_dte_tables (struct amdgpu_device*) ; 
 int si_notify_smc_display_change (struct amdgpu_device*,int) ; 
 int si_populate_mc_reg_table (struct amdgpu_device*,struct amdgpu_ps*) ; 
 int si_populate_smc_tdp_limits (struct amdgpu_device*,struct amdgpu_ps*) ; 
 int si_populate_smc_tdp_limits_2 (struct amdgpu_device*,struct amdgpu_ps*) ; 
 int si_process_firmware_header (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_program_ds_registers (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_program_git (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_program_response_times (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_program_sstp (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_program_tp (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_program_tpp (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_program_vc (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_setup_bsp (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_start_dpm (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_thermal_start_thermal_controller (struct amdgpu_device*) ; 
 int si_upload_firmware (struct amdgpu_device*) ; 

__attribute__((used)) static int si_dpm_enable(struct amdgpu_device *adev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(adev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(adev);
	struct si_power_info *si_pi = si_get_pi(adev);
	struct amdgpu_ps *boot_ps = adev->pm.dpm.boot_ps;
	int ret;

	if (amdgpu_si_is_smc_running(adev))
		return -EINVAL;
	if (pi->voltage_control || si_pi->voltage_control_svi2)
		si_enable_voltage_control(adev, true);
	if (pi->mvdd_control)
		si_get_mvdd_configuration(adev);
	if (pi->voltage_control || si_pi->voltage_control_svi2) {
		ret = si_construct_voltage_tables(adev);
		if (ret) {
			DRM_ERROR("si_construct_voltage_tables failed\n");
			return ret;
		}
	}
	if (eg_pi->dynamic_ac_timing) {
		ret = si_initialize_mc_reg_table(adev);
		if (ret)
			eg_pi->dynamic_ac_timing = false;
	}
	if (pi->dynamic_ss)
		si_enable_spread_spectrum(adev, true);
	if (pi->thermal_protection)
		si_enable_thermal_protection(adev, true);
	si_setup_bsp(adev);
	si_program_git(adev);
	si_program_tp(adev);
	si_program_tpp(adev);
	si_program_sstp(adev);
	si_enable_display_gap(adev);
	si_program_vc(adev);
	ret = si_upload_firmware(adev);
	if (ret) {
		DRM_ERROR("si_upload_firmware failed\n");
		return ret;
	}
	ret = si_process_firmware_header(adev);
	if (ret) {
		DRM_ERROR("si_process_firmware_header failed\n");
		return ret;
	}
	ret = si_initial_switch_from_arb_f0_to_f1(adev);
	if (ret) {
		DRM_ERROR("si_initial_switch_from_arb_f0_to_f1 failed\n");
		return ret;
	}
	ret = si_init_smc_table(adev);
	if (ret) {
		DRM_ERROR("si_init_smc_table failed\n");
		return ret;
	}
	ret = si_init_smc_spll_table(adev);
	if (ret) {
		DRM_ERROR("si_init_smc_spll_table failed\n");
		return ret;
	}
	ret = si_init_arb_table_index(adev);
	if (ret) {
		DRM_ERROR("si_init_arb_table_index failed\n");
		return ret;
	}
	if (eg_pi->dynamic_ac_timing) {
		ret = si_populate_mc_reg_table(adev, boot_ps);
		if (ret) {
			DRM_ERROR("si_populate_mc_reg_table failed\n");
			return ret;
		}
	}
	ret = si_initialize_smc_cac_tables(adev);
	if (ret) {
		DRM_ERROR("si_initialize_smc_cac_tables failed\n");
		return ret;
	}
	ret = si_initialize_hardware_cac_manager(adev);
	if (ret) {
		DRM_ERROR("si_initialize_hardware_cac_manager failed\n");
		return ret;
	}
	ret = si_initialize_smc_dte_tables(adev);
	if (ret) {
		DRM_ERROR("si_initialize_smc_dte_tables failed\n");
		return ret;
	}
	ret = si_populate_smc_tdp_limits(adev, boot_ps);
	if (ret) {
		DRM_ERROR("si_populate_smc_tdp_limits failed\n");
		return ret;
	}
	ret = si_populate_smc_tdp_limits_2(adev, boot_ps);
	if (ret) {
		DRM_ERROR("si_populate_smc_tdp_limits_2 failed\n");
		return ret;
	}
	si_program_response_times(adev);
	si_program_ds_registers(adev);
	si_dpm_start_smc(adev);
	ret = si_notify_smc_display_change(adev, false);
	if (ret) {
		DRM_ERROR("si_notify_smc_display_change failed\n");
		return ret;
	}
	si_enable_sclk_control(adev, true);
	si_start_dpm(adev);

	si_enable_auto_throttle_source(adev, AMDGPU_DPM_AUTO_THROTTLE_SRC_THERMAL, true);
	si_thermal_start_thermal_controller(adev);

	return 0;
}