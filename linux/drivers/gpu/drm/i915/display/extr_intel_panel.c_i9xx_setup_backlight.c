#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int combination_mode; int active_low_pwm; int max; int enabled; int /*<<< orphan*/  min; int /*<<< orphan*/  level; } ;
struct intel_panel {TYPE_2__ backlight; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_connector {struct intel_panel panel; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  BLC_PWM_CTL ; 
 int BLM_LEGACY_MODE ; 
 int BLM_POLARITY_PNV ; 
 int ENODEV ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_I915GM (struct drm_i915_private*) ; 
 scalar_t__ IS_I945GM (struct drm_i915_private*) ; 
 scalar_t__ IS_PINEVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  clamp (int,int /*<<< orphan*/ ,int) ; 
 int get_backlight_max_vbt (struct intel_connector*) ; 
 int /*<<< orphan*/  get_backlight_min_vbt (struct intel_connector*) ; 
 int i9xx_get_backlight (struct intel_connector*) ; 
 int intel_panel_compute_brightness (struct intel_connector*,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i9xx_setup_backlight(struct intel_connector *connector, enum pipe unused)
{
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);
	struct intel_panel *panel = &connector->panel;
	u32 ctl, val;

	ctl = I915_READ(BLC_PWM_CTL);

	if (IS_GEN(dev_priv, 2) || IS_I915GM(dev_priv) || IS_I945GM(dev_priv))
		panel->backlight.combination_mode = ctl & BLM_LEGACY_MODE;

	if (IS_PINEVIEW(dev_priv))
		panel->backlight.active_low_pwm = ctl & BLM_POLARITY_PNV;

	panel->backlight.max = ctl >> 17;

	if (!panel->backlight.max) {
		panel->backlight.max = get_backlight_max_vbt(connector);
		panel->backlight.max >>= 1;
	}

	if (!panel->backlight.max)
		return -ENODEV;

	if (panel->backlight.combination_mode)
		panel->backlight.max *= 0xff;

	panel->backlight.min = get_backlight_min_vbt(connector);

	val = i9xx_get_backlight(connector);
	val = intel_panel_compute_brightness(connector, val);
	panel->backlight.level = clamp(val, panel->backlight.min,
				       panel->backlight.max);

	panel->backlight.enabled = val != 0;

	return 0;
}