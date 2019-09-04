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
struct TYPE_5__ {int /*<<< orphan*/ * man; } ;
struct TYPE_6__ {TYPE_2__ bdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {int flags; int /*<<< orphan*/  dev; TYPE_3__ mman; int /*<<< orphan*/  vram_lost_counter; TYPE_1__ mode_info; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 size_t TTM_PL_TT ; 
 int amdgpu_asic_reset (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_atom_asic_init (int /*<<< orphan*/ ) ; 
 int amdgpu_device_check_vram_lost (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_device_fill_reset_magic (struct amdgpu_device*) ; 
 int amdgpu_device_handle_vram_lost (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_device_ip_check_soft_reset (struct amdgpu_device*) ; 
 int amdgpu_device_ip_need_full_reset (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_device_ip_post_soft_reset (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_device_ip_pre_soft_reset (struct amdgpu_device*) ; 
 int amdgpu_device_ip_resume_phase1 (struct amdgpu_device*) ; 
 int amdgpu_device_ip_resume_phase2 (struct amdgpu_device*) ; 
 int amdgpu_device_ip_soft_reset (struct amdgpu_device*) ; 
 int amdgpu_device_ip_suspend (struct amdgpu_device*) ; 
 int amdgpu_gtt_mgr_recover (int /*<<< orphan*/ *) ; 
 int amdgpu_ib_ring_tests (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_irq_gpu_reset_resume_helper (struct amdgpu_device*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int amdgpu_device_reset(struct amdgpu_device *adev)
{
	bool need_full_reset, vram_lost = 0;
	int r;

	need_full_reset = amdgpu_device_ip_need_full_reset(adev);

	if (!need_full_reset) {
		amdgpu_device_ip_pre_soft_reset(adev);
		r = amdgpu_device_ip_soft_reset(adev);
		amdgpu_device_ip_post_soft_reset(adev);
		if (r || amdgpu_device_ip_check_soft_reset(adev)) {
			DRM_INFO("soft reset failed, will fallback to full reset!\n");
			need_full_reset = true;
		}
	}

	if (need_full_reset) {
		r = amdgpu_device_ip_suspend(adev);

retry:
		r = amdgpu_asic_reset(adev);
		/* post card */
		amdgpu_atom_asic_init(adev->mode_info.atom_context);

		if (!r) {
			dev_info(adev->dev, "GPU reset succeeded, trying to resume\n");
			r = amdgpu_device_ip_resume_phase1(adev);
			if (r)
				goto out;

			vram_lost = amdgpu_device_check_vram_lost(adev);
			if (vram_lost) {
				DRM_ERROR("VRAM is lost!\n");
				atomic_inc(&adev->vram_lost_counter);
			}

			r = amdgpu_gtt_mgr_recover(
				&adev->mman.bdev.man[TTM_PL_TT]);
			if (r)
				goto out;

			r = amdgpu_device_ip_resume_phase2(adev);
			if (r)
				goto out;

			if (vram_lost)
				amdgpu_device_fill_reset_magic(adev);
		}
	}

out:
	if (!r) {
		amdgpu_irq_gpu_reset_resume_helper(adev);
		r = amdgpu_ib_ring_tests(adev);
		if (r) {
			dev_err(adev->dev, "ib ring test failed (%d).\n", r);
			r = amdgpu_device_ip_suspend(adev);
			need_full_reset = true;
			goto retry;
		}
	}

	if (!r && ((need_full_reset && !(adev->flags & AMD_IS_APU)) || vram_lost))
		r = amdgpu_device_handle_vram_lost(adev);

	return r;
}