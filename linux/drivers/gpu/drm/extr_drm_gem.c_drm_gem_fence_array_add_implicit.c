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
struct xarray {int dummy; } ;
struct drm_gem_object {int /*<<< orphan*/  resv; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 struct dma_fence* dma_resv_get_excl_rcu (int /*<<< orphan*/ ) ; 
 int dma_resv_get_fences_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int*,struct dma_fence***) ; 
 int drm_gem_fence_array_add (struct xarray*,struct dma_fence*) ; 
 int /*<<< orphan*/  kfree (struct dma_fence**) ; 

int drm_gem_fence_array_add_implicit(struct xarray *fence_array,
				     struct drm_gem_object *obj,
				     bool write)
{
	int ret;
	struct dma_fence **fences;
	unsigned int i, fence_count;

	if (!write) {
		struct dma_fence *fence =
			dma_resv_get_excl_rcu(obj->resv);

		return drm_gem_fence_array_add(fence_array, fence);
	}

	ret = dma_resv_get_fences_rcu(obj->resv, NULL,
						&fence_count, &fences);
	if (ret || !fence_count)
		return ret;

	for (i = 0; i < fence_count; i++) {
		ret = drm_gem_fence_array_add(fence_array, fences[i]);
		if (ret)
			break;
	}

	for (; i < fence_count; i++)
		dma_fence_put(fences[i]);
	kfree(fences);
	return ret;
}