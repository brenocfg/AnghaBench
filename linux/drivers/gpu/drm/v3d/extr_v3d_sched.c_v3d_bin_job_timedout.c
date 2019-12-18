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
struct v3d_bin_job {int /*<<< orphan*/  timedout_ctra; int /*<<< orphan*/  timedout_ctca; } ;
struct drm_sched_job {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V3D_BIN ; 
 struct v3d_bin_job* to_bin_job (struct drm_sched_job*) ; 
 int /*<<< orphan*/  v3d_cl_job_timedout (struct drm_sched_job*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
v3d_bin_job_timedout(struct drm_sched_job *sched_job)
{
	struct v3d_bin_job *job = to_bin_job(sched_job);

	v3d_cl_job_timedout(sched_job, V3D_BIN,
			    &job->timedout_ctca, &job->timedout_ctra);
}