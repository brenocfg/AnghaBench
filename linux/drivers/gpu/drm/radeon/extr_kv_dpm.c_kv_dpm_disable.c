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
struct TYPE_3__ {int /*<<< orphan*/  boot_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {scalar_t__ family; TYPE_2__ pm; } ;

/* Variables and functions */
 scalar_t__ CHIP_MULLINS ; 
 int /*<<< orphan*/  kv_clear_vc (struct radeon_device*) ; 
 int /*<<< orphan*/  kv_dpm_powergate_acp (struct radeon_device*,int) ; 
 int /*<<< orphan*/  kv_dpm_powergate_samu (struct radeon_device*,int) ; 
 int /*<<< orphan*/  kv_dpm_powergate_uvd (struct radeon_device*,int) ; 
 int /*<<< orphan*/  kv_dpm_powergate_vce (struct radeon_device*,int) ; 
 int /*<<< orphan*/  kv_enable_didt (struct radeon_device*,int) ; 
 int /*<<< orphan*/  kv_enable_nb_dpm (struct radeon_device*,int) ; 
 int /*<<< orphan*/  kv_enable_smc_cac (struct radeon_device*,int) ; 
 int /*<<< orphan*/  kv_enable_thermal_int (struct radeon_device*,int) ; 
 int /*<<< orphan*/  kv_enable_ulv (struct radeon_device*,int) ; 
 int /*<<< orphan*/  kv_reset_am (struct radeon_device*) ; 
 int /*<<< orphan*/  kv_smc_bapm_enable (struct radeon_device*,int) ; 
 int /*<<< orphan*/  kv_stop_dpm (struct radeon_device*) ; 
 int /*<<< orphan*/  kv_update_current_ps (struct radeon_device*,int /*<<< orphan*/ ) ; 

void kv_dpm_disable(struct radeon_device *rdev)
{
	kv_smc_bapm_enable(rdev, false);

	if (rdev->family == CHIP_MULLINS)
		kv_enable_nb_dpm(rdev, false);

	/* powerup blocks */
	kv_dpm_powergate_acp(rdev, false);
	kv_dpm_powergate_samu(rdev, false);
	kv_dpm_powergate_vce(rdev, false);
	kv_dpm_powergate_uvd(rdev, false);

	kv_enable_smc_cac(rdev, false);
	kv_enable_didt(rdev, false);
	kv_clear_vc(rdev);
	kv_stop_dpm(rdev);
	kv_enable_ulv(rdev, false);
	kv_reset_am(rdev);
	kv_enable_thermal_int(rdev, false);

	kv_update_current_ps(rdev, rdev->pm.dpm.boot_ps);
}