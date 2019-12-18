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
typedef  int u64 ;
struct intel_uncore {int dummy; } ;
struct TYPE_3__ {unsigned int start; } ;
struct i915_vma {unsigned int fence_size; int /*<<< orphan*/  obj; TYPE_1__ node; } ;
struct i915_fence_reg {TYPE_2__* i915; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
struct TYPE_4__ {struct intel_uncore uncore; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FENCE_REG_965_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FENCE_REG_965_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FENCE_REG_GEN6_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FENCE_REG_GEN6_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int GEN6_FENCE_PITCH_SHIFT ; 
 scalar_t__ I915_TILING_Y ; 
 int I965_FENCE_PAGE ; 
 int I965_FENCE_PITCH_SHIFT ; 
 int I965_FENCE_REG_VALID ; 
 int /*<<< orphan*/  I965_FENCE_TILING_Y_SHIFT ; 
 int INTEL_GEN (TYPE_2__*) ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned int,int) ; 
 unsigned int i915_gem_object_get_stride (int /*<<< orphan*/ ) ; 
 scalar_t__ i915_gem_object_get_tiling (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_is_map_and_fenceable (struct i915_vma*) ; 
 int /*<<< orphan*/  intel_uncore_posting_read_fw (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write_fw (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int) ; 
 int /*<<< orphan*/  pipelined ; 
 int /*<<< orphan*/  upper_32_bits (int) ; 

__attribute__((used)) static void i965_write_fence_reg(struct i915_fence_reg *fence,
				 struct i915_vma *vma)
{
	i915_reg_t fence_reg_lo, fence_reg_hi;
	int fence_pitch_shift;
	u64 val;

	if (INTEL_GEN(fence->i915) >= 6) {
		fence_reg_lo = FENCE_REG_GEN6_LO(fence->id);
		fence_reg_hi = FENCE_REG_GEN6_HI(fence->id);
		fence_pitch_shift = GEN6_FENCE_PITCH_SHIFT;

	} else {
		fence_reg_lo = FENCE_REG_965_LO(fence->id);
		fence_reg_hi = FENCE_REG_965_HI(fence->id);
		fence_pitch_shift = I965_FENCE_PITCH_SHIFT;
	}

	val = 0;
	if (vma) {
		unsigned int stride = i915_gem_object_get_stride(vma->obj);

		GEM_BUG_ON(!i915_vma_is_map_and_fenceable(vma));
		GEM_BUG_ON(!IS_ALIGNED(vma->node.start, I965_FENCE_PAGE));
		GEM_BUG_ON(!IS_ALIGNED(vma->fence_size, I965_FENCE_PAGE));
		GEM_BUG_ON(!IS_ALIGNED(stride, 128));

		val = (vma->node.start + vma->fence_size - I965_FENCE_PAGE) << 32;
		val |= vma->node.start;
		val |= (u64)((stride / 128) - 1) << fence_pitch_shift;
		if (i915_gem_object_get_tiling(vma->obj) == I915_TILING_Y)
			val |= BIT(I965_FENCE_TILING_Y_SHIFT);
		val |= I965_FENCE_REG_VALID;
	}

	if (!pipelined) {
		struct intel_uncore *uncore = &fence->i915->uncore;

		/*
		 * To w/a incoherency with non-atomic 64-bit register updates,
		 * we split the 64-bit update into two 32-bit writes. In order
		 * for a partial fence not to be evaluated between writes, we
		 * precede the update with write to turn off the fence register,
		 * and only enable the fence as the last step.
		 *
		 * For extra levels of paranoia, we make sure each step lands
		 * before applying the next step.
		 */
		intel_uncore_write_fw(uncore, fence_reg_lo, 0);
		intel_uncore_posting_read_fw(uncore, fence_reg_lo);

		intel_uncore_write_fw(uncore, fence_reg_hi, upper_32_bits(val));
		intel_uncore_write_fw(uncore, fence_reg_lo, lower_32_bits(val));
		intel_uncore_posting_read_fw(uncore, fence_reg_lo);
	}
}