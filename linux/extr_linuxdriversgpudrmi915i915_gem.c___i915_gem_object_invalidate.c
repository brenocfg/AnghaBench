#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* filp; } ;
struct TYPE_4__ {int madv; int /*<<< orphan*/  lock; } ;
struct drm_i915_gem_object {TYPE_3__ base; TYPE_1__ mm; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_5__ {struct address_space* f_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
#define  I915_MADV_DONTNEED 129 
#define  __I915_MADV_PURGED 128 
 int /*<<< orphan*/  i915_gem_object_has_pages (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_truncate (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  invalidate_mapping_pages (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void __i915_gem_object_invalidate(struct drm_i915_gem_object *obj)
{
	struct address_space *mapping;

	lockdep_assert_held(&obj->mm.lock);
	GEM_BUG_ON(i915_gem_object_has_pages(obj));

	switch (obj->mm.madv) {
	case I915_MADV_DONTNEED:
		i915_gem_object_truncate(obj);
	case __I915_MADV_PURGED:
		return;
	}

	if (obj->base.filp == NULL)
		return;

	mapping = obj->base.filp->f_mapping,
	invalidate_mapping_pages(mapping, 0, (loff_t)-1);
}