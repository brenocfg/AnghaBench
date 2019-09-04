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
struct rv7xx_power_info {scalar_t__ mg_clock_gating; scalar_t__ gfx_clock_gating; scalar_t__ dynamic_pcie_gen2; scalar_t__ thermal_protection; scalar_t__ dynamic_ss; scalar_t__ voltage_control; } ;
struct radeon_ps {int dummy; } ;
struct TYPE_3__ {struct radeon_ps* boot_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;
struct evergreen_power_info {int dynamic_ac_timing; scalar_t__ ls_clock_gating; scalar_t__ memory_transition; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  RADEON_DPM_AUTO_THROTTLE_SRC_THERMAL ; 
 scalar_t__ btc_dpm_enabled (struct radeon_device*) ; 
 int cypress_construct_voltage_tables (struct radeon_device*) ; 
 int /*<<< orphan*/  cypress_enable_display_gap (struct radeon_device*) ; 
 int /*<<< orphan*/  cypress_enable_mclk_control (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cypress_enable_sclk_control (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cypress_enable_spread_spectrum (struct radeon_device*,int) ; 
 int cypress_notify_smc_display_change (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cypress_start_dpm (struct radeon_device*) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  ni_cg_clockgating_default (struct radeon_device*) ; 
 int /*<<< orphan*/  ni_enable_dynamic_pcie_gen2 (struct radeon_device*,int) ; 
 int /*<<< orphan*/  ni_gfx_clockgating_enable (struct radeon_device*,int) ; 
 int ni_init_arb_table_index (struct radeon_device*) ; 
 int ni_init_smc_spll_table (struct radeon_device*) ; 
 int ni_init_smc_table (struct radeon_device*) ; 
 int ni_initial_switch_from_arb_f0_to_f1 (struct radeon_device*) ; 
 int ni_initialize_hardware_cac_manager (struct radeon_device*) ; 
 int ni_initialize_mc_reg_table (struct radeon_device*) ; 
 int ni_initialize_smc_cac_tables (struct radeon_device*) ; 
 int /*<<< orphan*/  ni_ls_clockgating_default (struct radeon_device*) ; 
 int /*<<< orphan*/  ni_ls_clockgating_enable (struct radeon_device*,int) ; 
 int /*<<< orphan*/  ni_mg_clockgating_default (struct radeon_device*) ; 
 int /*<<< orphan*/  ni_mg_clockgating_enable (struct radeon_device*,int) ; 
 int ni_populate_mc_reg_table (struct radeon_device*,struct radeon_ps*) ; 
 int ni_populate_smc_tdp_limits (struct radeon_device*,struct radeon_ps*) ; 
 int ni_process_firmware_header (struct radeon_device*) ; 
 int /*<<< orphan*/  ni_program_response_times (struct radeon_device*) ; 
 int /*<<< orphan*/  ni_update_current_ps (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  r7xx_start_smc (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_enable_auto_throttle_source (struct radeon_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rv770_enable_thermal_protection (struct radeon_device*,int) ; 
 int /*<<< orphan*/  rv770_enable_voltage_control (struct radeon_device*,int) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_program_git (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_program_sstp (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_program_tp (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_program_tpp (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_program_vc (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_setup_bsp (struct radeon_device*) ; 
 int rv770_upload_firmware (struct radeon_device*) ; 

int ni_dpm_enable(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct radeon_ps *boot_ps = rdev->pm.dpm.boot_ps;
	int ret;

	if (pi->gfx_clock_gating)
		ni_cg_clockgating_default(rdev);
	if (btc_dpm_enabled(rdev))
		return -EINVAL;
	if (pi->mg_clock_gating)
		ni_mg_clockgating_default(rdev);
	if (eg_pi->ls_clock_gating)
		ni_ls_clockgating_default(rdev);
	if (pi->voltage_control) {
		rv770_enable_voltage_control(rdev, true);
		ret = cypress_construct_voltage_tables(rdev);
		if (ret) {
			DRM_ERROR("cypress_construct_voltage_tables failed\n");
			return ret;
		}
	}
	if (eg_pi->dynamic_ac_timing) {
		ret = ni_initialize_mc_reg_table(rdev);
		if (ret)
			eg_pi->dynamic_ac_timing = false;
	}
	if (pi->dynamic_ss)
		cypress_enable_spread_spectrum(rdev, true);
	if (pi->thermal_protection)
		rv770_enable_thermal_protection(rdev, true);
	rv770_setup_bsp(rdev);
	rv770_program_git(rdev);
	rv770_program_tp(rdev);
	rv770_program_tpp(rdev);
	rv770_program_sstp(rdev);
	cypress_enable_display_gap(rdev);
	rv770_program_vc(rdev);
	if (pi->dynamic_pcie_gen2)
		ni_enable_dynamic_pcie_gen2(rdev, true);
	ret = rv770_upload_firmware(rdev);
	if (ret) {
		DRM_ERROR("rv770_upload_firmware failed\n");
		return ret;
	}
	ret = ni_process_firmware_header(rdev);
	if (ret) {
		DRM_ERROR("ni_process_firmware_header failed\n");
		return ret;
	}
	ret = ni_initial_switch_from_arb_f0_to_f1(rdev);
	if (ret) {
		DRM_ERROR("ni_initial_switch_from_arb_f0_to_f1 failed\n");
		return ret;
	}
	ret = ni_init_smc_table(rdev);
	if (ret) {
		DRM_ERROR("ni_init_smc_table failed\n");
		return ret;
	}
	ret = ni_init_smc_spll_table(rdev);
	if (ret) {
		DRM_ERROR("ni_init_smc_spll_table failed\n");
		return ret;
	}
	ret = ni_init_arb_table_index(rdev);
	if (ret) {
		DRM_ERROR("ni_init_arb_table_index failed\n");
		return ret;
	}
	if (eg_pi->dynamic_ac_timing) {
		ret = ni_populate_mc_reg_table(rdev, boot_ps);
		if (ret) {
			DRM_ERROR("ni_populate_mc_reg_table failed\n");
			return ret;
		}
	}
	ret = ni_initialize_smc_cac_tables(rdev);
	if (ret) {
		DRM_ERROR("ni_initialize_smc_cac_tables failed\n");
		return ret;
	}
	ret = ni_initialize_hardware_cac_manager(rdev);
	if (ret) {
		DRM_ERROR("ni_initialize_hardware_cac_manager failed\n");
		return ret;
	}
	ret = ni_populate_smc_tdp_limits(rdev, boot_ps);
	if (ret) {
		DRM_ERROR("ni_populate_smc_tdp_limits failed\n");
		return ret;
	}
	ni_program_response_times(rdev);
	r7xx_start_smc(rdev);
	ret = cypress_notify_smc_display_change(rdev, false);
	if (ret) {
		DRM_ERROR("cypress_notify_smc_display_change failed\n");
		return ret;
	}
	cypress_enable_sclk_control(rdev, true);
	if (eg_pi->memory_transition)
		cypress_enable_mclk_control(rdev, true);
	cypress_start_dpm(rdev);
	if (pi->gfx_clock_gating)
		ni_gfx_clockgating_enable(rdev, true);
	if (pi->mg_clock_gating)
		ni_mg_clockgating_enable(rdev, true);
	if (eg_pi->ls_clock_gating)
		ni_ls_clockgating_enable(rdev, true);

	rv770_enable_auto_throttle_source(rdev, RADEON_DPM_AUTO_THROTTLE_SRC_THERMAL, true);

	ni_update_current_ps(rdev, boot_ps);

	return 0;
}