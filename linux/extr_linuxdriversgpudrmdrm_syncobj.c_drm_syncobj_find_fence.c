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
typedef  int /*<<< orphan*/  u32 ;
struct drm_syncobj {int dummy; } ;
struct drm_file {int dummy; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 struct dma_fence* drm_syncobj_fence_get (struct drm_syncobj*) ; 
 struct drm_syncobj* drm_syncobj_find (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_syncobj_put (struct drm_syncobj*) ; 

int drm_syncobj_find_fence(struct drm_file *file_private,
			   u32 handle,
			   struct dma_fence **fence)
{
	struct drm_syncobj *syncobj = drm_syncobj_find(file_private, handle);
	int ret = 0;

	if (!syncobj)
		return -ENOENT;

	*fence = drm_syncobj_fence_get(syncobj);
	if (!*fence) {
		ret = -EINVAL;
	}
	drm_syncobj_put(syncobj);
	return ret;
}