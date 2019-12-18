#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mode_config_initialized; int /*<<< orphan*/  bios_hardcoded_edid; } ;
struct radeon_device {TYPE_1__ mode_info; int /*<<< orphan*/  ddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_helper_force_disable_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_afmt_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_fbdev_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_hpd_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_i2c_fini (struct radeon_device*) ; 

void radeon_modeset_fini(struct radeon_device *rdev)
{
	if (rdev->mode_info.mode_config_initialized) {
		drm_kms_helper_poll_fini(rdev->ddev);
		radeon_hpd_fini(rdev);
		drm_helper_force_disable_all(rdev->ddev);
		radeon_fbdev_fini(rdev);
		radeon_afmt_fini(rdev);
		drm_mode_config_cleanup(rdev->ddev);
		rdev->mode_info.mode_config_initialized = false;
	}

	kfree(rdev->mode_info.bios_hardcoded_edid);

	/* free i2c buses */
	radeon_i2c_fini(rdev);
}