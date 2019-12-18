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
struct TYPE_2__ {int /*<<< orphan*/  total; int /*<<< orphan*/  (* clear_range ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  gt; struct drm_i915_private* i915; } ;
struct i915_ggtt {int /*<<< orphan*/  (* invalidate ) (struct i915_ggtt*) ;TYPE_1__ vm; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gt_check_and_clear_faults (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct i915_ggtt*) ; 

__attribute__((used)) static void ggtt_suspend_mappings(struct i915_ggtt *ggtt)
{
	struct drm_i915_private *i915 = ggtt->vm.i915;

	/* Don't bother messing with faults pre GEN6 as we have little
	 * documentation supporting that it's a good idea.
	 */
	if (INTEL_GEN(i915) < 6)
		return;

	intel_gt_check_and_clear_faults(ggtt->vm.gt);

	ggtt->vm.clear_range(&ggtt->vm, 0, ggtt->vm.total);

	ggtt->invalidate(ggtt);
}