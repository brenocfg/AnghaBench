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
struct intel_overlay {int active; int /*<<< orphan*/ * crtc; scalar_t__ old_yscale; scalar_t__ old_xscale; } ;
struct drm_i915_private {struct intel_overlay* overlay; } ;

/* Variables and functions */

void intel_overlay_reset(struct drm_i915_private *dev_priv)
{
	struct intel_overlay *overlay = dev_priv->overlay;

	if (!overlay)
		return;

	overlay->old_xscale = 0;
	overlay->old_yscale = 0;
	overlay->crtc = NULL;
	overlay->active = false;
}