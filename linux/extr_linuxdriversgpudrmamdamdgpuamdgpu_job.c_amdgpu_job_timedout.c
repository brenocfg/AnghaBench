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
struct drm_sched_job {int /*<<< orphan*/  sched; } ;
struct TYPE_6__ {int /*<<< orphan*/  sync_seq; int /*<<< orphan*/  last_seq; } ;
struct amdgpu_ring {int /*<<< orphan*/  adev; TYPE_3__ fence_drv; } ;
struct TYPE_5__ {TYPE_1__* sched; } ;
struct amdgpu_job {TYPE_2__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_device_gpu_recover (int /*<<< orphan*/ ,struct amdgpu_job*,int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct amdgpu_job* to_amdgpu_job (struct drm_sched_job*) ; 
 struct amdgpu_ring* to_amdgpu_ring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amdgpu_job_timedout(struct drm_sched_job *s_job)
{
	struct amdgpu_ring *ring = to_amdgpu_ring(s_job->sched);
	struct amdgpu_job *job = to_amdgpu_job(s_job);

	DRM_ERROR("ring %s timeout, signaled seq=%u, emitted seq=%u\n",
		  job->base.sched->name, atomic_read(&ring->fence_drv.last_seq),
		  ring->fence_drv.sync_seq);

	amdgpu_device_gpu_recover(ring->adev, job, false);
}