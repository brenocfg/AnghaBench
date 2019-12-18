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
struct ww_acquire_ctx {int dummy; } ;
struct v3d_job {int bo_count; int /*<<< orphan*/ * bo; int /*<<< orphan*/  deps; } ;

/* Variables and functions */
 int drm_gem_fence_array_add_implicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int drm_gem_lock_reservations (int /*<<< orphan*/ *,int,struct ww_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_gem_unlock_reservations (int /*<<< orphan*/ *,int,struct ww_acquire_ctx*) ; 

__attribute__((used)) static int
v3d_lock_bo_reservations(struct v3d_job *job,
			 struct ww_acquire_ctx *acquire_ctx)
{
	int i, ret;

	ret = drm_gem_lock_reservations(job->bo, job->bo_count, acquire_ctx);
	if (ret)
		return ret;

	for (i = 0; i < job->bo_count; i++) {
		ret = drm_gem_fence_array_add_implicit(&job->deps,
						       job->bo[i], true);
		if (ret) {
			drm_gem_unlock_reservations(job->bo, job->bo_count,
						    acquire_ctx);
			return ret;
		}
	}

	return 0;
}