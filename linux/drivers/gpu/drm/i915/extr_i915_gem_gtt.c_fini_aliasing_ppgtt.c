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
struct i915_ppgtt {int /*<<< orphan*/  vm; } ;
struct TYPE_4__ {int /*<<< orphan*/  unbind_vma; int /*<<< orphan*/  bind_vma; } ;
struct TYPE_5__ {TYPE_1__ vma_ops; struct drm_i915_private* i915; } ;
struct i915_ggtt {TYPE_2__ vm; int /*<<< orphan*/  alias; } ;
struct TYPE_6__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_3__ drm; } ;

/* Variables and functions */
 struct i915_ppgtt* fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ggtt_bind_vma ; 
 int /*<<< orphan*/  ggtt_unbind_vma ; 
 int /*<<< orphan*/  i915_vm_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fini_aliasing_ppgtt(struct i915_ggtt *ggtt)
{
	struct drm_i915_private *i915 = ggtt->vm.i915;
	struct i915_ppgtt *ppgtt;

	mutex_lock(&i915->drm.struct_mutex);

	ppgtt = fetch_and_zero(&ggtt->alias);
	if (!ppgtt)
		goto out;

	i915_vm_put(&ppgtt->vm);

	ggtt->vm.vma_ops.bind_vma   = ggtt_bind_vma;
	ggtt->vm.vma_ops.unbind_vma = ggtt_unbind_vma;

out:
	mutex_unlock(&i915->drm.struct_mutex);
}