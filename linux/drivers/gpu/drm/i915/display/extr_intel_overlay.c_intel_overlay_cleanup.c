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
struct intel_overlay {int /*<<< orphan*/  last_flip; int /*<<< orphan*/  reg_bo; int /*<<< orphan*/  active; } ;
struct drm_i915_private {int /*<<< orphan*/  overlay; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct intel_overlay* fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_active_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct intel_overlay*) ; 

void intel_overlay_cleanup(struct drm_i915_private *dev_priv)
{
	struct intel_overlay *overlay;

	overlay = fetch_and_zero(&dev_priv->overlay);
	if (!overlay)
		return;

	/*
	 * The bo's should be free'd by the generic code already.
	 * Furthermore modesetting teardown happens beforehand so the
	 * hardware should be off already.
	 */
	WARN_ON(overlay->active);

	i915_gem_object_put(overlay->reg_bo);
	i915_active_fini(&overlay->last_flip);

	kfree(overlay);
}