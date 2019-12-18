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
struct radeon_ps {int dummy; } ;
struct TYPE_3__ {struct radeon_ps* boot_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;
struct ci_power_info {scalar_t__ voltage_control; int caps_dynamic_ac_timing; scalar_t__ thermal_protection; scalar_t__ dynamic_ss; } ;

/* Variables and functions */
 scalar_t__ CISLANDS_VOLTAGE_CONTROL_NONE ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  RADEON_DPM_AUTO_THROTTLE_SRC_THERMAL ; 
 int ci_construct_voltage_tables (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_dpm_start_smc (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_enable_auto_throttle_source (struct radeon_device*,int /*<<< orphan*/ ,int) ; 
 int ci_enable_didt (struct radeon_device*,int) ; 
 int /*<<< orphan*/  ci_enable_display_gap (struct radeon_device*) ; 
 int ci_enable_ds_master_switch (struct radeon_device*,int) ; 
 int ci_enable_power_containment (struct radeon_device*,int) ; 
 int /*<<< orphan*/  ci_enable_sclk_control (struct radeon_device*,int) ; 
 int ci_enable_smc_cac (struct radeon_device*,int) ; 
 int /*<<< orphan*/  ci_enable_spread_spectrum (struct radeon_device*,int) ; 
 int ci_enable_thermal_based_sclk_dpm (struct radeon_device*,int) ; 
 int /*<<< orphan*/  ci_enable_thermal_protection (struct radeon_device*,int) ; 
 int ci_enable_ulv (struct radeon_device*,int) ; 
 int /*<<< orphan*/  ci_enable_voltage_control (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_enable_vr_hot_gpio_interrupt (struct radeon_device*) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 int ci_init_arb_table_index (struct radeon_device*) ; 
 int ci_init_smc_table (struct radeon_device*) ; 
 int ci_initial_switch_from_arb_f0_to_f1 (struct radeon_device*) ; 
 int ci_initialize_mc_reg_table (struct radeon_device*) ; 
 scalar_t__ ci_is_smc_running (struct radeon_device*) ; 
 int ci_notify_smc_display_change (struct radeon_device*,int) ; 
 int ci_populate_initial_mc_reg_table (struct radeon_device*) ; 
 int ci_populate_pm_base (struct radeon_device*) ; 
 int ci_power_control_set_level (struct radeon_device*) ; 
 int ci_process_firmware_header (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_program_sstp (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_program_vc (struct radeon_device*) ; 
 int ci_start_dpm (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_thermal_start_thermal_controller (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_update_current_ps (struct radeon_device*,struct radeon_ps*) ; 
 int ci_upload_firmware (struct radeon_device*) ; 

int ci_dpm_enable(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	struct radeon_ps *boot_ps = rdev->pm.dpm.boot_ps;
	int ret;

	if (ci_is_smc_running(rdev))
		return -EINVAL;
	if (pi->voltage_control != CISLANDS_VOLTAGE_CONTROL_NONE) {
		ci_enable_voltage_control(rdev);
		ret = ci_construct_voltage_tables(rdev);
		if (ret) {
			DRM_ERROR("ci_construct_voltage_tables failed\n");
			return ret;
		}
	}
	if (pi->caps_dynamic_ac_timing) {
		ret = ci_initialize_mc_reg_table(rdev);
		if (ret)
			pi->caps_dynamic_ac_timing = false;
	}
	if (pi->dynamic_ss)
		ci_enable_spread_spectrum(rdev, true);
	if (pi->thermal_protection)
		ci_enable_thermal_protection(rdev, true);
	ci_program_sstp(rdev);
	ci_enable_display_gap(rdev);
	ci_program_vc(rdev);
	ret = ci_upload_firmware(rdev);
	if (ret) {
		DRM_ERROR("ci_upload_firmware failed\n");
		return ret;
	}
	ret = ci_process_firmware_header(rdev);
	if (ret) {
		DRM_ERROR("ci_process_firmware_header failed\n");
		return ret;
	}
	ret = ci_initial_switch_from_arb_f0_to_f1(rdev);
	if (ret) {
		DRM_ERROR("ci_initial_switch_from_arb_f0_to_f1 failed\n");
		return ret;
	}
	ret = ci_init_smc_table(rdev);
	if (ret) {
		DRM_ERROR("ci_init_smc_table failed\n");
		return ret;
	}
	ret = ci_init_arb_table_index(rdev);
	if (ret) {
		DRM_ERROR("ci_init_arb_table_index failed\n");
		return ret;
	}
	if (pi->caps_dynamic_ac_timing) {
		ret = ci_populate_initial_mc_reg_table(rdev);
		if (ret) {
			DRM_ERROR("ci_populate_initial_mc_reg_table failed\n");
			return ret;
		}
	}
	ret = ci_populate_pm_base(rdev);
	if (ret) {
		DRM_ERROR("ci_populate_pm_base failed\n");
		return ret;
	}
	ci_dpm_start_smc(rdev);
	ci_enable_vr_hot_gpio_interrupt(rdev);
	ret = ci_notify_smc_display_change(rdev, false);
	if (ret) {
		DRM_ERROR("ci_notify_smc_display_change failed\n");
		return ret;
	}
	ci_enable_sclk_control(rdev, true);
	ret = ci_enable_ulv(rdev, true);
	if (ret) {
		DRM_ERROR("ci_enable_ulv failed\n");
		return ret;
	}
	ret = ci_enable_ds_master_switch(rdev, true);
	if (ret) {
		DRM_ERROR("ci_enable_ds_master_switch failed\n");
		return ret;
	}
	ret = ci_start_dpm(rdev);
	if (ret) {
		DRM_ERROR("ci_start_dpm failed\n");
		return ret;
	}
	ret = ci_enable_didt(rdev, true);
	if (ret) {
		DRM_ERROR("ci_enable_didt failed\n");
		return ret;
	}
	ret = ci_enable_smc_cac(rdev, true);
	if (ret) {
		DRM_ERROR("ci_enable_smc_cac failed\n");
		return ret;
	}
	ret = ci_enable_power_containment(rdev, true);
	if (ret) {
		DRM_ERROR("ci_enable_power_containment failed\n");
		return ret;
	}

	ret = ci_power_control_set_level(rdev);
	if (ret) {
		DRM_ERROR("ci_power_control_set_level failed\n");
		return ret;
	}

	ci_enable_auto_throttle_source(rdev, RADEON_DPM_AUTO_THROTTLE_SRC_THERMAL, true);

	ret = ci_enable_thermal_based_sclk_dpm(rdev, true);
	if (ret) {
		DRM_ERROR("ci_enable_thermal_based_sclk_dpm failed\n");
		return ret;
	}

	ci_thermal_start_thermal_controller(rdev);

	ci_update_current_ps(rdev, boot_ps);

	return 0;
}