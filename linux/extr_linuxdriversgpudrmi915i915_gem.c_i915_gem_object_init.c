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
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  radix; } ;
struct TYPE_5__ {TYPE_1__ get_page; int /*<<< orphan*/  madv; int /*<<< orphan*/  lock; } ;
struct drm_i915_gem_object {TYPE_3__ base; TYPE_2__ mm; int /*<<< orphan*/  frontbuffer_write; int /*<<< orphan*/  frontbuffer_ggtt_origin; int /*<<< orphan*/  __builtin_resv; int /*<<< orphan*/ * resv; struct drm_i915_gem_object_ops const* ops; int /*<<< orphan*/  batch_pool_link; int /*<<< orphan*/  lut_list; int /*<<< orphan*/  vma_list; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int /*<<< orphan*/  I915_MADV_WILLNEED ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ORIGIN_GTT ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  frontbuffer_retire ; 
 int /*<<< orphan*/  i915_gem_info_add_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_request_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reservation_object_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_i915 (int /*<<< orphan*/ ) ; 

void i915_gem_object_init(struct drm_i915_gem_object *obj,
			  const struct drm_i915_gem_object_ops *ops)
{
	mutex_init(&obj->mm.lock);

	INIT_LIST_HEAD(&obj->vma_list);
	INIT_LIST_HEAD(&obj->lut_list);
	INIT_LIST_HEAD(&obj->batch_pool_link);

	obj->ops = ops;

	reservation_object_init(&obj->__builtin_resv);
	obj->resv = &obj->__builtin_resv;

	obj->frontbuffer_ggtt_origin = ORIGIN_GTT;
	init_request_active(&obj->frontbuffer_write, frontbuffer_retire);

	obj->mm.madv = I915_MADV_WILLNEED;
	INIT_RADIX_TREE(&obj->mm.get_page.radix, GFP_KERNEL | __GFP_NOWARN);
	mutex_init(&obj->mm.get_page.lock);

	i915_gem_info_add_obj(to_i915(obj->base.dev), obj->base.size);
}