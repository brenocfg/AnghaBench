#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct radeon_device {int dummy; } ;
struct kv_power_info {int uvd_power_gated; scalar_t__ caps_uvd_pg; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_UVDPowerOFF ; 
 int /*<<< orphan*/  PPSMC_MSG_UVDPowerON ; 
 int /*<<< orphan*/  RADEON_CG_BLOCK_UVD ; 
 int /*<<< orphan*/  cik_update_cg (struct radeon_device*,int /*<<< orphan*/ ,int) ; 
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  kv_notify_message_to_smu (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kv_update_uvd_dpm (struct radeon_device*,int) ; 
 int /*<<< orphan*/  uvd_v1_0_start (struct radeon_device*) ; 
 int /*<<< orphan*/  uvd_v1_0_stop (struct radeon_device*) ; 
 int /*<<< orphan*/  uvd_v4_2_resume (struct radeon_device*) ; 

void kv_dpm_powergate_uvd(struct radeon_device *rdev, bool gate)
{
	struct kv_power_info *pi = kv_get_pi(rdev);

	if (pi->uvd_power_gated == gate)
		return;

	pi->uvd_power_gated = gate;

	if (gate) {
		if (pi->caps_uvd_pg) {
			uvd_v1_0_stop(rdev);
			cik_update_cg(rdev, RADEON_CG_BLOCK_UVD, false);
		}
		kv_update_uvd_dpm(rdev, gate);
		if (pi->caps_uvd_pg)
			kv_notify_message_to_smu(rdev, PPSMC_MSG_UVDPowerOFF);
	} else {
		if (pi->caps_uvd_pg) {
			kv_notify_message_to_smu(rdev, PPSMC_MSG_UVDPowerON);
			uvd_v4_2_resume(rdev);
			uvd_v1_0_start(rdev);
			cik_update_cg(rdev, RADEON_CG_BLOCK_UVD, true);
		}
		kv_update_uvd_dpm(rdev, gate);
	}
}