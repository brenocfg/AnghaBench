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
struct TYPE_6__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  interactive; } ;
struct intel_rps {TYPE_3__ power; } ;
struct TYPE_4__ {int /*<<< orphan*/  awake; } ;
struct TYPE_5__ {struct intel_rps rps; } ;
struct drm_i915_private {TYPE_1__ gt; TYPE_2__ gt_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  HIGH_POWER ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rps_set_power (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

void intel_rps_mark_interactive(struct drm_i915_private *i915, bool interactive)
{
	struct intel_rps *rps = &i915->gt_pm.rps;

	if (INTEL_GEN(i915) < 6)
		return;

	mutex_lock(&rps->power.mutex);
	if (interactive) {
		if (!rps->power.interactive++ && READ_ONCE(i915->gt.awake))
			rps_set_power(i915, HIGH_POWER);
	} else {
		GEM_BUG_ON(!rps->power.interactive);
		rps->power.interactive--;
	}
	mutex_unlock(&rps->power.mutex);
}