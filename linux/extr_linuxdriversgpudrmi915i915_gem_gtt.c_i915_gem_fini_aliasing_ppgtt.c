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
struct i915_hw_ppgtt {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  unbind_vma; int /*<<< orphan*/  bind_vma; } ;
struct TYPE_6__ {TYPE_2__ vma_ops; } ;
struct i915_ggtt {TYPE_3__ vm; } ;
struct TYPE_4__ {int /*<<< orphan*/  aliasing_ppgtt; } ;
struct drm_i915_private {TYPE_1__ mm; struct i915_ggtt ggtt; } ;

/* Variables and functions */
 struct i915_hw_ppgtt* fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ggtt_bind_vma ; 
 int /*<<< orphan*/  ggtt_unbind_vma ; 
 int /*<<< orphan*/  i915_ppgtt_put (struct i915_hw_ppgtt*) ; 

void i915_gem_fini_aliasing_ppgtt(struct drm_i915_private *i915)
{
	struct i915_ggtt *ggtt = &i915->ggtt;
	struct i915_hw_ppgtt *ppgtt;

	ppgtt = fetch_and_zero(&i915->mm.aliasing_ppgtt);
	if (!ppgtt)
		return;

	i915_ppgtt_put(ppgtt);

	ggtt->vm.vma_ops.bind_vma   = ggtt_bind_vma;
	ggtt->vm.vma_ops.unbind_vma = ggtt_unbind_vma;
}