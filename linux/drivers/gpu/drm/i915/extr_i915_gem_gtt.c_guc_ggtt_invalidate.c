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
struct intel_uncore {int dummy; } ;
struct TYPE_4__ {TYPE_1__* gt; } ;
struct i915_ggtt {TYPE_2__ vm; } ;
struct TYPE_3__ {struct intel_uncore* uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN8_GTCR ; 
 int /*<<< orphan*/  GEN8_GTCR_INVALIDATE ; 
 int /*<<< orphan*/  gen6_ggtt_invalidate (struct i915_ggtt*) ; 
 int /*<<< orphan*/  intel_uncore_write_fw (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void guc_ggtt_invalidate(struct i915_ggtt *ggtt)
{
	struct intel_uncore *uncore = ggtt->vm.gt->uncore;

	gen6_ggtt_invalidate(ggtt);
	intel_uncore_write_fw(uncore, GEN8_GTCR, GEN8_GTCR_INVALIDATE);
}