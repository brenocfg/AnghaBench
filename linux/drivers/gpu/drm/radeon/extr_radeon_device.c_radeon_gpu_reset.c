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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {scalar_t__ pm_method; int dpm_enabled; } ;
struct TYPE_5__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_4__ {scalar_t__ bl_encoder; } ;
struct radeon_device {int needs_reset; int in_reset; int /*<<< orphan*/  exclusive_lock; int /*<<< orphan*/  dev; TYPE_3__ pm; int /*<<< orphan*/  ddev; TYPE_2__ mman; TYPE_1__ mode_info; scalar_t__ is_atom_bios; int /*<<< orphan*/ * ring; int /*<<< orphan*/  gpu_reset_counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EAGAIN ; 
 scalar_t__ PM_METHOD_DPM ; 
 int RADEON_NUM_RINGS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  downgrade_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_resume_force_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int radeon_asic_reset (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_atom_disp_eng_pll_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_atom_encoder_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_fence_driver_force_completion (struct radeon_device*,int) ; 
 int /*<<< orphan*/  radeon_get_backlight_level (struct radeon_device*,scalar_t__) ; 
 int /*<<< orphan*/  radeon_hpd_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_hpd_init (struct radeon_device*) ; 
 int radeon_ib_ring_tests (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_pm_compute_clocks (struct radeon_device*) ; 
 int radeon_pm_late_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_pm_resume (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_restore_bios_scratch_regs (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_resume (struct radeon_device*) ; 
 unsigned int radeon_ring_backup (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  radeon_ring_restore (struct radeon_device*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_save_bios_scratch_regs (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_set_backlight_level (struct radeon_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_suspend (struct radeon_device*) ; 
 int ttm_bo_lock_delayed_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unlock_delayed_workqueue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int radeon_gpu_reset(struct radeon_device *rdev)
{
	unsigned ring_sizes[RADEON_NUM_RINGS];
	uint32_t *ring_data[RADEON_NUM_RINGS];

	bool saved = false;

	int i, r;
	int resched;

	down_write(&rdev->exclusive_lock);

	if (!rdev->needs_reset) {
		up_write(&rdev->exclusive_lock);
		return 0;
	}

	atomic_inc(&rdev->gpu_reset_counter);

	radeon_save_bios_scratch_regs(rdev);
	/* block TTM */
	resched = ttm_bo_lock_delayed_workqueue(&rdev->mman.bdev);
	radeon_suspend(rdev);
	radeon_hpd_fini(rdev);

	for (i = 0; i < RADEON_NUM_RINGS; ++i) {
		ring_sizes[i] = radeon_ring_backup(rdev, &rdev->ring[i],
						   &ring_data[i]);
		if (ring_sizes[i]) {
			saved = true;
			dev_info(rdev->dev, "Saved %d dwords of commands "
				 "on ring %d.\n", ring_sizes[i], i);
		}
	}

	r = radeon_asic_reset(rdev);
	if (!r) {
		dev_info(rdev->dev, "GPU reset succeeded, trying to resume\n");
		radeon_resume(rdev);
	}

	radeon_restore_bios_scratch_regs(rdev);

	for (i = 0; i < RADEON_NUM_RINGS; ++i) {
		if (!r && ring_data[i]) {
			radeon_ring_restore(rdev, &rdev->ring[i],
					    ring_sizes[i], ring_data[i]);
		} else {
			radeon_fence_driver_force_completion(rdev, i);
			kfree(ring_data[i]);
		}
	}

	if ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled) {
		/* do dpm late init */
		r = radeon_pm_late_init(rdev);
		if (r) {
			rdev->pm.dpm_enabled = false;
			DRM_ERROR("radeon_pm_late_init failed, disabling dpm\n");
		}
	} else {
		/* resume old pm late */
		radeon_pm_resume(rdev);
	}

	/* init dig PHYs, disp eng pll */
	if (rdev->is_atom_bios) {
		radeon_atom_encoder_init(rdev);
		radeon_atom_disp_eng_pll_init(rdev);
		/* turn on the BL */
		if (rdev->mode_info.bl_encoder) {
			u8 bl_level = radeon_get_backlight_level(rdev,
								 rdev->mode_info.bl_encoder);
			radeon_set_backlight_level(rdev, rdev->mode_info.bl_encoder,
						   bl_level);
		}
	}
	/* reset hpd state */
	radeon_hpd_init(rdev);

	ttm_bo_unlock_delayed_workqueue(&rdev->mman.bdev, resched);

	rdev->in_reset = true;
	rdev->needs_reset = false;

	downgrade_write(&rdev->exclusive_lock);

	drm_helper_resume_force_mode(rdev->ddev);

	/* set the power state here in case we are a PX system or headless */
	if ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled)
		radeon_pm_compute_clocks(rdev);

	if (!r) {
		r = radeon_ib_ring_tests(rdev);
		if (r && saved)
			r = -EAGAIN;
	} else {
		/* bad news, how to tell it to userspace ? */
		dev_info(rdev->dev, "GPU reset failed\n");
	}

	rdev->needs_reset = r == -EAGAIN;
	rdev->in_reset = false;

	up_read(&rdev->exclusive_lock);
	return r;
}