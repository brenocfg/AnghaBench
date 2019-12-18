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
typedef  scalar_t__ u32 ;
struct regmask {int gen_mask; int /*<<< orphan*/  reg; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
struct TYPE_2__ {int gen_mask; } ;

/* Variables and functions */
 TYPE_1__* INTEL_INFO (struct drm_i915_private*) ; 
 scalar_t__ i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool find_reg(struct drm_i915_private *i915,
		     i915_reg_t reg,
		     const struct regmask *tbl,
		     unsigned long count)
{
	u32 offset = i915_mmio_reg_offset(reg);

	while (count--) {
		if (INTEL_INFO(i915)->gen_mask & tbl->gen_mask &&
		    i915_mmio_reg_offset(tbl->reg) == offset)
			return true;
		tbl++;
	}

	return false;
}