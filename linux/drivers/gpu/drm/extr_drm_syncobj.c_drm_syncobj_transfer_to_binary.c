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
struct drm_syncobj_transfer {int /*<<< orphan*/  flags; int /*<<< orphan*/  src_point; int /*<<< orphan*/  src_handle; int /*<<< orphan*/  dst_handle; } ;
struct drm_syncobj {int dummy; } ;
struct drm_file {int dummy; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 struct drm_syncobj* drm_syncobj_find (struct drm_file*,int /*<<< orphan*/ ) ; 
 int drm_syncobj_find_fence (struct drm_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_fence**) ; 
 int /*<<< orphan*/  drm_syncobj_put (struct drm_syncobj*) ; 
 int /*<<< orphan*/  drm_syncobj_replace_fence (struct drm_syncobj*,struct dma_fence*) ; 

__attribute__((used)) static int
drm_syncobj_transfer_to_binary(struct drm_file *file_private,
			       struct drm_syncobj_transfer *args)
{
	struct drm_syncobj *binary_syncobj = NULL;
	struct dma_fence *fence;
	int ret;

	binary_syncobj = drm_syncobj_find(file_private, args->dst_handle);
	if (!binary_syncobj)
		return -ENOENT;
	ret = drm_syncobj_find_fence(file_private, args->src_handle,
				     args->src_point, args->flags, &fence);
	if (ret)
		goto err;
	drm_syncobj_replace_fence(binary_syncobj, fence);
	dma_fence_put(fence);
err:
	drm_syncobj_put(binary_syncobj);

	return ret;
}