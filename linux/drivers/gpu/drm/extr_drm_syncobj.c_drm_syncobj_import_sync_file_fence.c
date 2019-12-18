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
struct drm_syncobj {int dummy; } ;
struct drm_file {int dummy; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 struct drm_syncobj* drm_syncobj_find (struct drm_file*,int) ; 
 int /*<<< orphan*/  drm_syncobj_put (struct drm_syncobj*) ; 
 int /*<<< orphan*/  drm_syncobj_replace_fence (struct drm_syncobj*,struct dma_fence*) ; 
 struct dma_fence* sync_file_get_fence (int) ; 

__attribute__((used)) static int drm_syncobj_import_sync_file_fence(struct drm_file *file_private,
					      int fd, int handle)
{
	struct dma_fence *fence = sync_file_get_fence(fd);
	struct drm_syncobj *syncobj;

	if (!fence)
		return -EINVAL;

	syncobj = drm_syncobj_find(file_private, handle);
	if (!syncobj) {
		dma_fence_put(fence);
		return -ENOENT;
	}

	drm_syncobj_replace_fence(syncobj, fence);
	dma_fence_put(fence);
	drm_syncobj_put(syncobj);
	return 0;
}