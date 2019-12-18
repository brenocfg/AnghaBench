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
struct v3d_job {struct v3d_dev* v3d; } ;
struct v3d_dev {int dummy; } ;
struct drm_sched_job {int dummy; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 struct v3d_job* to_v3d_job (struct drm_sched_job*) ; 
 int /*<<< orphan*/  v3d_clean_caches (struct v3d_dev*) ; 

__attribute__((used)) static struct dma_fence *
v3d_cache_clean_job_run(struct drm_sched_job *sched_job)
{
	struct v3d_job *job = to_v3d_job(sched_job);
	struct v3d_dev *v3d = job->v3d;

	v3d_clean_caches(v3d);

	return NULL;
}