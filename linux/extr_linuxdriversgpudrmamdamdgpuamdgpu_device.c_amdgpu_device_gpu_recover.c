#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  thread; } ;
struct amdgpu_ring {TYPE_2__ sched; } ;
struct TYPE_7__ {TYPE_2__* sched; } ;
struct amdgpu_job {TYPE_4__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  bdev; } ;
struct amdgpu_device {int in_gpu_reset; int /*<<< orphan*/  lock_reset; int /*<<< orphan*/  gpu_reset_counter; int /*<<< orphan*/  dev; TYPE_1__ mman; int /*<<< orphan*/  ddev; struct amdgpu_ring** rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGIM_ERROR_VF_GPU_RESET_FAIL ; 
 int AMDGPU_MAX_RINGS ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  amdgpu_amdkfd_post_reset (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_amdkfd_pre_reset (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_device_has_dc_support (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_device_ip_check_soft_reset (struct amdgpu_device*) ; 
 int amdgpu_device_reset (struct amdgpu_device*) ; 
 int amdgpu_device_reset_sriov (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  amdgpu_fence_driver_force_completion (struct amdgpu_ring*) ; 
 int amdgpu_gpu_recovery ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_vf_error_put (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_vf_error_trans_all (struct amdgpu_device*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  drm_helper_resume_force_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_sched_hw_job_reset (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  drm_sched_job_recovery (TYPE_2__*) ; 
 int /*<<< orphan*/  kthread_park (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_unpark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ttm_bo_lock_delayed_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unlock_delayed_workqueue (int /*<<< orphan*/ *,int) ; 

int amdgpu_device_gpu_recover(struct amdgpu_device *adev,
			      struct amdgpu_job *job, bool force)
{
	int i, r, resched;

	if (!force && !amdgpu_device_ip_check_soft_reset(adev)) {
		DRM_INFO("No hardware hang detected. Did some blocks stall?\n");
		return 0;
	}

	if (!force && (amdgpu_gpu_recovery == 0 ||
			(amdgpu_gpu_recovery == -1  && !amdgpu_sriov_vf(adev)))) {
		DRM_INFO("GPU recovery disabled.\n");
		return 0;
	}

	dev_info(adev->dev, "GPU reset begin!\n");

	mutex_lock(&adev->lock_reset);
	atomic_inc(&adev->gpu_reset_counter);
	adev->in_gpu_reset = 1;

	/* Block kfd */
	amdgpu_amdkfd_pre_reset(adev);

	/* block TTM */
	resched = ttm_bo_lock_delayed_workqueue(&adev->mman.bdev);

	/* block all schedulers and reset given job's ring */
	for (i = 0; i < AMDGPU_MAX_RINGS; ++i) {
		struct amdgpu_ring *ring = adev->rings[i];

		if (!ring || !ring->sched.thread)
			continue;

		kthread_park(ring->sched.thread);

		if (job && job->base.sched == &ring->sched)
			continue;

		drm_sched_hw_job_reset(&ring->sched, job ? &job->base : NULL);

		/* after all hw jobs are reset, hw fence is meaningless, so force_completion */
		amdgpu_fence_driver_force_completion(ring);
	}

	if (amdgpu_sriov_vf(adev))
		r = amdgpu_device_reset_sriov(adev, job ? false : true);
	else
		r = amdgpu_device_reset(adev);

	for (i = 0; i < AMDGPU_MAX_RINGS; ++i) {
		struct amdgpu_ring *ring = adev->rings[i];

		if (!ring || !ring->sched.thread)
			continue;

		/* only need recovery sched of the given job's ring
		 * or all rings (in the case @job is NULL)
		 * after above amdgpu_reset accomplished
		 */
		if ((!job || job->base.sched == &ring->sched) && !r)
			drm_sched_job_recovery(&ring->sched);

		kthread_unpark(ring->sched.thread);
	}

	if (!amdgpu_device_has_dc_support(adev)) {
		drm_helper_resume_force_mode(adev->ddev);
	}

	ttm_bo_unlock_delayed_workqueue(&adev->mman.bdev, resched);

	if (r) {
		/* bad news, how to tell it to userspace ? */
		dev_info(adev->dev, "GPU reset(%d) failed\n", atomic_read(&adev->gpu_reset_counter));
		amdgpu_vf_error_put(adev, AMDGIM_ERROR_VF_GPU_RESET_FAIL, 0, r);
	} else {
		dev_info(adev->dev, "GPU reset(%d) succeeded!\n",atomic_read(&adev->gpu_reset_counter));
	}

	/*unlock kfd */
	amdgpu_amdkfd_post_reset(adev);
	amdgpu_vf_error_trans_all(adev);
	adev->in_gpu_reset = 0;
	mutex_unlock(&adev->lock_reset);
	return r;
}