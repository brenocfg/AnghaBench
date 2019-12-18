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
struct TYPE_4__ {int dynpm_can_upclock; int dynpm_can_downclock; int num_power_states; int /*<<< orphan*/  dynpm_idle_work; scalar_t__ default_mclk; scalar_t__ default_sclk; scalar_t__ default_vddci; scalar_t__ default_vddc; int /*<<< orphan*/  int_thermal_type; scalar_t__ current_mclk; scalar_t__ current_sclk; int /*<<< orphan*/  dynpm_planned_action; int /*<<< orphan*/  dynpm_state; int /*<<< orphan*/  profile; } ;
struct TYPE_3__ {scalar_t__ default_mclk; scalar_t__ default_sclk; } ;
struct radeon_device {scalar_t__ family; TYPE_2__ pm; scalar_t__ mc_fw; scalar_t__ is_atom_bios; scalar_t__ bios; TYPE_1__ clock; } ;

/* Variables and functions */
 scalar_t__ CHIP_BARTS ; 
 scalar_t__ CHIP_CAYMAN ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  DYNPM_ACTION_NONE ; 
 int /*<<< orphan*/  DYNPM_STATE_DISABLED ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM_PROFILE_DEFAULT ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_VDDC ; 
 int /*<<< orphan*/  SET_VOLTAGE_TYPE_ASIC_VDDCI ; 
 int /*<<< orphan*/  THERMAL_TYPE_NONE ; 
 int /*<<< orphan*/  radeon_atom_set_voltage (struct radeon_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_atombios_get_power_modes (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_combios_get_power_modes (struct radeon_device*) ; 
 scalar_t__ radeon_debugfs_pm_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_dynpm_idle_work_handler ; 
 int radeon_hwmon_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_pm_init_profile (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_pm_print_states (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_set_engine_clock (struct radeon_device*,scalar_t__) ; 
 int /*<<< orphan*/  radeon_set_memory_clock (struct radeon_device*,scalar_t__) ; 

__attribute__((used)) static int radeon_pm_init_old(struct radeon_device *rdev)
{
	int ret;

	rdev->pm.profile = PM_PROFILE_DEFAULT;
	rdev->pm.dynpm_state = DYNPM_STATE_DISABLED;
	rdev->pm.dynpm_planned_action = DYNPM_ACTION_NONE;
	rdev->pm.dynpm_can_upclock = true;
	rdev->pm.dynpm_can_downclock = true;
	rdev->pm.default_sclk = rdev->clock.default_sclk;
	rdev->pm.default_mclk = rdev->clock.default_mclk;
	rdev->pm.current_sclk = rdev->clock.default_sclk;
	rdev->pm.current_mclk = rdev->clock.default_mclk;
	rdev->pm.int_thermal_type = THERMAL_TYPE_NONE;

	if (rdev->bios) {
		if (rdev->is_atom_bios)
			radeon_atombios_get_power_modes(rdev);
		else
			radeon_combios_get_power_modes(rdev);
		radeon_pm_print_states(rdev);
		radeon_pm_init_profile(rdev);
		/* set up the default clocks if the MC ucode is loaded */
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
	}

	/* set up the internal thermal sensor if applicable */
	ret = radeon_hwmon_init(rdev);
	if (ret)
		return ret;

	INIT_DELAYED_WORK(&rdev->pm.dynpm_idle_work, radeon_dynpm_idle_work_handler);

	if (rdev->pm.num_power_states > 1) {
		if (radeon_debugfs_pm_init(rdev)) {
			DRM_ERROR("Failed to register debugfs file for PM!\n");
		}

		DRM_INFO("radeon: power management initialized\n");
	}

	return 0;
}