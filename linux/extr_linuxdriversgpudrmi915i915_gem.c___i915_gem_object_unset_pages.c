#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sg_table {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  obj_lock; } ;
struct drm_i915_private {TYPE_2__ mm; } ;
struct TYPE_7__ {scalar_t__ sg; scalar_t__ phys; } ;
struct TYPE_8__ {TYPE_3__ page_sizes; int /*<<< orphan*/ * mapping; int /*<<< orphan*/  link; int /*<<< orphan*/  pages; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {TYPE_4__ mm; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __i915_gem_object_reset_page_iter (struct drm_i915_gem_object*) ; 
 struct sg_table* fetch_and_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ is_vmalloc_addr (void*) ; 
 int /*<<< orphan*/  kmap_to_page (void*) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 void* page_mask_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vunmap (void*) ; 

__attribute__((used)) static struct sg_table *
__i915_gem_object_unset_pages(struct drm_i915_gem_object *obj)
{
	struct drm_i915_private *i915 = to_i915(obj->base.dev);
	struct sg_table *pages;

	pages = fetch_and_zero(&obj->mm.pages);
	if (!pages)
		return NULL;

	spin_lock(&i915->mm.obj_lock);
	list_del(&obj->mm.link);
	spin_unlock(&i915->mm.obj_lock);

	if (obj->mm.mapping) {
		void *ptr;

		ptr = page_mask_bits(obj->mm.mapping);
		if (is_vmalloc_addr(ptr))
			vunmap(ptr);
		else
			kunmap(kmap_to_page(ptr));

		obj->mm.mapping = NULL;
	}

	__i915_gem_object_reset_page_iter(obj);
	obj->mm.page_sizes.phys = obj->mm.page_sizes.sg = 0;

	return pages;
}