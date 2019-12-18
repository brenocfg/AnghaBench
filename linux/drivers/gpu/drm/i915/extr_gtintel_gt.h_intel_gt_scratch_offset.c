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
typedef  int u32 ;
struct intel_gt {int /*<<< orphan*/  scratch; } ;
typedef  enum intel_gt_scratch_field { ____Placeholder_intel_gt_scratch_field } intel_gt_scratch_field ;

/* Variables and functions */
 int i915_ggtt_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 intel_gt_scratch_offset(const struct intel_gt *gt,
					  enum intel_gt_scratch_field field)
{
	return i915_ggtt_offset(gt->scratch) + field;
}