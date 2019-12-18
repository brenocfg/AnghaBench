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
typedef  int /*<<< orphan*/  u32 ;
struct intel_gt {TYPE_1__* i915; } ;
typedef  int /*<<< orphan*/  intel_engine_mask_t ;
struct TYPE_2__ {int /*<<< orphan*/  gpu_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_reset_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_gt_reset (struct intel_gt*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 fake_hangcheck(struct intel_gt *gt, intel_engine_mask_t mask)
{
	u32 count = i915_reset_count(&gt->i915->gpu_error);

	intel_gt_reset(gt, mask, NULL);

	return count;
}