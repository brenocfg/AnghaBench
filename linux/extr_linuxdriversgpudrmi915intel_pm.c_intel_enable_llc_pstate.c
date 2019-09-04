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
struct TYPE_3__ {int enabled; } ;
struct TYPE_4__ {TYPE_1__ llc_pstate; } ;
struct drm_i915_private {TYPE_2__ gt_pm; int /*<<< orphan*/  pcu_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen6_update_ring_freq (struct drm_i915_private*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void intel_enable_llc_pstate(struct drm_i915_private *i915)
{
	lockdep_assert_held(&i915->pcu_lock);

	if (i915->gt_pm.llc_pstate.enabled)
		return;

	gen6_update_ring_freq(i915);

	i915->gt_pm.llc_pstate.enabled = true;
}