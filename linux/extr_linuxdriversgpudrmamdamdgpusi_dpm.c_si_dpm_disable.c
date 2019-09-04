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
struct rv7xx_power_info {scalar_t__ thermal_protection; } ;
struct amdgpu_ps {int dummy; } ;
struct TYPE_3__ {struct amdgpu_ps* boot_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct amdgpu_device {TYPE_2__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_DPM_AUTO_THROTTLE_SRC_THERMAL ; 
 int /*<<< orphan*/  amdgpu_si_is_smc_running (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ni_update_current_ps (struct amdgpu_device*,struct amdgpu_ps*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_clear_vc (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_disable_ulv (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_dpm_stop_smc (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_enable_auto_throttle_source (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  si_enable_power_containment (struct amdgpu_device*,struct amdgpu_ps*,int) ; 
 int /*<<< orphan*/  si_enable_smc_cac (struct amdgpu_device*,struct amdgpu_ps*,int) ; 
 int /*<<< orphan*/  si_enable_spread_spectrum (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  si_enable_thermal_protection (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  si_force_switch_to_arb_f0 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_reset_to_default (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_stop_dpm (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_thermal_stop_thermal_controller (struct amdgpu_device*) ; 

__attribute__((used)) static void si_dpm_disable(struct amdgpu_device *adev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(adev);
	struct amdgpu_ps *boot_ps = adev->pm.dpm.boot_ps;

	if (!amdgpu_si_is_smc_running(adev))
		return;
	si_thermal_stop_thermal_controller(adev);
	si_disable_ulv(adev);
	si_clear_vc(adev);
	if (pi->thermal_protection)
		si_enable_thermal_protection(adev, false);
	si_enable_power_containment(adev, boot_ps, false);
	si_enable_smc_cac(adev, boot_ps, false);
	si_enable_spread_spectrum(adev, false);
	si_enable_auto_throttle_source(adev, AMDGPU_DPM_AUTO_THROTTLE_SRC_THERMAL, false);
	si_stop_dpm(adev);
	si_reset_to_default(adev);
	si_dpm_stop_smc(adev);
	si_force_switch_to_arb_f0(adev);

	ni_update_current_ps(adev, boot_ps);
}