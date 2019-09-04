#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ci_power_info {scalar_t__ thermal_protection; } ;
struct amdgpu_ps {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_5__ {TYPE_1__ thermal; struct amdgpu_ps* boot_ps; } ;
struct TYPE_6__ {TYPE_2__ dpm; } ;
struct amdgpu_device {TYPE_3__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_DPM_AUTO_THROTTLE_SRC_THERMAL ; 
 int /*<<< orphan*/  AMDGPU_THERMAL_IRQ_HIGH_TO_LOW ; 
 int /*<<< orphan*/  AMDGPU_THERMAL_IRQ_LOW_TO_HIGH ; 
 int /*<<< orphan*/  amdgpu_ci_is_smc_running (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_irq_put (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ci_clear_vc (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_dpm_powergate_uvd (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  ci_dpm_stop_smc (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_enable_auto_throttle_source (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ci_enable_didt (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  ci_enable_ds_master_switch (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  ci_enable_power_containment (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  ci_enable_smc_cac (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  ci_enable_spread_spectrum (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  ci_enable_thermal_based_sclk_dpm (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  ci_enable_thermal_protection (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  ci_enable_ulv (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  ci_force_switch_to_arb_f0 (struct amdgpu_device*) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_reset_to_default (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_stop_dpm (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_thermal_stop_thermal_controller (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_update_current_ps (struct amdgpu_device*,struct amdgpu_ps*) ; 

__attribute__((used)) static void ci_dpm_disable(struct amdgpu_device *adev)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	struct amdgpu_ps *boot_ps = adev->pm.dpm.boot_ps;

	amdgpu_irq_put(adev, &adev->pm.dpm.thermal.irq,
		       AMDGPU_THERMAL_IRQ_LOW_TO_HIGH);
	amdgpu_irq_put(adev, &adev->pm.dpm.thermal.irq,
		       AMDGPU_THERMAL_IRQ_HIGH_TO_LOW);

	ci_dpm_powergate_uvd(adev, true);

	if (!amdgpu_ci_is_smc_running(adev))
		return;

	ci_thermal_stop_thermal_controller(adev);

	if (pi->thermal_protection)
		ci_enable_thermal_protection(adev, false);
	ci_enable_power_containment(adev, false);
	ci_enable_smc_cac(adev, false);
	ci_enable_didt(adev, false);
	ci_enable_spread_spectrum(adev, false);
	ci_enable_auto_throttle_source(adev, AMDGPU_DPM_AUTO_THROTTLE_SRC_THERMAL, false);
	ci_stop_dpm(adev);
	ci_enable_ds_master_switch(adev, false);
	ci_enable_ulv(adev, false);
	ci_clear_vc(adev);
	ci_reset_to_default(adev);
	ci_dpm_stop_smc(adev);
	ci_force_switch_to_arb_f0(adev);
	ci_enable_thermal_based_sclk_dpm(adev, false);

	ci_update_current_ps(adev, boot_ps);
}