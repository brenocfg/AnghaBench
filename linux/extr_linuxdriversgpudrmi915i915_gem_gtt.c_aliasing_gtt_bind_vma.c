#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  start; } ;
struct i915_vma {int flags; TYPE_3__* vm; int /*<<< orphan*/  size; TYPE_2__ node; int /*<<< orphan*/  obj; } ;
struct TYPE_9__ {int (* allocate_va_range ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* insert_entries ) (TYPE_4__*,struct i915_vma*,int,int) ;} ;
struct i915_hw_ppgtt {TYPE_4__ vm; } ;
struct TYPE_6__ {struct i915_hw_ppgtt* aliasing_ppgtt; } ;
struct drm_i915_private {TYPE_1__ mm; } ;
typedef  enum i915_cache_level { ____Placeholder_i915_cache_level } i915_cache_level ;
struct TYPE_8__ {int /*<<< orphan*/  (* insert_entries ) (TYPE_3__*,struct i915_vma*,int,int) ;struct drm_i915_private* i915; } ;

/* Variables and functions */
 int I915_VMA_GLOBAL_BIND ; 
 int I915_VMA_LOCAL_BIND ; 
 int PTE_READ_ONLY ; 
 scalar_t__ i915_gem_object_is_readonly (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,struct i915_vma*,int,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,struct i915_vma*,int,int) ; 

__attribute__((used)) static int aliasing_gtt_bind_vma(struct i915_vma *vma,
				 enum i915_cache_level cache_level,
				 u32 flags)
{
	struct drm_i915_private *i915 = vma->vm->i915;
	u32 pte_flags;
	int ret;

	/* Currently applicable only to VLV */
	pte_flags = 0;
	if (i915_gem_object_is_readonly(vma->obj))
		pte_flags |= PTE_READ_ONLY;

	if (flags & I915_VMA_LOCAL_BIND) {
		struct i915_hw_ppgtt *appgtt = i915->mm.aliasing_ppgtt;

		if (!(vma->flags & I915_VMA_LOCAL_BIND)) {
			ret = appgtt->vm.allocate_va_range(&appgtt->vm,
							   vma->node.start,
							   vma->size);
			if (ret)
				return ret;
		}

		appgtt->vm.insert_entries(&appgtt->vm, vma, cache_level,
					  pte_flags);
	}

	if (flags & I915_VMA_GLOBAL_BIND) {
		intel_runtime_pm_get(i915);
		vma->vm->insert_entries(vma->vm, vma, cache_level, pte_flags);
		intel_runtime_pm_put(i915);
	}

	return 0;
}