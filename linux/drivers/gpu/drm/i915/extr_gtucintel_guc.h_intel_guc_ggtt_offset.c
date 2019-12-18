#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct intel_guc {int dummy; } ;
struct i915_vma {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GUC_GGTT_TOP ; 
 scalar_t__ i915_ggtt_offset (struct i915_vma*) ; 
 scalar_t__ i915_ggtt_pin_bias (struct i915_vma*) ; 
 int range_overflows_t (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64 ; 

__attribute__((used)) static inline u32 intel_guc_ggtt_offset(struct intel_guc *guc,
					struct i915_vma *vma)
{
	u32 offset = i915_ggtt_offset(vma);

	GEM_BUG_ON(offset < i915_ggtt_pin_bias(vma));
	GEM_BUG_ON(range_overflows_t(u64, offset, vma->size, GUC_GGTT_TOP));

	return offset;
}