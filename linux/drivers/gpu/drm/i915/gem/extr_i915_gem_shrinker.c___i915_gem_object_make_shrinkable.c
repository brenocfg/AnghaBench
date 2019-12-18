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
struct list_head {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  obj_lock; int /*<<< orphan*/  shrink_memory; int /*<<< orphan*/  shrink_count; } ;
struct drm_i915_private {TYPE_3__ mm; } ;
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/  refcount; } ;
struct TYPE_4__ {int /*<<< orphan*/  link; } ;
struct drm_i915_gem_object {TYPE_2__ base; TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  i915_gem_object_has_pages (struct drm_i915_gem_object*) ; 
 scalar_t__ i915_gem_object_is_shrinkable (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  kref_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* obj_to_i915 (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void __i915_gem_object_make_shrinkable(struct drm_i915_gem_object *obj,
					      struct list_head *head)
{
	GEM_BUG_ON(!i915_gem_object_has_pages(obj));
	GEM_BUG_ON(!list_empty(&obj->mm.link));

	if (i915_gem_object_is_shrinkable(obj)) {
		struct drm_i915_private *i915 = obj_to_i915(obj);
		unsigned long flags;

		spin_lock_irqsave(&i915->mm.obj_lock, flags);
		GEM_BUG_ON(!kref_read(&obj->base.refcount));

		list_add_tail(&obj->mm.link, head);
		i915->mm.shrink_count++;
		i915->mm.shrink_memory += obj->base.size;

		spin_unlock_irqrestore(&i915->mm.obj_lock, flags);
	}
}