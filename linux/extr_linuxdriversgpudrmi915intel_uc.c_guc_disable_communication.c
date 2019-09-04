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
struct intel_guc {int /*<<< orphan*/  handler; int /*<<< orphan*/  send; int /*<<< orphan*/  ct; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ HAS_GUC_CT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen9_disable_guc_interrupts (struct drm_i915_private*) ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_guc_ct_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_guc_send_nop ; 
 int /*<<< orphan*/  intel_guc_to_host_event_handler_nop ; 

__attribute__((used)) static void guc_disable_communication(struct intel_guc *guc)
{
	struct drm_i915_private *i915 = guc_to_i915(guc);

	if (HAS_GUC_CT(i915))
		intel_guc_ct_disable(&guc->ct);

	gen9_disable_guc_interrupts(i915);

	guc->send = intel_guc_send_nop;
	guc->handler = intel_guc_to_host_event_handler_nop;
}