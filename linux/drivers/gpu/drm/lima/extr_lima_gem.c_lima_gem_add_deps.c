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
struct lima_submit {TYPE_1__* task; int /*<<< orphan*/ * in_sync; } ;
struct drm_file {int dummy; } ;
struct dma_fence {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  deps; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int drm_gem_fence_array_add (int /*<<< orphan*/ *,struct dma_fence*) ; 
 int drm_syncobj_find_fence (struct drm_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_fence**) ; 

__attribute__((used)) static int lima_gem_add_deps(struct drm_file *file, struct lima_submit *submit)
{
	int i, err;

	for (i = 0; i < ARRAY_SIZE(submit->in_sync); i++) {
		struct dma_fence *fence = NULL;

		if (!submit->in_sync[i])
			continue;

		err = drm_syncobj_find_fence(file, submit->in_sync[i],
					     0, 0, &fence);
		if (err)
			return err;

		err = drm_gem_fence_array_add(&submit->task->deps, fence);
		if (err) {
			dma_fence_put(fence);
			return err;
		}
	}

	return 0;
}