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
struct v3d_job {int /*<<< orphan*/  exec; } ;
struct drm_sched_job {int dummy; } ;

/* Variables and functions */
 struct v3d_job* to_v3d_job (struct drm_sched_job*) ; 
 int /*<<< orphan*/  v3d_exec_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
v3d_job_free(struct drm_sched_job *sched_job)
{
	struct v3d_job *job = to_v3d_job(sched_job);

	v3d_exec_put(job->exec);
}