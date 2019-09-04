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
struct TYPE_8__ {scalar_t__ total; int (* allocate_va_range ) (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ;} ;
struct i915_hw_ppgtt {TYPE_4__ vm; } ;
struct TYPE_6__ {scalar_t__ bind_vma; scalar_t__ unbind_vma; } ;
struct TYPE_7__ {scalar_t__ total; TYPE_2__ vma_ops; } ;
struct i915_ggtt {TYPE_3__ vm; } ;
struct TYPE_5__ {struct i915_hw_ppgtt* aliasing_ppgtt; } ;
struct drm_i915_private {TYPE_1__ mm; struct i915_ggtt ggtt; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ GEM_WARN_ON (int) ; 
 scalar_t__ IS_ERR (struct i915_hw_ppgtt*) ; 
 int PTR_ERR (struct i915_hw_ppgtt*) ; 
 scalar_t__ aliasing_gtt_bind_vma ; 
 scalar_t__ aliasing_gtt_unbind_vma ; 
 scalar_t__ ggtt_bind_vma ; 
 scalar_t__ ggtt_unbind_vma ; 
 struct i915_hw_ppgtt* i915_ppgtt_create (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_ppgtt_put (struct i915_hw_ppgtt*) ; 
 int stub1 (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 

int i915_gem_init_aliasing_ppgtt(struct drm_i915_private *i915)
{
	struct i915_ggtt *ggtt = &i915->ggtt;
	struct i915_hw_ppgtt *ppgtt;
	int err;

	ppgtt = i915_ppgtt_create(i915, ERR_PTR(-EPERM));
	if (IS_ERR(ppgtt))
		return PTR_ERR(ppgtt);

	if (GEM_WARN_ON(ppgtt->vm.total < ggtt->vm.total)) {
		err = -ENODEV;
		goto err_ppgtt;
	}

	/*
	 * Note we only pre-allocate as far as the end of the global
	 * GTT. On 48b / 4-level page-tables, the difference is very,
	 * very significant! We have to preallocate as GVT/vgpu does
	 * not like the page directory disappearing.
	 */
	err = ppgtt->vm.allocate_va_range(&ppgtt->vm, 0, ggtt->vm.total);
	if (err)
		goto err_ppgtt;

	i915->mm.aliasing_ppgtt = ppgtt;

	GEM_BUG_ON(ggtt->vm.vma_ops.bind_vma != ggtt_bind_vma);
	ggtt->vm.vma_ops.bind_vma = aliasing_gtt_bind_vma;

	GEM_BUG_ON(ggtt->vm.vma_ops.unbind_vma != ggtt_unbind_vma);
	ggtt->vm.vma_ops.unbind_vma = aliasing_gtt_unbind_vma;

	return 0;

err_ppgtt:
	i915_ppgtt_put(ppgtt);
	return err;
}