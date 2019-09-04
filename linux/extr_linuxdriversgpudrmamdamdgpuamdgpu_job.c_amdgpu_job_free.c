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
struct amdgpu_job {int /*<<< orphan*/  sched_sync; int /*<<< orphan*/  sync; int /*<<< orphan*/  fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_job_free_resources (struct amdgpu_job*) ; 
 int /*<<< orphan*/  amdgpu_sync_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_job*) ; 

void amdgpu_job_free(struct amdgpu_job *job)
{
	amdgpu_job_free_resources(job);

	dma_fence_put(job->fence);
	amdgpu_sync_free(&job->sync);
	amdgpu_sync_free(&job->sched_sync);
	kfree(job);
}