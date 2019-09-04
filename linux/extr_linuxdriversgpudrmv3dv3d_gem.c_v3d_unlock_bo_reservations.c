#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ww_acquire_ctx {int dummy; } ;
struct v3d_exec_info {int bo_count; TYPE_1__** bo; } ;
struct v3d_bo {TYPE_2__* resv; } ;
struct drm_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 struct v3d_bo* to_v3d_bo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ww_acquire_fini (struct ww_acquire_ctx*) ; 
 int /*<<< orphan*/  ww_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
v3d_unlock_bo_reservations(struct drm_device *dev,
			   struct v3d_exec_info *exec,
			   struct ww_acquire_ctx *acquire_ctx)
{
	int i;

	for (i = 0; i < exec->bo_count; i++) {
		struct v3d_bo *bo = to_v3d_bo(&exec->bo[i]->base);

		ww_mutex_unlock(&bo->resv->lock);
	}

	ww_acquire_fini(acquire_ctx);
}