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
struct TYPE_7__ {int /*<<< orphan*/  start; } ;
struct i915_vma {int flags; int /*<<< orphan*/  size; TYPE_3__ node; TYPE_4__* vm; } ;
struct i915_address_space {int /*<<< orphan*/  (* clear_range ) (struct i915_address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_1__* aliasing_ppgtt; } ;
struct drm_i915_private {TYPE_2__ mm; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* clear_range ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct drm_i915_private* i915; } ;
struct TYPE_5__ {struct i915_address_space vm; } ;

/* Variables and functions */
 int I915_VMA_GLOBAL_BIND ; 
 int I915_VMA_LOCAL_BIND ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct i915_address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aliasing_gtt_unbind_vma(struct i915_vma *vma)
{
	struct drm_i915_private *i915 = vma->vm->i915;

	if (vma->flags & I915_VMA_GLOBAL_BIND) {
		intel_runtime_pm_get(i915);
		vma->vm->clear_range(vma->vm, vma->node.start, vma->size);
		intel_runtime_pm_put(i915);
	}

	if (vma->flags & I915_VMA_LOCAL_BIND) {
		struct i915_address_space *vm = &i915->mm.aliasing_ppgtt->vm;

		vm->clear_range(vm, vma->node.start, vma->size);
	}
}