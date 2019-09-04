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
struct TYPE_7__ {int /*<<< orphan*/  get; int /*<<< orphan*/  set; int /*<<< orphan*/  disable; int /*<<< orphan*/  enable; int /*<<< orphan*/  setup; } ;
struct intel_panel {TYPE_3__ backlight; } ;
struct intel_encoder {scalar_t__ type; } ;
struct TYPE_8__ {struct drm_device* dev; } ;
struct intel_connector {struct intel_panel panel; struct intel_encoder* encoder; TYPE_4__ base; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct TYPE_6__ {TYPE_1__ backlight; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ INTEL_BACKLIGHT_DSI_DCS ; 
 scalar_t__ INTEL_OUTPUT_DSI ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dcs_disable_backlight ; 
 int /*<<< orphan*/  dcs_enable_backlight ; 
 int /*<<< orphan*/  dcs_get_backlight ; 
 int /*<<< orphan*/  dcs_set_backlight ; 
 int /*<<< orphan*/  dcs_setup_backlight ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

int intel_dsi_dcs_init_backlight_funcs(struct intel_connector *intel_connector)
{
	struct drm_device *dev = intel_connector->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_encoder *encoder = intel_connector->encoder;
	struct intel_panel *panel = &intel_connector->panel;

	if (dev_priv->vbt.backlight.type != INTEL_BACKLIGHT_DSI_DCS)
		return -ENODEV;

	if (WARN_ON(encoder->type != INTEL_OUTPUT_DSI))
		return -EINVAL;

	panel->backlight.setup = dcs_setup_backlight;
	panel->backlight.enable = dcs_enable_backlight;
	panel->backlight.disable = dcs_disable_backlight;
	panel->backlight.set = dcs_set_backlight;
	panel->backlight.get = dcs_get_backlight;

	return 0;
}