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
struct intel_guc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  awake; } ;
struct drm_i915_private {TYPE_1__ gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  guc_clients_doorbell_fini (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_interrupts_release (struct drm_i915_private*) ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 

void intel_guc_submission_disable(struct intel_guc *guc)
{
	struct drm_i915_private *dev_priv = guc_to_i915(guc);

	GEM_BUG_ON(dev_priv->gt.awake); /* GT should be parked first */

	guc_interrupts_release(dev_priv);
	guc_clients_doorbell_fini(guc);
}