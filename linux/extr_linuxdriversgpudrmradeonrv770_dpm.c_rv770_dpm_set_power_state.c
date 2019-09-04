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
struct rv7xx_power_info {scalar_t__ dcodt; } ;
struct radeon_ps {int dummy; } ;
struct TYPE_4__ {struct radeon_ps* current_ps; struct radeon_ps* requested_ps; } ;
struct TYPE_3__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_1__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  r7xx_program_memory_timing_parameters (struct radeon_device*,struct radeon_ps*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 int rv770_halt_smc (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_program_dcodt_after_state_switch (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  rv770_program_dcodt_before_state_switch (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int rv770_restrict_performance_levels_before_switch (struct radeon_device*) ; 
 int rv770_resume_smc (struct radeon_device*) ; 
 int rv770_set_sw_state (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_set_uvd_clock_after_set_eng_clock (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int /*<<< orphan*/  rv770_set_uvd_clock_before_set_eng_clock (struct radeon_device*,struct radeon_ps*,struct radeon_ps*) ; 
 int rv770_upload_sw_state (struct radeon_device*,struct radeon_ps*) ; 

int rv770_dpm_set_power_state(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct radeon_ps *new_ps = rdev->pm.dpm.requested_ps;
	struct radeon_ps *old_ps = rdev->pm.dpm.current_ps;
	int ret;

	ret = rv770_restrict_performance_levels_before_switch(rdev);
	if (ret) {
		DRM_ERROR("rv770_restrict_performance_levels_before_switch failed\n");
		return ret;
	}
	rv770_set_uvd_clock_before_set_eng_clock(rdev, new_ps, old_ps);
	ret = rv770_halt_smc(rdev);
	if (ret) {
		DRM_ERROR("rv770_halt_smc failed\n");
		return ret;
	}
	ret = rv770_upload_sw_state(rdev, new_ps);
	if (ret) {
		DRM_ERROR("rv770_upload_sw_state failed\n");
		return ret;
	}
	r7xx_program_memory_timing_parameters(rdev, new_ps);
	if (pi->dcodt)
		rv770_program_dcodt_before_state_switch(rdev, new_ps, old_ps);
	ret = rv770_resume_smc(rdev);
	if (ret) {
		DRM_ERROR("rv770_resume_smc failed\n");
		return ret;
	}
	ret = rv770_set_sw_state(rdev);
	if (ret) {
		DRM_ERROR("rv770_set_sw_state failed\n");
		return ret;
	}
	if (pi->dcodt)
		rv770_program_dcodt_after_state_switch(rdev, new_ps, old_ps);
	rv770_set_uvd_clock_after_set_eng_clock(rdev, new_ps, old_ps);

	return 0;
}