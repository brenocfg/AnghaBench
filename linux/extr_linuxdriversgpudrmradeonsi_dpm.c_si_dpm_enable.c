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
struct radeon_ps {int dummy; } ;
struct TYPE_3__ {struct radeon_ps* boot_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;
struct evergreen_power_info {int dynamic_ac_timing; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  RADEON_DPM_AUTO_THROTTLE_SRC_THERMAL ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  ni_update_current_ps (struct radeon_device*,struct radeon_ps*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 int si_construct_voltage_tables (struct radeon_device*) ; 
 int /*<<< orphan*/  si_dpm_start_smc (struct radeon_device*) ; 
 int /*<<< orphan*/  si_enable_auto_throttle_source (struct radeon_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  si_enable_display_gap (struct radeon_device*) ; 
 int /*<<< orphan*/  si_enable_sclk_control (struct radeon_device*,int) ; 
 int /*<<< orphan*/  si_enable_spread_spectrum (struct radeon_device*,int) ; 
 int /*<<< orphan*/  si_enable_thermal_protection (struct radeon_device*,int) ; 
 int /*<<< orphan*/  si_enable_voltage_control (struct radeon_device*,int) ; 
 int /*<<< orphan*/  si_get_mvdd_configuration (struct radeon_device*) ; 
 struct si_power_info* si_get_pi (struct radeon_device*) ; 
 int si_init_arb_table_index (struct radeon_device*) ; 
 int si_init_smc_spll_table (struct radeon_device*) ; 
 int si_init_smc_table (struct radeon_device*) ; 
 int si_initial_switch_from_arb_f0_to_f1 (struct radeon_device*) ; 
 int si_initialize_hardware_cac_manager (struct radeon_device*) ; 
 int si_initialize_mc_reg_table (struct radeon_device*) ; 
 int si_initialize_smc_cac_tables (struct radeon_device*) ; 
 int si_initialize_smc_dte_tables (struct radeon_device*) ; 
 scalar_t__ si_is_smc_running (struct radeon_device*) ; 
 int si_notify_smc_display_change (struct radeon_device*,int) ; 
 int si_populate_mc_reg_table (struct radeon_device*,struct radeon_ps*) ; 
 int si_populate_smc_tdp_limits (struct radeon_device*,struct radeon_ps*) ; 
 int si_populate_smc_tdp_limits_2 (struct radeon_device*,struct radeon_ps*) ; 
 int si_process_firmware_header (struct radeon_device*) ; 
 int /*<<< orphan*/  si_program_ds_registers (struct radeon_device*) ; 
 int /*<<< orphan*/  si_program_git (struct radeon_device*) ; 
 int /*<<< orphan*/  si_program_response_times (struct radeon_device*) ; 
 int /*<<< orphan*/  si_program_sstp (struct radeon_device*) ; 
 int /*<<< orphan*/  si_program_tp (struct radeon_device*) ; 
 int /*<<< orphan*/  si_program_tpp (struct radeon_device*) ; 
 int /*<<< orphan*/  si_program_vc (struct radeon_device*) ; 
 int /*<<< orphan*/  si_setup_bsp (struct radeon_device*) ; 
 int /*<<< orphan*/  si_start_dpm (struct radeon_device*) ; 
 int /*<<< orphan*/  si_thermal_start_thermal_controller (struct radeon_device*) ; 
 int si_upload_firmware (struct radeon_device*) ; 

int si_dpm_enable(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct si_power_info *si_pi = si_get_pi(rdev);
	struct radeon_ps *boot_ps = rdev->pm.dpm.boot_ps;
	int ret;

	if (si_is_smc_running(rdev))
		return -EINVAL;
	if (pi->voltage_control || si_pi->voltage_control_svi2)
		si_enable_voltage_control(rdev, true);
	if (pi->mvdd_control)
		si_get_mvdd_configuration(rdev);
	if (pi->voltage_control || si_pi->voltage_control_svi2) {
		ret = si_construct_voltage_tables(rdev);
		if (ret) {
			DRM_ERROR("si_construct_voltage_tables failed\n");
			return ret;
		}
	}
	if (eg_pi->dynamic_ac_timing) {
		ret = si_initialize_mc_reg_table(rdev);
		if (ret)
			eg_pi->dynamic_ac_timing = false;
	}
	if (pi->dynamic_ss)
		si_enable_spread_spectrum(rdev, true);
	if (pi->thermal_protection)
		si_enable_thermal_protection(rdev, true);
	si_setup_bsp(rdev);
	si_program_git(rdev);
	si_program_tp(rdev);
	si_program_tpp(rdev);
	si_program_sstp(rdev);
	si_enable_display_gap(rdev);
	si_program_vc(rdev);
	ret = si_upload_firmware(rdev);
	if (ret) {
		DRM_ERROR("si_upload_firmware failed\n");
		return ret;
	}
	ret = si_process_firmware_header(rdev);
	if (ret) {
		DRM_ERROR("si_process_firmware_header failed\n");
		return ret;
	}
	ret = si_initial_switch_from_arb_f0_to_f1(rdev);
	if (ret) {
		DRM_ERROR("si_initial_switch_from_arb_f0_to_f1 failed\n");
		return ret;
	}
	ret = si_init_smc_table(rdev);
	if (ret) {
		DRM_ERROR("si_init_smc_table failed\n");
		return ret;
	}
	ret = si_init_smc_spll_table(rdev);
	if (ret) {
		DRM_ERROR("si_init_smc_spll_table failed\n");
		return ret;
	}
	ret = si_init_arb_table_index(rdev);
	if (ret) {
		DRM_ERROR("si_init_arb_table_index failed\n");
		return ret;
	}
	if (eg_pi->dynamic_ac_timing) {
		ret = si_populate_mc_reg_table(rdev, boot_ps);
		if (ret) {
			DRM_ERROR("si_populate_mc_reg_table failed\n");
			return ret;
		}
	}
	ret = si_initialize_smc_cac_tables(rdev);
	if (ret) {
		DRM_ERROR("si_initialize_smc_cac_tables failed\n");
		return ret;
	}
	ret = si_initialize_hardware_cac_manager(rdev);
	if (ret) {
		DRM_ERROR("si_initialize_hardware_cac_manager failed\n");
		return ret;
	}
	ret = si_initialize_smc_dte_tables(rdev);
	if (ret) {
		DRM_ERROR("si_initialize_smc_dte_tables failed\n");
		return ret;
	}
	ret = si_populate_smc_tdp_limits(rdev, boot_ps);
	if (ret) {
		DRM_ERROR("si_populate_smc_tdp_limits failed\n");
		return ret;
	}
	ret = si_populate_smc_tdp_limits_2(rdev, boot_ps);
	if (ret) {
		DRM_ERROR("si_populate_smc_tdp_limits_2 failed\n");
		return ret;
	}
	si_program_response_times(rdev);
	si_program_ds_registers(rdev);
	si_dpm_start_smc(rdev);
	ret = si_notify_smc_display_change(rdev, false);
	if (ret) {
		DRM_ERROR("si_notify_smc_display_change failed\n");
		return ret;
	}
	si_enable_sclk_control(rdev, true);
	si_start_dpm(rdev);

	si_enable_auto_throttle_source(rdev, RADEON_DPM_AUTO_THROTTLE_SRC_THERMAL, true);

	si_thermal_start_thermal_controller(rdev);

	ni_update_current_ps(rdev, boot_ps);

	return 0;
}