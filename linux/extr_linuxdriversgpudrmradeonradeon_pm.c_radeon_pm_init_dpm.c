#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  work; } ;
struct TYPE_7__ {int /*<<< orphan*/  boot_ps; int /*<<< orphan*/  requested_ps; int /*<<< orphan*/  current_ps; TYPE_2__ thermal; int /*<<< orphan*/  forced_level; void* user_state; void* state; } ;
struct TYPE_8__ {int dpm_enabled; scalar_t__ default_mclk; scalar_t__ default_sclk; scalar_t__ default_vddci; scalar_t__ default_vddc; int /*<<< orphan*/  mutex; TYPE_3__ dpm; int /*<<< orphan*/  int_thermal_type; scalar_t__ current_mclk; scalar_t__ current_sclk; } ;
struct TYPE_5__ {scalar_t__ default_mclk; scalar_t__ default_sclk; } ;
struct radeon_device {scalar_t__ family; TYPE_4__ pm; scalar_t__ mc_fw; scalar_t__ is_atom_bios; scalar_t__ bios; TYPE_1__ clock; } ;

/* Variables and functions */
 scalar_t__ CHIP_BARTS ; 
 scalar_t__ CHIP_CAYMAN ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* POWER_STATE_TYPE_BALANCED ; 
 int /*<<< orphan*/  RADEON_DPM_FORCED_LEVEL_AUTO ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_VDDC ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_VDDCI ; 
 int /*<<< orphan*/  THERMAL_TYPE_NONE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_atom_set_voltage (struct radeon_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_atombios_get_power_modes (struct radeon_device*) ; 
 scalar_t__ radeon_debugfs_pm_init (struct radeon_device*) ; 
 int radeon_dpm ; 
 int radeon_dpm_enable (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_dpm_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_dpm_print_power_states (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_dpm_setup_asic (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_dpm_thermal_work_handler ; 
 int radeon_hwmon_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_set_engine_clock (struct radeon_device*,scalar_t__) ; 
 int /*<<< orphan*/  radeon_set_memory_clock (struct radeon_device*,scalar_t__) ; 

__attribute__((used)) static int radeon_pm_init_dpm(struct radeon_device *rdev)
{
	int ret;

	/* default to balanced state */
	rdev->pm.dpm.state = POWER_STATE_TYPE_BALANCED;
	rdev->pm.dpm.user_state = POWER_STATE_TYPE_BALANCED;
	rdev->pm.dpm.forced_level = RADEON_DPM_FORCED_LEVEL_AUTO;
	rdev->pm.default_sclk = rdev->clock.default_sclk;
	rdev->pm.default_mclk = rdev->clock.default_mclk;
	rdev->pm.current_sclk = rdev->clock.default_sclk;
	rdev->pm.current_mclk = rdev->clock.default_mclk;
	rdev->pm.int_thermal_type = THERMAL_TYPE_NONE;

	if (rdev->bios && rdev->is_atom_bios)
		radeon_atombios_get_power_modes(rdev);
	else
		return -EINVAL;

	/* set up the internal thermal sensor if applicable */
	ret = radeon_hwmon_init(rdev);
	if (ret)
		return ret;

	INIT_WORK(&rdev->pm.dpm.thermal.work, radeon_dpm_thermal_work_handler);
	mutex_lock(&rdev->pm.mutex);
	radeon_dpm_init(rdev);
	rdev->pm.dpm.current_ps = rdev->pm.dpm.requested_ps = rdev->pm.dpm.boot_ps;
	if (radeon_dpm == 1)
		radeon_dpm_print_power_states(rdev);
	radeon_dpm_setup_asic(rdev);
	ret = radeon_dpm_enable(rdev);
	mutex_unlock(&rdev->pm.mutex);
	if (ret)
		goto dpm_failed;
	rdev->pm.dpm_enabled = true;

	if (radeon_debugfs_pm_init(rdev)) {
		DRM_ERROR("Failed to register debugfs file for dpm!\n");
	}

	DRM_INFO("radeon: dpm initialized\n");

	return 0;

dpm_failed:
	rdev->pm.dpm_enabled = false;
	if ((rdev->family >= CHIP_BARTS) &&
	    (rdev->family <= CHIP_CAYMAN) &&
	    rdev->mc_fw) {
		if (rdev->pm.default_vddc)
			radeon_atom_set_voltage(rdev, rdev->pm.default_vddc,
						SET_VOLTAGE_TYPE_ASIC_VDDC);
		if (rdev->pm.default_vddci)
			radeon_atom_set_voltage(rdev, rdev->pm.default_vddci,
						SET_VOLTAGE_TYPE_ASIC_VDDCI);
		if (rdev->pm.default_sclk)
			radeon_set_engine_clock(rdev, rdev->pm.default_sclk);
		if (rdev->pm.default_mclk)
			radeon_set_memory_clock(rdev, rdev->pm.default_mclk);
	}
	DRM_ERROR("radeon: dpm initialization failed\n");
	return ret;
}