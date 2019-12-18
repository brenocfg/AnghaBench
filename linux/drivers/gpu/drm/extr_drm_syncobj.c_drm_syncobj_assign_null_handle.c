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
struct dma_fence {int dummy; } ;

/* Variables and functions */
 struct dma_fence* dma_fence_get_stub () ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  drm_syncobj_replace_fence (struct drm_syncobj*,struct dma_fence*) ; 

__attribute__((used)) static void drm_syncobj_assign_null_handle(struct drm_syncobj *syncobj)
{
	struct dma_fence *fence = dma_fence_get_stub();

	drm_syncobj_replace_fence(syncobj, fence);
	dma_fence_put(fence);
}