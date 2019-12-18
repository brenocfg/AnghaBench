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
struct drm_sched_job {int /*<<< orphan*/  s_priority; int /*<<< orphan*/  sched; } ;
struct amdgpu_ring {int dummy; } ;
struct amdgpu_job {int /*<<< orphan*/  sched_sync; int /*<<< orphan*/  sync; int /*<<< orphan*/  fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_ring_priority_put (struct amdgpu_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_sync_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_sched_job_cleanup (struct drm_sched_job*) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_job*) ; 
 struct amdgpu_job* to_amdgpu_job (struct drm_sched_job*) ; 
 struct amdgpu_ring* to_amdgpu_ring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amdgpu_job_free_cb(struct drm_sched_job *s_job)
{
	struct amdgpu_ring *ring = to_amdgpu_ring(s_job->sched);
	struct amdgpu_job *job = to_amdgpu_job(s_job);

	drm_sched_job_cleanup(s_job);

	amdgpu_ring_priority_put(ring, s_job->s_priority);
	dma_fence_put(job->fence);
	amdgpu_sync_free(&job->sync);
	amdgpu_sync_free(&job->sched_sync);
	kfree(job);
}