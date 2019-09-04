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
struct TYPE_3__ {void* flush_wq; } ;
struct TYPE_4__ {TYPE_1__ relay; } ;
struct intel_guc {TYPE_2__ log; void* preempt_wq; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 scalar_t__ HAS_LOGICAL_RING_PREEMPTION (struct drm_i915_private*) ; 
 scalar_t__ USES_GUC_SUBMISSION (struct drm_i915_private*) ; 
 int WQ_FREEZABLE ; 
 int WQ_HIGHPRI ; 
 void* alloc_ordered_workqueue (char*,int) ; 
 int /*<<< orphan*/  destroy_workqueue (void*) ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 

__attribute__((used)) static int guc_init_wq(struct intel_guc *guc)
{
	struct drm_i915_private *dev_priv = guc_to_i915(guc);

	/*
	 * GuC log buffer flush work item has to do register access to
	 * send the ack to GuC and this work item, if not synced before
	 * suspend, can potentially get executed after the GFX device is
	 * suspended.
	 * By marking the WQ as freezable, we don't have to bother about
	 * flushing of this work item from the suspend hooks, the pending
	 * work item if any will be either executed before the suspend
	 * or scheduled later on resume. This way the handling of work
	 * item can be kept same between system suspend & rpm suspend.
	 */
	guc->log.relay.flush_wq =
		alloc_ordered_workqueue("i915-guc_log",
					WQ_HIGHPRI | WQ_FREEZABLE);
	if (!guc->log.relay.flush_wq) {
		DRM_ERROR("Couldn't allocate workqueue for GuC log\n");
		return -ENOMEM;
	}

	/*
	 * Even though both sending GuC action, and adding a new workitem to
	 * GuC workqueue are serialized (each with its own locking), since
	 * we're using mutliple engines, it's possible that we're going to
	 * issue a preempt request with two (or more - each for different
	 * engine) workitems in GuC queue. In this situation, GuC may submit
	 * all of them, which will make us very confused.
	 * Our preemption contexts may even already be complete - before we
	 * even had the chance to sent the preempt action to GuC!. Rather
	 * than introducing yet another lock, we can just use ordered workqueue
	 * to make sure we're always sending a single preemption request with a
	 * single workitem.
	 */
	if (HAS_LOGICAL_RING_PREEMPTION(dev_priv) &&
	    USES_GUC_SUBMISSION(dev_priv)) {
		guc->preempt_wq = alloc_ordered_workqueue("i915-guc_preempt",
							  WQ_HIGHPRI);
		if (!guc->preempt_wq) {
			destroy_workqueue(guc->log.relay.flush_wq);
			DRM_ERROR("Couldn't allocate workqueue for GuC "
				  "preemption\n");
			return -ENOMEM;
		}
	}

	return 0;
}