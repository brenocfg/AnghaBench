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
struct intel_guc {scalar_t__ handler; scalar_t__ mmio_msg; } ;
struct drm_i915_private {int /*<<< orphan*/  irq_lock; } ;
struct TYPE_2__ {struct drm_i915_private* i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 TYPE_1__* guc_to_gt (struct intel_guc*) ; 
 scalar_t__ intel_guc_to_host_event_handler_nop ; 
 int /*<<< orphan*/  intel_guc_to_host_process_recv_msg (struct intel_guc*,scalar_t__*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void guc_handle_mmio_msg(struct intel_guc *guc)
{
	struct drm_i915_private *i915 = guc_to_gt(guc)->i915;

	/* we need communication to be enabled to reply to GuC */
	GEM_BUG_ON(guc->handler == intel_guc_to_host_event_handler_nop);

	if (!guc->mmio_msg)
		return;

	spin_lock_irq(&i915->irq_lock);
	intel_guc_to_host_process_recv_msg(guc, &guc->mmio_msg, 1);
	spin_unlock_irq(&i915->irq_lock);

	guc->mmio_msg = 0;
}