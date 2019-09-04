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
struct ci_power_info {scalar_t__ voltage_control; int caps_dynamic_ac_timing; scalar_t__ thermal_protection; scalar_t__ dynamic_ss; } ;
struct amdgpu_ps {int dummy; } ;
struct TYPE_3__ {struct amdgpu_ps* boot_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct amdgpu_device {TYPE_2__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_DPM_AUTO_THROTTLE_SRC_THERMAL ; 
 scalar_t__ CISLANDS_VOLTAGE_CONTROL_NONE ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ci_construct_voltage_tables (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_dpm_start_smc (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_enable_auto_throttle_source (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 int ci_enable_didt (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  ci_enable_display_gap (struct amdgpu_device*) ; 
 int ci_enable_ds_master_switch (struct amdgpu_device*,int) ; 
 int ci_enable_power_containment (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  ci_enable_sclk_control (struct amdgpu_device*,int) ; 
 int ci_enable_smc_cac (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  ci_enable_spread_spectrum (struct amdgpu_device*,int) ; 
 int ci_enable_thermal_based_sclk_dpm (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  ci_enable_thermal_protection (struct amdgpu_device*,int) ; 
 int ci_enable_ulv (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  ci_enable_voltage_control (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_enable_vr_hot_gpio_interrupt (struct amdgpu_device*) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 int ci_init_arb_table_index (struct amdgpu_device*) ; 
 int ci_init_smc_table (struct amdgpu_device*) ; 
 int ci_initial_switch_from_arb_f0_to_f1 (struct amdgpu_device*) ; 
 int ci_initialize_mc_reg_table (struct amdgpu_device*) ; 
 int ci_notify_smc_display_change (struct amdgpu_device*,int) ; 
 int ci_populate_initial_mc_reg_table (struct amdgpu_device*) ; 
 int ci_populate_pm_base (struct amdgpu_device*) ; 
 int ci_power_control_set_level (struct amdgpu_device*) ; 
 int ci_process_firmware_header (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_program_sstp (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_program_vc (struct amdgpu_device*) ; 
 int ci_start_dpm (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_thermal_start_thermal_controller (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_update_current_ps (struct amdgpu_device*,struct amdgpu_ps*) ; 
 int ci_upload_firmware (struct amdgpu_device*) ; 

__attribute__((used)) static int ci_dpm_enable(struct amdgpu_device *adev)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	struct amdgpu_ps *boot_ps = adev->pm.dpm.boot_ps;
	int ret;

	if (pi->voltage_control != CISLANDS_VOLTAGE_CONTROL_NONE) {
		ci_enable_voltage_control(adev);
		ret = ci_construct_voltage_tables(adev);
		if (ret) {
			DRM_ERROR("ci_construct_voltage_tables failed\n");
			return ret;
		}
	}
	if (pi->caps_dynamic_ac_timing) {
		ret = ci_initialize_mc_reg_table(adev);
		if (ret)
			pi->caps_dynamic_ac_timing = false;
	}
	if (pi->dynamic_ss)
		ci_enable_spread_spectrum(adev, true);
	if (pi->thermal_protection)
		ci_enable_thermal_protection(adev, true);
	ci_program_sstp(adev);
	ci_enable_display_gap(adev);
	ci_program_vc(adev);
	ret = ci_upload_firmware(adev);
	if (ret) {
		DRM_ERROR("ci_upload_firmware failed\n");
		return ret;
	}
	ret = ci_process_firmware_header(adev);
	if (ret) {
		DRM_ERROR("ci_process_firmware_header failed\n");
		return ret;
	}
	ret = ci_initial_switch_from_arb_f0_to_f1(adev);
	if (ret) {
		DRM_ERROR("ci_initial_switch_from_arb_f0_to_f1 failed\n");
		return ret;
	}
	ret = ci_init_smc_table(adev);
	if (ret) {
		DRM_ERROR("ci_init_smc_table failed\n");
		return ret;
	}
	ret = ci_init_arb_table_index(adev);
	if (ret) {
		DRM_ERROR("ci_init_arb_table_index failed\n");
		return ret;
	}
	if (pi->caps_dynamic_ac_timing) {
		ret = ci_populate_initial_mc_reg_table(adev);
		if (ret) {
			DRM_ERROR("ci_populate_initial_mc_reg_table failed\n");
			return ret;
		}
	}
	ret = ci_populate_pm_base(adev);
	if (ret) {
		DRM_ERROR("ci_populate_pm_base failed\n");
		return ret;
	}
	ci_dpm_start_smc(adev);
	ci_enable_vr_hot_gpio_interrupt(adev);
	ret = ci_notify_smc_display_change(adev, false);
	if (ret) {
		DRM_ERROR("ci_notify_smc_display_change failed\n");
		return ret;
	}
	ci_enable_sclk_control(adev, true);
	ret = ci_enable_ulv(adev, true);
	if (ret) {
		DRM_ERROR("ci_enable_ulv failed\n");
		return ret;
	}
	ret = ci_enable_ds_master_switch(adev, true);
	if (ret) {
		DRM_ERROR("ci_enable_ds_master_switch failed\n");
		return ret;
	}
	ret = ci_start_dpm(adev);
	if (ret) {
		DRM_ERROR("ci_start_dpm failed\n");
		return ret;
	}
	ret = ci_enable_didt(adev, true);
	if (ret) {
		DRM_ERROR("ci_enable_didt failed\n");
		return ret;
	}
	ret = ci_enable_smc_cac(adev, true);
	if (ret) {
		DRM_ERROR("ci_enable_smc_cac failed\n");
		return ret;
	}
	ret = ci_enable_power_containment(adev, true);
	if (ret) {
		DRM_ERROR("ci_enable_power_containment failed\n");
		return ret;
	}

	ret = ci_power_control_set_level(adev);
	if (ret) {
		DRM_ERROR("ci_power_control_set_level failed\n");
		return ret;
	}

	ci_enable_auto_throttle_source(adev, AMDGPU_DPM_AUTO_THROTTLE_SRC_THERMAL, true);

	ret = ci_enable_thermal_based_sclk_dpm(adev, true);
	if (ret) {
		DRM_ERROR("ci_enable_thermal_based_sclk_dpm failed\n");
		return ret;
	}

	ci_thermal_start_thermal_controller(adev);

	ci_update_current_ps(adev, boot_ps);

	return 0;
}