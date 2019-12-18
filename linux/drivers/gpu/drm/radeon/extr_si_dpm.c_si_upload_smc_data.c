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
struct TYPE_6__ {struct radeon_crtc** crtcs; } ;
struct TYPE_4__ {scalar_t__ new_active_crtc_count; int new_active_crtcs; } ;
struct TYPE_5__ {TYPE_1__ dpm; } ;
struct radeon_device {int num_crtc; TYPE_3__ mode_info; TYPE_2__ pm; } ;
struct radeon_crtc {int line_time; int crtc_id; int wm_high; int wm_low; } ;

/* Variables and functions */
 scalar_t__ PPSMC_Result_OK ; 
 int /*<<< orphan*/  SI_SMC_SOFT_REGISTER_crtc_index ; 
 int /*<<< orphan*/  SI_SMC_SOFT_REGISTER_mclk_change_block_cp_max ; 
 int /*<<< orphan*/  SI_SMC_SOFT_REGISTER_mclk_change_block_cp_min ; 
 scalar_t__ si_write_smc_soft_register (struct radeon_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int si_upload_smc_data(struct radeon_device *rdev)
{
	struct radeon_crtc *radeon_crtc = NULL;
	int i;

	if (rdev->pm.dpm.new_active_crtc_count == 0)
		return 0;

	for (i = 0; i < rdev->num_crtc; i++) {
		if (rdev->pm.dpm.new_active_crtcs & (1 << i)) {
			radeon_crtc = rdev->mode_info.crtcs[i];
			break;
		}
	}

	if (radeon_crtc == NULL)
		return 0;

	if (radeon_crtc->line_time <= 0)
		return 0;

	if (si_write_smc_soft_register(rdev,
				       SI_SMC_SOFT_REGISTER_crtc_index,
				       radeon_crtc->crtc_id) != PPSMC_Result_OK)
		return 0;

	if (si_write_smc_soft_register(rdev,
				       SI_SMC_SOFT_REGISTER_mclk_change_block_cp_min,
				       radeon_crtc->wm_high / radeon_crtc->line_time) != PPSMC_Result_OK)
		return 0;

	if (si_write_smc_soft_register(rdev,
				       SI_SMC_SOFT_REGISTER_mclk_change_block_cp_max,
				       radeon_crtc->wm_low / radeon_crtc->line_time) != PPSMC_Result_OK)
		return 0;

	return 0;
}