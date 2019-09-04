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
struct TYPE_3__ {int initialized; unsigned int num_fences_mask; int /*<<< orphan*/  fences; int /*<<< orphan*/  lock; int /*<<< orphan*/  fallback_timer; int /*<<< orphan*/  last_seq; scalar_t__ sync_seq; scalar_t__ gpu_addr; int /*<<< orphan*/ * cpu_addr; } ;
struct amdgpu_ring {int /*<<< orphan*/  name; int /*<<< orphan*/  sched; int /*<<< orphan*/  adev; TYPE_2__* funcs; TYPE_1__ fence_drv; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_RING_TYPE_COMPUTE ; 
 scalar_t__ AMDGPU_RING_TYPE_KIQ ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 long MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  amdgpu_fence_fallback ; 
 int /*<<< orphan*/  amdgpu_job_hang_limit ; 
 int /*<<< orphan*/  amdgpu_lockup_timeout ; 
 int /*<<< orphan*/  amdgpu_sched_ops ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_sched_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int amdgpu_fence_driver_init_ring(struct amdgpu_ring *ring,
				  unsigned num_hw_submission)
{
	long timeout;
	int r;

	/* Check that num_hw_submission is a power of two */
	if ((num_hw_submission & (num_hw_submission - 1)) != 0)
		return -EINVAL;

	ring->fence_drv.cpu_addr = NULL;
	ring->fence_drv.gpu_addr = 0;
	ring->fence_drv.sync_seq = 0;
	atomic_set(&ring->fence_drv.last_seq, 0);
	ring->fence_drv.initialized = false;

	timer_setup(&ring->fence_drv.fallback_timer, amdgpu_fence_fallback, 0);

	ring->fence_drv.num_fences_mask = num_hw_submission * 2 - 1;
	spin_lock_init(&ring->fence_drv.lock);
	ring->fence_drv.fences = kcalloc(num_hw_submission * 2, sizeof(void *),
					 GFP_KERNEL);
	if (!ring->fence_drv.fences)
		return -ENOMEM;

	/* No need to setup the GPU scheduler for KIQ ring */
	if (ring->funcs->type != AMDGPU_RING_TYPE_KIQ) {
		/* for non-sriov case, no timeout enforce on compute ring */
		if ((ring->funcs->type == AMDGPU_RING_TYPE_COMPUTE)
				&& !amdgpu_sriov_vf(ring->adev))
			timeout = MAX_SCHEDULE_TIMEOUT;
		else
			timeout = msecs_to_jiffies(amdgpu_lockup_timeout);

		r = drm_sched_init(&ring->sched, &amdgpu_sched_ops,
				   num_hw_submission, amdgpu_job_hang_limit,
				   timeout, ring->name);
		if (r) {
			DRM_ERROR("Failed to create scheduler on ring %s.\n",
				  ring->name);
			return r;
		}
	}

	return 0;
}