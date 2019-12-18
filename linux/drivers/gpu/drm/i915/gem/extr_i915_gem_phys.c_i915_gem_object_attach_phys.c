#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sg_table {int /*<<< orphan*/  sgl; } ;
struct TYPE_6__ {scalar_t__ madv; int /*<<< orphan*/  lock; scalar_t__ mapping; scalar_t__ quirked; } ;
struct TYPE_5__ {int size; } ;
struct drm_i915_gem_object {TYPE_2__ mm; TYPE_3__* ops; TYPE_1__ base; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* put_pages ) (struct drm_i915_gem_object*,struct sg_table*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  I915_GEM_OBJECT_UNBIND_ACTIVE ; 
 scalar_t__ I915_MADV_WILLNEED ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct sg_table*) ; 
 int ____i915_gem_object_get_pages (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  __i915_gem_object_pin_pages (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  __i915_gem_object_set_pages (struct drm_i915_gem_object*,struct sg_table*,unsigned int) ; 
 struct sg_table* __i915_gem_object_unset_pages (struct drm_i915_gem_object*) ; 
 int i915_gem_object_unbind (struct drm_i915_gem_object*,int /*<<< orphan*/ ) ; 
 TYPE_3__ i915_gem_phys_ops ; 
 TYPE_3__ i915_gem_shmem_ops ; 
 unsigned int i915_sg_page_sizes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_gem_object*,struct sg_table*) ; 

int i915_gem_object_attach_phys(struct drm_i915_gem_object *obj, int align)
{
	struct sg_table *pages;
	int err;

	if (align > obj->base.size)
		return -EINVAL;

	if (obj->ops == &i915_gem_phys_ops)
		return 0;

	if (obj->ops != &i915_gem_shmem_ops)
		return -EINVAL;

	err = i915_gem_object_unbind(obj, I915_GEM_OBJECT_UNBIND_ACTIVE);
	if (err)
		return err;

	mutex_lock(&obj->mm.lock);

	if (obj->mm.madv != I915_MADV_WILLNEED) {
		err = -EFAULT;
		goto err_unlock;
	}

	if (obj->mm.quirked) {
		err = -EFAULT;
		goto err_unlock;
	}

	if (obj->mm.mapping) {
		err = -EBUSY;
		goto err_unlock;
	}

	pages = __i915_gem_object_unset_pages(obj);

	obj->ops = &i915_gem_phys_ops;

	err = ____i915_gem_object_get_pages(obj);
	if (err)
		goto err_xfer;

	/* Perma-pin (until release) the physical set of pages */
	__i915_gem_object_pin_pages(obj);

	if (!IS_ERR_OR_NULL(pages))
		i915_gem_shmem_ops.put_pages(obj, pages);
	mutex_unlock(&obj->mm.lock);
	return 0;

err_xfer:
	obj->ops = &i915_gem_shmem_ops;
	if (!IS_ERR_OR_NULL(pages)) {
		unsigned int sg_page_sizes = i915_sg_page_sizes(pages->sgl);

		__i915_gem_object_set_pages(obj, pages, sg_page_sizes);
	}
err_unlock:
	mutex_unlock(&obj->mm.lock);
	return err;
}