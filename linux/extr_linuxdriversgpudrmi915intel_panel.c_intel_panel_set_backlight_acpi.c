#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {scalar_t__ max; scalar_t__ enabled; TYPE_3__* device; int /*<<< orphan*/  level; int /*<<< orphan*/  present; } ;
struct intel_panel {TYPE_4__ backlight; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct intel_connector {struct intel_panel panel; TYPE_1__ base; } ;
struct drm_i915_private {int /*<<< orphan*/  backlight_lock; } ;
struct drm_connector_state {int /*<<< orphan*/  crtc; int /*<<< orphan*/  connector; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  brightness; } ;
struct TYPE_7__ {TYPE_2__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clamp_user_to_hw (struct intel_connector*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_panel_actually_set_backlight (struct drm_connector_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scale_hw_to_user (struct intel_connector*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_connector* to_intel_connector (int /*<<< orphan*/ ) ; 

void intel_panel_set_backlight_acpi(const struct drm_connector_state *conn_state,
				    u32 user_level, u32 user_max)
{
	struct intel_connector *connector = to_intel_connector(conn_state->connector);
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);
	struct intel_panel *panel = &connector->panel;
	u32 hw_level;

	/*
	 * Lack of crtc may occur during driver init because
	 * connection_mutex isn't held across the entire backlight
	 * setup + modeset readout, and the BIOS can issue the
	 * requests at any time.
	 */
	if (!panel->backlight.present || !conn_state->crtc)
		return;

	mutex_lock(&dev_priv->backlight_lock);

	WARN_ON(panel->backlight.max == 0);

	hw_level = clamp_user_to_hw(connector, user_level, user_max);
	panel->backlight.level = hw_level;

	if (panel->backlight.device)
		panel->backlight.device->props.brightness =
			scale_hw_to_user(connector,
					 panel->backlight.level,
					 panel->backlight.device->props.max_brightness);

	if (panel->backlight.enabled)
		intel_panel_actually_set_backlight(conn_state, hw_level);

	mutex_unlock(&dev_priv->backlight_lock);
}