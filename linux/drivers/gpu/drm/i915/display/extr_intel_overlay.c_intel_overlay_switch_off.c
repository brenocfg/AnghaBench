#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_overlay {TYPE_1__* regs; int /*<<< orphan*/  active; struct drm_i915_private* i915; } ;
struct TYPE_5__ {int /*<<< orphan*/  connection_mutex; } ;
struct TYPE_6__ {TYPE_2__ mode_config; int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_3__ drm; } ;
struct TYPE_4__ {int /*<<< orphan*/  OCMD; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drm_modeset_is_locked (int /*<<< orphan*/ *) ; 
 int intel_overlay_off (struct intel_overlay*) ; 
 int intel_overlay_recover_from_interrupt (struct intel_overlay*) ; 
 int intel_overlay_release_old_vid (struct intel_overlay*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int intel_overlay_switch_off(struct intel_overlay *overlay)
{
	struct drm_i915_private *dev_priv = overlay->i915;
	int ret;

	lockdep_assert_held(&dev_priv->drm.struct_mutex);
	WARN_ON(!drm_modeset_is_locked(&dev_priv->drm.mode_config.connection_mutex));

	ret = intel_overlay_recover_from_interrupt(overlay);
	if (ret != 0)
		return ret;

	if (!overlay->active)
		return 0;

	ret = intel_overlay_release_old_vid(overlay);
	if (ret != 0)
		return ret;

	iowrite32(0, &overlay->regs->OCMD);

	return intel_overlay_off(overlay);
}