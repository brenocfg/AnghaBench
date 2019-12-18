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
typedef  size_t u32 ;
struct TYPE_4__ {struct i915_fence_reg** regs; } ;
struct intel_vgpu {TYPE_1__ fence; struct intel_gvt* gvt; } ;
struct intel_gvt {struct drm_i915_private* dev_priv; } ;
struct i915_fence_reg {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_6__ {TYPE_2__ vm; } ;
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; TYPE_3__ ggtt; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  _clear_vgpu_fence (struct intel_vgpu*) ; 
 int /*<<< orphan*/  i915_unreserve_fence (struct i915_fence_reg*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put_unchecked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t vgpu_fence_sz (struct intel_vgpu*) ; 

__attribute__((used)) static void free_vgpu_fence(struct intel_vgpu *vgpu)
{
	struct intel_gvt *gvt = vgpu->gvt;
	struct drm_i915_private *dev_priv = gvt->dev_priv;
	struct i915_fence_reg *reg;
	u32 i;

	if (WARN_ON(!vgpu_fence_sz(vgpu)))
		return;

	intel_runtime_pm_get(&dev_priv->runtime_pm);

	mutex_lock(&dev_priv->ggtt.vm.mutex);
	_clear_vgpu_fence(vgpu);
	for (i = 0; i < vgpu_fence_sz(vgpu); i++) {
		reg = vgpu->fence.regs[i];
		i915_unreserve_fence(reg);
		vgpu->fence.regs[i] = NULL;
	}
	mutex_unlock(&dev_priv->ggtt.vm.mutex);

	intel_runtime_pm_put_unchecked(&dev_priv->runtime_pm);
}