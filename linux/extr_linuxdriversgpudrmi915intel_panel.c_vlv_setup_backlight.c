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
struct TYPE_4__ {int active_low_pwm; int max; int enabled; int /*<<< orphan*/  min; int /*<<< orphan*/  level; } ;
struct intel_panel {TYPE_2__ backlight; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_connector {struct intel_panel panel; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int BLM_POLARITY_I965 ; 
 int BLM_PWM_ENABLE ; 
 int ENODEV ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int PIPE_A ; 
 int PIPE_B ; 
 int /*<<< orphan*/  VLV_BLC_PWM_CTL (int) ; 
 int /*<<< orphan*/  VLV_BLC_PWM_CTL2 (int) ; 
 scalar_t__ WARN_ON (int) ; 
 int _vlv_get_backlight (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  clamp (int,int /*<<< orphan*/ ,int) ; 
 int get_backlight_max_vbt (struct intel_connector*) ; 
 int /*<<< orphan*/  get_backlight_min_vbt (struct intel_connector*) ; 
 int intel_panel_compute_brightness (struct intel_connector*,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlv_setup_backlight(struct intel_connector *connector, enum pipe pipe)
{
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);
	struct intel_panel *panel = &connector->panel;
	u32 ctl, ctl2, val;

	if (WARN_ON(pipe != PIPE_A && pipe != PIPE_B))
		return -ENODEV;

	ctl2 = I915_READ(VLV_BLC_PWM_CTL2(pipe));
	panel->backlight.active_low_pwm = ctl2 & BLM_POLARITY_I965;

	ctl = I915_READ(VLV_BLC_PWM_CTL(pipe));
	panel->backlight.max = ctl >> 16;

	if (!panel->backlight.max)
		panel->backlight.max = get_backlight_max_vbt(connector);

	if (!panel->backlight.max)
		return -ENODEV;

	panel->backlight.min = get_backlight_min_vbt(connector);

	val = _vlv_get_backlight(dev_priv, pipe);
	val = intel_panel_compute_brightness(connector, val);
	panel->backlight.level = clamp(val, panel->backlight.min,
				       panel->backlight.max);

	panel->backlight.enabled = ctl2 & BLM_PWM_ENABLE;

	return 0;
}