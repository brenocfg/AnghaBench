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
struct intel_guc {int msg_enabled_mask; int /*<<< orphan*/  irq_lock; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SOFT_SCRATCH (int) ; 
 int /*<<< orphan*/  disable_rpm_wakeref_asserts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  enable_rpm_wakeref_asserts (struct drm_i915_private*) ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_guc_to_host_process_recv_msg (struct intel_guc*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void intel_guc_to_host_event_handler_mmio(struct intel_guc *guc)
{
	struct drm_i915_private *dev_priv = guc_to_i915(guc);
	u32 msg, val;

	/*
	 * Sample the log buffer flush related bits & clear them out now
	 * itself from the message identity register to minimize the
	 * probability of losing a flush interrupt, when there are back
	 * to back flush interrupts.
	 * There can be a new flush interrupt, for different log buffer
	 * type (like for ISR), whilst Host is handling one (for DPC).
	 * Since same bit is used in message register for ISR & DPC, it
	 * could happen that GuC sets the bit for 2nd interrupt but Host
	 * clears out the bit on handling the 1st interrupt.
	 */
	disable_rpm_wakeref_asserts(dev_priv);
	spin_lock(&guc->irq_lock);
	val = I915_READ(SOFT_SCRATCH(15));
	msg = val & guc->msg_enabled_mask;
	I915_WRITE(SOFT_SCRATCH(15), val & ~msg);
	spin_unlock(&guc->irq_lock);
	enable_rpm_wakeref_asserts(dev_priv);

	intel_guc_to_host_process_recv_msg(guc, msg);
}