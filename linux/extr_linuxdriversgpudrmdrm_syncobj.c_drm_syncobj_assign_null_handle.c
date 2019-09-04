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
struct drm_syncobj_null_fence {int /*<<< orphan*/  base; int /*<<< orphan*/  lock; } ;
struct drm_syncobj {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_fence_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_syncobj_null_fence_ops ; 
 int /*<<< orphan*/  drm_syncobj_replace_fence (struct drm_syncobj*,int /*<<< orphan*/ *) ; 
 struct drm_syncobj_null_fence* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drm_syncobj_assign_null_handle(struct drm_syncobj *syncobj)
{
	struct drm_syncobj_null_fence *fence;
	fence = kzalloc(sizeof(*fence), GFP_KERNEL);
	if (fence == NULL)
		return -ENOMEM;

	spin_lock_init(&fence->lock);
	dma_fence_init(&fence->base, &drm_syncobj_null_fence_ops,
		       &fence->lock, 0, 0);
	dma_fence_signal(&fence->base);

	drm_syncobj_replace_fence(syncobj, &fence->base);

	dma_fence_put(&fence->base);

	return 0;
}