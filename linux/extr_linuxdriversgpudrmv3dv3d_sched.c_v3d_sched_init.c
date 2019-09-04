#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v3d_dev {TYPE_1__* queue; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  sched; } ;

/* Variables and functions */
 size_t V3D_BIN ; 
 size_t V3D_RENDER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  drm_sched_fini (int /*<<< orphan*/ *) ; 
 int drm_sched_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  v3d_sched_ops ; 

int
v3d_sched_init(struct v3d_dev *v3d)
{
	int hw_jobs_limit = 1;
	int job_hang_limit = 0;
	int hang_limit_ms = 500;
	int ret;

	ret = drm_sched_init(&v3d->queue[V3D_BIN].sched,
			     &v3d_sched_ops,
			     hw_jobs_limit, job_hang_limit,
			     msecs_to_jiffies(hang_limit_ms),
			     "v3d_bin");
	if (ret) {
		dev_err(v3d->dev, "Failed to create bin scheduler: %d.", ret);
		return ret;
	}

	ret = drm_sched_init(&v3d->queue[V3D_RENDER].sched,
			     &v3d_sched_ops,
			     hw_jobs_limit, job_hang_limit,
			     msecs_to_jiffies(hang_limit_ms),
			     "v3d_render");
	if (ret) {
		dev_err(v3d->dev, "Failed to create render scheduler: %d.",
			ret);
		drm_sched_fini(&v3d->queue[V3D_BIN].sched);
		return ret;
	}

	return 0;
}