#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int enabled; int /*<<< orphan*/  (* disable ) (struct drm_connector_state const*) ;TYPE_4__* device; int /*<<< orphan*/  present; } ;
struct intel_panel {TYPE_5__ backlight; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct intel_connector {struct intel_panel panel; TYPE_1__ base; } ;
struct TYPE_7__ {scalar_t__ switch_power_state; } ;
struct drm_i915_private {int /*<<< orphan*/  backlight_lock; TYPE_2__ drm; } ;
struct drm_connector_state {int /*<<< orphan*/  connector; } ;
struct TYPE_8__ {int /*<<< orphan*/  power; } ;
struct TYPE_9__ {TYPE_3__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 scalar_t__ DRM_SWITCH_POWER_CHANGING ; 
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_connector_state const*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_connector* to_intel_connector (int /*<<< orphan*/ ) ; 

void intel_panel_disable_backlight(const struct drm_connector_state *old_conn_state)
{
	struct intel_connector *connector = to_intel_connector(old_conn_state->connector);
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);
	struct intel_panel *panel = &connector->panel;

	if (!panel->backlight.present)
		return;

	/*
	 * Do not disable backlight on the vga_switcheroo path. When switching
	 * away from i915, the other client may depend on i915 to handle the
	 * backlight. This will leave the backlight on unnecessarily when
	 * another client is not activated.
	 */
	if (dev_priv->drm.switch_power_state == DRM_SWITCH_POWER_CHANGING) {
		DRM_DEBUG_DRIVER("Skipping backlight disable on vga switch\n");
		return;
	}

	mutex_lock(&dev_priv->backlight_lock);

	if (panel->backlight.device)
		panel->backlight.device->props.power = FB_BLANK_POWERDOWN;
	panel->backlight.enabled = false;
	panel->backlight.disable(old_conn_state);

	mutex_unlock(&dev_priv->backlight_lock);
}