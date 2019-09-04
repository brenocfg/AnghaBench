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
typedef  scalar_t__ u32 ;
struct TYPE_5__ {scalar_t__ max; scalar_t__ min; } ;
struct intel_panel {TYPE_2__ backlight; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_connector {struct intel_panel panel; TYPE_1__ base; } ;
struct drm_i915_private {int quirks; } ;
struct TYPE_6__ {scalar_t__ invert_brightness; } ;

/* Variables and functions */
 int QUIRK_INVERT_BRIGHTNESS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_3__ i915_modparams ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 intel_panel_compute_brightness(struct intel_connector *connector,
					  u32 val)
{
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);
	struct intel_panel *panel = &connector->panel;

	WARN_ON(panel->backlight.max == 0);

	if (i915_modparams.invert_brightness < 0)
		return val;

	if (i915_modparams.invert_brightness > 0 ||
	    dev_priv->quirks & QUIRK_INVERT_BRIGHTNESS) {
		return panel->backlight.max - val + panel->backlight.min;
	}

	return val;
}