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
struct drm_i915_gem_object_ops {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  radix; } ;
struct TYPE_6__ {TYPE_2__ get_page; int /*<<< orphan*/  madv; int /*<<< orphan*/  link; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct drm_i915_gem_object {TYPE_3__ mm; struct drm_i915_gem_object_ops const* ops; int /*<<< orphan*/  rcu; int /*<<< orphan*/  lut_list; TYPE_1__ vma; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int /*<<< orphan*/  I915_MADV_WILLNEED ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int) ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  init_rcu_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void i915_gem_object_init(struct drm_i915_gem_object *obj,
			  const struct drm_i915_gem_object_ops *ops)
{
	mutex_init(&obj->mm.lock);

	spin_lock_init(&obj->vma.lock);
	INIT_LIST_HEAD(&obj->vma.list);

	INIT_LIST_HEAD(&obj->mm.link);

	INIT_LIST_HEAD(&obj->lut_list);

	init_rcu_head(&obj->rcu);

	obj->ops = ops;

	obj->mm.madv = I915_MADV_WILLNEED;
	INIT_RADIX_TREE(&obj->mm.get_page.radix, GFP_KERNEL | __GFP_NOWARN);
	mutex_init(&obj->mm.get_page.lock);
}