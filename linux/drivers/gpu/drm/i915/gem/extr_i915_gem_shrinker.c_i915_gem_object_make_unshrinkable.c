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
struct TYPE_6__ {int /*<<< orphan*/  obj_lock; int /*<<< orphan*/  shrink_memory; int /*<<< orphan*/  shrink_count; } ;
struct drm_i915_private {TYPE_3__ mm; } ;
struct TYPE_4__ {scalar_t__ size; } ;
struct TYPE_5__ {int /*<<< orphan*/  link; } ;
struct drm_i915_gem_object {TYPE_1__ base; TYPE_2__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* obj_to_i915 (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void i915_gem_object_make_unshrinkable(struct drm_i915_gem_object *obj)
{
	/*
	 * We can only be called while the pages are pinned or when
	 * the pages are released. If pinned, we should only be called
	 * from a single caller under controlled conditions; and on release
	 * only one caller may release us. Neither the two may cross.
	 */
	if (!list_empty(&obj->mm.link)) { /* pinned by caller */
		struct drm_i915_private *i915 = obj_to_i915(obj);
		unsigned long flags;

		spin_lock_irqsave(&i915->mm.obj_lock, flags);
		GEM_BUG_ON(list_empty(&obj->mm.link));

		list_del_init(&obj->mm.link);
		i915->mm.shrink_count--;
		i915->mm.shrink_memory -= obj->base.size;

		spin_unlock_irqrestore(&i915->mm.obj_lock, flags);
	}
}