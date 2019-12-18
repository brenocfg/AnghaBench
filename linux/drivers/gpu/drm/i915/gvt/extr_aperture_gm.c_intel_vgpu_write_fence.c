#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct TYPE_2__ {struct i915_fence_reg** regs; } ;
struct intel_vgpu {TYPE_1__ fence; struct intel_gvt* gvt; } ;
struct intel_gvt {struct drm_i915_private* dev_priv; } ;
struct i915_fence_reg {int /*<<< orphan*/  id; } ;
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  FENCE_REG_GEN6_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FENCE_REG_GEN6_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  assert_rpm_wakelock_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 
 size_t vgpu_fence_sz (struct intel_vgpu*) ; 

void intel_vgpu_write_fence(struct intel_vgpu *vgpu,
		u32 fence, u64 value)
{
	struct intel_gvt *gvt = vgpu->gvt;
	struct drm_i915_private *dev_priv = gvt->dev_priv;
	struct i915_fence_reg *reg;
	i915_reg_t fence_reg_lo, fence_reg_hi;

	assert_rpm_wakelock_held(&dev_priv->runtime_pm);

	if (WARN_ON(fence >= vgpu_fence_sz(vgpu)))
		return;

	reg = vgpu->fence.regs[fence];
	if (WARN_ON(!reg))
		return;

	fence_reg_lo = FENCE_REG_GEN6_LO(reg->id);
	fence_reg_hi = FENCE_REG_GEN6_HI(reg->id);

	I915_WRITE(fence_reg_lo, 0);
	POSTING_READ(fence_reg_lo);

	I915_WRITE(fence_reg_hi, upper_32_bits(value));
	I915_WRITE(fence_reg_lo, lower_32_bits(value));
	POSTING_READ(fence_reg_lo);
}