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
struct drm_syncobj_transfer {int /*<<< orphan*/  dst_point; int /*<<< orphan*/  flags; int /*<<< orphan*/  src_point; int /*<<< orphan*/  src_handle; int /*<<< orphan*/  dst_handle; } ;
struct drm_syncobj {int dummy; } ;
struct drm_file {int dummy; } ;
struct dma_fence_chain {int dummy; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  drm_syncobj_add_point (struct drm_syncobj*,struct dma_fence_chain*,struct dma_fence*,int /*<<< orphan*/ ) ; 
 struct drm_syncobj* drm_syncobj_find (struct drm_file*,int /*<<< orphan*/ ) ; 
 int drm_syncobj_find_fence (struct drm_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_fence**) ; 
 int /*<<< orphan*/  drm_syncobj_put (struct drm_syncobj*) ; 
 struct dma_fence_chain* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_syncobj_transfer_to_timeline(struct drm_file *file_private,
					    struct drm_syncobj_transfer *args)
{
	struct drm_syncobj *timeline_syncobj = NULL;
	struct dma_fence *fence;
	struct dma_fence_chain *chain;
	int ret;

	timeline_syncobj = drm_syncobj_find(file_private, args->dst_handle);
	if (!timeline_syncobj) {
		return -ENOENT;
	}
	ret = drm_syncobj_find_fence(file_private, args->src_handle,
				     args->src_point, args->flags,
				     &fence);
	if (ret)
		goto err;
	chain = kzalloc(sizeof(struct dma_fence_chain), GFP_KERNEL);
	if (!chain) {
		ret = -ENOMEM;
		goto err1;
	}
	drm_syncobj_add_point(timeline_syncobj, chain, fence, args->dst_point);
err1:
	dma_fence_put(fence);
err:
	drm_syncobj_put(timeline_syncobj);

	return ret;
}