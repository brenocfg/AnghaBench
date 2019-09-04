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
struct drm_syncobj_cb {int dummy; } ;
struct drm_syncobj {int /*<<< orphan*/  lock; scalar_t__ fence; } ;
struct dma_fence {int dummy; } ;
typedef  int /*<<< orphan*/  drm_syncobj_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (struct dma_fence*) ; 
 struct dma_fence* dma_fence_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_syncobj_add_callback_locked (struct drm_syncobj*,struct drm_syncobj_cb*,int /*<<< orphan*/ ) ; 
 struct dma_fence* drm_syncobj_fence_get (struct drm_syncobj*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_dereference_protected (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drm_syncobj_fence_get_or_add_callback(struct drm_syncobj *syncobj,
						 struct dma_fence **fence,
						 struct drm_syncobj_cb *cb,
						 drm_syncobj_func_t func)
{
	int ret;

	WARN_ON(*fence);

	*fence = drm_syncobj_fence_get(syncobj);
	if (*fence)
		return 1;

	spin_lock(&syncobj->lock);
	/* We've already tried once to get a fence and failed.  Now that we
	 * have the lock, try one more time just to be sure we don't add a
	 * callback when a fence has already been set.
	 */
	if (syncobj->fence) {
		*fence = dma_fence_get(rcu_dereference_protected(syncobj->fence,
								 lockdep_is_held(&syncobj->lock)));
		ret = 1;
	} else {
		*fence = NULL;
		drm_syncobj_add_callback_locked(syncobj, cb, func);
		ret = 0;
	}
	spin_unlock(&syncobj->lock);

	return ret;
}