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
struct intel_overlay {int active; TYPE_1__* crtc; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * overlay; } ;

/* Variables and functions */
 scalar_t__ IS_I830 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i830_overlay_clock_gating (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_overlay_release_old_vma (struct intel_overlay*) ; 

__attribute__((used)) static void intel_overlay_off_tail(struct intel_overlay *overlay)
{
	struct drm_i915_private *dev_priv = overlay->i915;

	intel_overlay_release_old_vma(overlay);

	overlay->crtc->overlay = NULL;
	overlay->crtc = NULL;
	overlay->active = false;

	if (IS_I830(dev_priv))
		i830_overlay_clock_gating(dev_priv, true);
}