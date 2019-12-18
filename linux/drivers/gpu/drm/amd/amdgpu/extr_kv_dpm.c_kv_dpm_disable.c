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
struct kv_power_info {scalar_t__ caps_uvd_pg; scalar_t__ caps_vce_pg; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_5__ {int /*<<< orphan*/  boot_ps; TYPE_1__ thermal; } ;
struct TYPE_6__ {TYPE_2__ dpm; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_3__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_THERMAL_IRQ_HIGH_TO_LOW ; 
 int /*<<< orphan*/  AMDGPU_THERMAL_IRQ_LOW_TO_HIGH ; 
 scalar_t__ CHIP_MULLINS ; 
 int /*<<< orphan*/  PPSMC_MSG_UVDPowerON ; 
 int /*<<< orphan*/  PPSMC_MSG_VCEPowerON ; 
 int /*<<< orphan*/  amdgpu_irq_put (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_kv_notify_message_to_smu (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_kv_smc_bapm_enable (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  kv_clear_vc (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kv_dpm_powergate_acp (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  kv_dpm_powergate_samu (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  kv_enable_didt (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  kv_enable_nb_dpm (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  kv_enable_smc_cac (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  kv_enable_ulv (struct amdgpu_device*,int) ; 
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kv_reset_am (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kv_stop_dpm (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kv_update_current_ps (struct amdgpu_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kv_dpm_disable(struct amdgpu_device *adev)
{
	struct kv_power_info *pi = kv_get_pi(adev);

	amdgpu_irq_put(adev, &adev->pm.dpm.thermal.irq,
		       AMDGPU_THERMAL_IRQ_LOW_TO_HIGH);
	amdgpu_irq_put(adev, &adev->pm.dpm.thermal.irq,
		       AMDGPU_THERMAL_IRQ_HIGH_TO_LOW);

	amdgpu_kv_smc_bapm_enable(adev, false);

	if (adev->asic_type == CHIP_MULLINS)
		kv_enable_nb_dpm(adev, false);

	/* powerup blocks */
	kv_dpm_powergate_acp(adev, false);
	kv_dpm_powergate_samu(adev, false);
	if (pi->caps_vce_pg) /* power on the VCE block */
		amdgpu_kv_notify_message_to_smu(adev, PPSMC_MSG_VCEPowerON);
	if (pi->caps_uvd_pg) /* power on the UVD block */
		amdgpu_kv_notify_message_to_smu(adev, PPSMC_MSG_UVDPowerON);

	kv_enable_smc_cac(adev, false);
	kv_enable_didt(adev, false);
	kv_clear_vc(adev);
	kv_stop_dpm(adev);
	kv_enable_ulv(adev, false);
	kv_reset_am(adev);

	kv_update_current_ps(adev, adev->pm.dpm.boot_ps);
}