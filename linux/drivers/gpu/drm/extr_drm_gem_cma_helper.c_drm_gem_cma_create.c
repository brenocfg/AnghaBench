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
struct drm_gem_cma_object {int /*<<< orphan*/  base; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  paddr; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct drm_gem_cma_object* ERR_PTR (int) ; 
 int GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct drm_gem_cma_object*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __GFP_NOWARN ; 
 struct drm_gem_cma_object* __drm_gem_cma_create (struct drm_device*,size_t) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  dma_alloc_wc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 size_t round_up (size_t,int /*<<< orphan*/ ) ; 

struct drm_gem_cma_object *drm_gem_cma_create(struct drm_device *drm,
					      size_t size)
{
	struct drm_gem_cma_object *cma_obj;
	int ret;

	size = round_up(size, PAGE_SIZE);

	cma_obj = __drm_gem_cma_create(drm, size);
	if (IS_ERR(cma_obj))
		return cma_obj;

	cma_obj->vaddr = dma_alloc_wc(drm->dev, size, &cma_obj->paddr,
				      GFP_KERNEL | __GFP_NOWARN);
	if (!cma_obj->vaddr) {
		dev_dbg(drm->dev, "failed to allocate buffer with size %zu\n",
			size);
		ret = -ENOMEM;
		goto error;
	}

	return cma_obj;

error:
	drm_gem_object_put_unlocked(&cma_obj->base);
	return ERR_PTR(ret);
}