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
typedef  scalar_t__ u32 ;
struct v3d_job {struct v3d_dev* v3d; } ;
struct v3d_dev {int dummy; } ;
struct drm_sched_job {int dummy; } ;
typedef  enum v3d_queue { ____Placeholder_v3d_queue } v3d_queue ;

/* Variables and functions */
 int /*<<< orphan*/  V3D_CLE_CTNCA (int) ; 
 int /*<<< orphan*/  V3D_CLE_CTNRA (int) ; 
 scalar_t__ V3D_CORE_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v3d_job* to_v3d_job (struct drm_sched_job*) ; 
 int /*<<< orphan*/  v3d_gpu_reset_for_timeout (struct v3d_dev*,struct drm_sched_job*) ; 

__attribute__((used)) static void
v3d_cl_job_timedout(struct drm_sched_job *sched_job, enum v3d_queue q,
		    u32 *timedout_ctca, u32 *timedout_ctra)
{
	struct v3d_job *job = to_v3d_job(sched_job);
	struct v3d_dev *v3d = job->v3d;
	u32 ctca = V3D_CORE_READ(0, V3D_CLE_CTNCA(q));
	u32 ctra = V3D_CORE_READ(0, V3D_CLE_CTNRA(q));

	if (*timedout_ctca != ctca || *timedout_ctra != ctra) {
		*timedout_ctca = ctca;
		*timedout_ctra = ctra;
		return;
	}

	v3d_gpu_reset_for_timeout(v3d, sched_job);
}