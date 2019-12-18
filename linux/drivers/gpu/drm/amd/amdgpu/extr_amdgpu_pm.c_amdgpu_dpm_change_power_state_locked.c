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
struct amdgpu_ps {int /*<<< orphan*/  vce_active; } ;
struct TYPE_7__ {scalar_t__ user_state; scalar_t__ state; int forced_level; scalar_t__ thermal_active; int /*<<< orphan*/  new_active_crtc_count; int /*<<< orphan*/  current_active_crtc_count; int /*<<< orphan*/  new_active_crtcs; int /*<<< orphan*/  current_active_crtcs; struct amdgpu_ps* requested_ps; struct amdgpu_ps* current_ps; int /*<<< orphan*/  vce_active; int /*<<< orphan*/  uvd_active; } ;
struct TYPE_8__ {TYPE_3__ dpm; int /*<<< orphan*/  dpm_enabled; } ;
struct TYPE_6__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_4__ pm; TYPE_2__ powerplay; } ;
typedef  enum amd_pm_state_type { ____Placeholder_amd_pm_state_type } amd_pm_state_type ;
typedef  enum amd_dpm_forced_level { ____Placeholder_amd_dpm_forced_level } amd_dpm_forced_level ;
struct TYPE_5__ {scalar_t__ force_performance_level; scalar_t__ check_state_equal; scalar_t__ display_configuration_changed; scalar_t__ print_power_state; } ;

/* Variables and functions */
 int AMD_DPM_FORCED_LEVEL_LOW ; 
 int amdgpu_dpm ; 
 scalar_t__ amdgpu_dpm_check_state_equal (struct amdgpu_device*,struct amdgpu_ps*,struct amdgpu_ps*,int*) ; 
 int /*<<< orphan*/  amdgpu_dpm_display_configuration_changed (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_dpm_force_performance_level (struct amdgpu_device*,int) ; 
 struct amdgpu_ps* amdgpu_dpm_pick_power_state (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  amdgpu_dpm_post_set_power_state (struct amdgpu_device*) ; 
 int amdgpu_dpm_pre_set_power_state (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_dpm_print_power_state (struct amdgpu_device*,struct amdgpu_ps*) ; 
 int /*<<< orphan*/  amdgpu_dpm_set_power_state (struct amdgpu_device*) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void amdgpu_dpm_change_power_state_locked(struct amdgpu_device *adev)
{
	struct amdgpu_ps *ps;
	enum amd_pm_state_type dpm_state;
	int ret;
	bool equal = false;

	/* if dpm init failed */
	if (!adev->pm.dpm_enabled)
		return;

	if (adev->pm.dpm.user_state != adev->pm.dpm.state) {
		/* add other state override checks here */
		if ((!adev->pm.dpm.thermal_active) &&
		    (!adev->pm.dpm.uvd_active))
			adev->pm.dpm.state = adev->pm.dpm.user_state;
	}
	dpm_state = adev->pm.dpm.state;

	ps = amdgpu_dpm_pick_power_state(adev, dpm_state);
	if (ps)
		adev->pm.dpm.requested_ps = ps;
	else
		return;

	if (amdgpu_dpm == 1 && adev->powerplay.pp_funcs->print_power_state) {
		printk("switching from power state:\n");
		amdgpu_dpm_print_power_state(adev, adev->pm.dpm.current_ps);
		printk("switching to power state:\n");
		amdgpu_dpm_print_power_state(adev, adev->pm.dpm.requested_ps);
	}

	/* update whether vce is active */
	ps->vce_active = adev->pm.dpm.vce_active;
	if (adev->powerplay.pp_funcs->display_configuration_changed)
		amdgpu_dpm_display_configuration_changed(adev);

	ret = amdgpu_dpm_pre_set_power_state(adev);
	if (ret)
		return;

	if (adev->powerplay.pp_funcs->check_state_equal) {
		if (0 != amdgpu_dpm_check_state_equal(adev, adev->pm.dpm.current_ps, adev->pm.dpm.requested_ps, &equal))
			equal = false;
	}

	if (equal)
		return;

	amdgpu_dpm_set_power_state(adev);
	amdgpu_dpm_post_set_power_state(adev);

	adev->pm.dpm.current_active_crtcs = adev->pm.dpm.new_active_crtcs;
	adev->pm.dpm.current_active_crtc_count = adev->pm.dpm.new_active_crtc_count;

	if (adev->powerplay.pp_funcs->force_performance_level) {
		if (adev->pm.dpm.thermal_active) {
			enum amd_dpm_forced_level level = adev->pm.dpm.forced_level;
			/* force low perf level for thermal */
			amdgpu_dpm_force_performance_level(adev, AMD_DPM_FORCED_LEVEL_LOW);
			/* save the user's level */
			adev->pm.dpm.forced_level = level;
		} else {
			/* otherwise, user selected level */
			amdgpu_dpm_force_performance_level(adev, adev->pm.dpm.forced_level);
		}
	}
}