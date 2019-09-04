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
struct TYPE_3__ {int /*<<< orphan*/  flush_wq; } ;
struct TYPE_4__ {TYPE_1__ relay; } ;
struct intel_guc {TYPE_2__ log; int /*<<< orphan*/  preempt_wq; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ HAS_LOGICAL_RING_PREEMPTION (struct drm_i915_private*) ; 
 scalar_t__ USES_GUC_SUBMISSION (struct drm_i915_private*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 

__attribute__((used)) static void guc_fini_wq(struct intel_guc *guc)
{
	struct drm_i915_private *dev_priv = guc_to_i915(guc);

	if (HAS_LOGICAL_RING_PREEMPTION(dev_priv) &&
	    USES_GUC_SUBMISSION(dev_priv))
		destroy_workqueue(guc->preempt_wq);

	destroy_workqueue(guc->log.relay.flush_wq);
}