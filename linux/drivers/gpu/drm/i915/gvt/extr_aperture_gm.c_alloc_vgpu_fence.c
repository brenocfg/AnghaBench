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
struct TYPE_4__ {struct i915_fence_reg** regs; } ;
struct intel_vgpu {TYPE_1__ fence; struct intel_gvt* gvt; } ;
struct intel_runtime_pm {int dummy; } ;
struct intel_gvt {struct drm_i915_private* dev_priv; } ;
struct i915_fence_reg {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_6__ {TYPE_2__ vm; } ;
struct drm_i915_private {TYPE_3__ ggtt; struct intel_runtime_pm runtime_pm; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ IS_ERR (struct i915_fence_reg*) ; 
 int /*<<< orphan*/  _clear_vgpu_fence (struct intel_vgpu*) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*) ; 
 struct i915_fence_reg* i915_reserve_fence (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_unreserve_fence (struct i915_fence_reg*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put_unchecked (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vgpu_fence_sz (struct intel_vgpu*) ; 

__attribute__((used)) static int alloc_vgpu_fence(struct intel_vgpu *vgpu)
{
	struct intel_gvt *gvt = vgpu->gvt;
	struct drm_i915_private *dev_priv = gvt->dev_priv;
	struct intel_runtime_pm *rpm = &dev_priv->runtime_pm;
	struct i915_fence_reg *reg;
	int i;

	intel_runtime_pm_get(rpm);

	/* Request fences from host */
	mutex_lock(&dev_priv->ggtt.vm.mutex);

	for (i = 0; i < vgpu_fence_sz(vgpu); i++) {
		reg = i915_reserve_fence(dev_priv);
		if (IS_ERR(reg))
			goto out_free_fence;

		vgpu->fence.regs[i] = reg;
	}

	_clear_vgpu_fence(vgpu);

	mutex_unlock(&dev_priv->ggtt.vm.mutex);
	intel_runtime_pm_put_unchecked(rpm);
	return 0;
out_free_fence:
	gvt_vgpu_err("Failed to alloc fences\n");
	/* Return fences to host, if fail */
	for (i = 0; i < vgpu_fence_sz(vgpu); i++) {
		reg = vgpu->fence.regs[i];
		if (!reg)
			continue;
		i915_unreserve_fence(reg);
		vgpu->fence.regs[i] = NULL;
	}
	mutex_unlock(&dev_priv->ggtt.vm.mutex);
	intel_runtime_pm_put_unchecked(rpm);
	return -ENOSPC;
}