#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sg_table {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  pages_pin_count; } ;
struct drm_i915_gem_object {TYPE_2__ mm; TYPE_1__* ops; int /*<<< orphan*/  bind_count; } ;
typedef  enum i915_mm_subclass { ____Placeholder_i915_mm_subclass } i915_mm_subclass ;
struct TYPE_3__ {int /*<<< orphan*/  (* put_pages ) (struct drm_i915_gem_object*,struct sg_table*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct sg_table*) ; 
 struct sg_table* __i915_gem_object_unset_pages (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_has_pages (struct drm_i915_gem_object*) ; 
 scalar_t__ i915_gem_object_has_pinned_pages (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_gem_object*,struct sg_table*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void __i915_gem_object_put_pages(struct drm_i915_gem_object *obj,
				 enum i915_mm_subclass subclass)
{
	struct sg_table *pages;

	if (i915_gem_object_has_pinned_pages(obj))
		return;

	GEM_BUG_ON(obj->bind_count);
	if (!i915_gem_object_has_pages(obj))
		return;

	/* May be called by shrinker from within get_pages() (on another bo) */
	mutex_lock_nested(&obj->mm.lock, subclass);
	if (unlikely(atomic_read(&obj->mm.pages_pin_count)))
		goto unlock;

	/*
	 * ->put_pages might need to allocate memory for the bit17 swizzle
	 * array, hence protect them from being reaped by removing them from gtt
	 * lists early.
	 */
	pages = __i915_gem_object_unset_pages(obj);
	if (!IS_ERR(pages))
		obj->ops->put_pages(obj, pages);

unlock:
	mutex_unlock(&obj->mm.lock);
}