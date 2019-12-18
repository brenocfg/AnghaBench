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
struct v3d_job {int /*<<< orphan*/  v3d; } ;
struct drm_sched_job {int dummy; } ;

/* Variables and functions */
 struct v3d_job* to_v3d_job (struct drm_sched_job*) ; 
 int /*<<< orphan*/  v3d_gpu_reset_for_timeout (int /*<<< orphan*/ ,struct drm_sched_job*) ; 

__attribute__((used)) static void
v3d_generic_job_timedout(struct drm_sched_job *sched_job)
{
	struct v3d_job *job = to_v3d_job(sched_job);

	v3d_gpu_reset_for_timeout(job->v3d, sched_job);
}