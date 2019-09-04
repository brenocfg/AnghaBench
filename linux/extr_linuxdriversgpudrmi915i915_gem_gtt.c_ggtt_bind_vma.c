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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  gtt; } ;
struct i915_vma {int flags; TYPE_1__ page_sizes; TYPE_2__* vm; struct drm_i915_gem_object* obj; } ;
struct drm_i915_private {int dummy; } ;
struct drm_i915_gem_object {int dummy; } ;
typedef  enum i915_cache_level { ____Placeholder_i915_cache_level } i915_cache_level ;
struct TYPE_4__ {int /*<<< orphan*/  (* insert_entries ) (TYPE_2__*,struct i915_vma*,int,int /*<<< orphan*/ ) ;struct drm_i915_private* i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_GTT_PAGE_SIZE ; 
 int I915_VMA_GLOBAL_BIND ; 
 int I915_VMA_LOCAL_BIND ; 
 int /*<<< orphan*/  PTE_READ_ONLY ; 
 scalar_t__ i915_gem_object_is_readonly (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct i915_vma*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ggtt_bind_vma(struct i915_vma *vma,
			 enum i915_cache_level cache_level,
			 u32 flags)
{
	struct drm_i915_private *i915 = vma->vm->i915;
	struct drm_i915_gem_object *obj = vma->obj;
	u32 pte_flags;

	/* Applicable to VLV (gen8+ do not support RO in the GGTT) */
	pte_flags = 0;
	if (i915_gem_object_is_readonly(obj))
		pte_flags |= PTE_READ_ONLY;

	intel_runtime_pm_get(i915);
	vma->vm->insert_entries(vma->vm, vma, cache_level, pte_flags);
	intel_runtime_pm_put(i915);

	vma->page_sizes.gtt = I915_GTT_PAGE_SIZE;

	/*
	 * Without aliasing PPGTT there's no difference between
	 * GLOBAL/LOCAL_BIND, it's all the same ptes. Hence unconditionally
	 * upgrade to both bound if we bind either to avoid double-binding.
	 */
	vma->flags |= I915_VMA_GLOBAL_BIND | I915_VMA_LOCAL_BIND;

	return 0;
}