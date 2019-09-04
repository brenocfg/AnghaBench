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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  work; } ;
struct mtk_drm_private {TYPE_1__ commit; } ;
struct drm_device {struct mtk_drm_private* dev_private; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_helper_cleanup_planes (struct drm_device*,struct drm_atomic_state*) ; 
 int drm_atomic_helper_prepare_planes (struct drm_device*,struct drm_atomic_state*) ; 
 int drm_atomic_helper_swap_state (struct drm_atomic_state*,int) ; 
 int /*<<< orphan*/  drm_atomic_state_get (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_atomic_complete (struct mtk_drm_private*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  mtk_atomic_schedule (struct mtk_drm_private*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_atomic_commit(struct drm_device *drm,
			     struct drm_atomic_state *state,
			     bool async)
{
	struct mtk_drm_private *private = drm->dev_private;
	int ret;

	ret = drm_atomic_helper_prepare_planes(drm, state);
	if (ret)
		return ret;

	mutex_lock(&private->commit.lock);
	flush_work(&private->commit.work);

	ret = drm_atomic_helper_swap_state(state, true);
	if (ret) {
		mutex_unlock(&private->commit.lock);
		drm_atomic_helper_cleanup_planes(drm, state);
		return ret;
	}

	drm_atomic_state_get(state);
	if (async)
		mtk_atomic_schedule(private, state);
	else
		mtk_atomic_complete(private, state);

	mutex_unlock(&private->commit.lock);

	return 0;
}