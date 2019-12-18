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
typedef  int uint32_t ;
struct drm_syncobj {int /*<<< orphan*/  lock; int /*<<< orphan*/  cb_list; int /*<<< orphan*/  refcount; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int DRM_SYNCOBJ_CREATE_SIGNALED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_syncobj_assign_null_handle (struct drm_syncobj*) ; 
 int /*<<< orphan*/  drm_syncobj_replace_fence (struct drm_syncobj*,struct dma_fence*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct drm_syncobj* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int drm_syncobj_create(struct drm_syncobj **out_syncobj, uint32_t flags,
		       struct dma_fence *fence)
{
	struct drm_syncobj *syncobj;

	syncobj = kzalloc(sizeof(struct drm_syncobj), GFP_KERNEL);
	if (!syncobj)
		return -ENOMEM;

	kref_init(&syncobj->refcount);
	INIT_LIST_HEAD(&syncobj->cb_list);
	spin_lock_init(&syncobj->lock);

	if (flags & DRM_SYNCOBJ_CREATE_SIGNALED)
		drm_syncobj_assign_null_handle(syncobj);

	if (fence)
		drm_syncobj_replace_fence(syncobj, fence);

	*out_syncobj = syncobj;
	return 0;
}