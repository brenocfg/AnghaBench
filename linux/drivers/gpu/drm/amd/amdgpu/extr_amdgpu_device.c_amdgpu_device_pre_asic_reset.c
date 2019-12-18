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
struct TYPE_2__ {int /*<<< orphan*/  thread; } ;
struct amdgpu_ring {TYPE_1__ sched; } ;
struct amdgpu_job {int /*<<< orphan*/  base; } ;
struct amdgpu_device {struct amdgpu_ring** rings; } ;

/* Variables and functions */
 int AMDGPU_MAX_RINGS ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 scalar_t__ amdgpu_device_ip_check_soft_reset (struct amdgpu_device*) ; 
 int amdgpu_device_ip_need_full_reset (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_device_ip_post_soft_reset (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_device_ip_pre_soft_reset (struct amdgpu_device*) ; 
 int amdgpu_device_ip_soft_reset (struct amdgpu_device*) ; 
 int amdgpu_device_ip_suspend (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_fence_driver_force_completion (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  drm_sched_increase_karma (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_device_pre_asic_reset(struct amdgpu_device *adev,
					struct amdgpu_job *job,
					bool *need_full_reset_arg)
{
	int i, r = 0;
	bool need_full_reset  = *need_full_reset_arg;

	/* block all schedulers and reset given job's ring */
	for (i = 0; i < AMDGPU_MAX_RINGS; ++i) {
		struct amdgpu_ring *ring = adev->rings[i];

		if (!ring || !ring->sched.thread)
			continue;

		/* after all hw jobs are reset, hw fence is meaningless, so force_completion */
		amdgpu_fence_driver_force_completion(ring);
	}

	if(job)
		drm_sched_increase_karma(&job->base);

	/* Don't suspend on bare metal if we are not going to HW reset the ASIC */
	if (!amdgpu_sriov_vf(adev)) {

		if (!need_full_reset)
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

		if (need_full_reset)
			r = amdgpu_device_ip_suspend(adev);

		*need_full_reset_arg = need_full_reset;
	}

	return r;
}