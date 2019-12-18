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
struct intel_guc {int /*<<< orphan*/  (* handler ) (struct intel_guc*) ;int /*<<< orphan*/  send; int /*<<< orphan*/  ct; } ;
struct drm_i915_private {int /*<<< orphan*/  irq_lock; } ;
struct TYPE_2__ {struct drm_i915_private* i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  guc_communication_enabled (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_enable_interrupts (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_get_mmio_msg (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_handle_mmio_msg (struct intel_guc*) ; 
 TYPE_1__* guc_to_gt (struct intel_guc*) ; 
 int i915_inject_load_error (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int intel_guc_ct_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_guc_send_ct ; 
 int /*<<< orphan*/  intel_guc_to_host_event_handler_ct (struct intel_guc*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int guc_enable_communication(struct intel_guc *guc)
{
	struct drm_i915_private *i915 = guc_to_gt(guc)->i915;
	int ret;

	GEM_BUG_ON(guc_communication_enabled(guc));

	ret = i915_inject_load_error(i915, -ENXIO);
	if (ret)
		return ret;

	ret = intel_guc_ct_enable(&guc->ct);
	if (ret)
		return ret;

	guc->send = intel_guc_send_ct;
	guc->handler = intel_guc_to_host_event_handler_ct;

	/* check for mmio messages received before/during the CT enable */
	guc_get_mmio_msg(guc);
	guc_handle_mmio_msg(guc);

	guc_enable_interrupts(guc);

	/* check for CT messages received before we enabled interrupts */
	spin_lock_irq(&i915->irq_lock);
	intel_guc_to_host_event_handler_ct(guc);
	spin_unlock_irq(&i915->irq_lock);

	DRM_INFO("GuC communication enabled\n");

	return 0;
}