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
struct TYPE_9__ {int /*<<< orphan*/  get; int /*<<< orphan*/  set; int /*<<< orphan*/  disable; int /*<<< orphan*/  enable; int /*<<< orphan*/  setup; } ;
struct intel_panel {TYPE_4__ backlight; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct intel_connector {TYPE_1__ base; struct intel_panel panel; } ;
struct TYPE_7__ {scalar_t__ type; } ;
struct TYPE_8__ {TYPE_2__ backlight; } ;
struct drm_i915_private {TYPE_3__ vbt; } ;
struct TYPE_10__ {int enable_dpcd_backlight; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ INTEL_BACKLIGHT_VESA_EDP_AUX_INTERFACE ; 
 TYPE_5__ i915_modparams ; 
 int /*<<< orphan*/  intel_dp_aux_disable_backlight ; 
 int /*<<< orphan*/  intel_dp_aux_display_control_capable (struct intel_connector*) ; 
 int /*<<< orphan*/  intel_dp_aux_enable_backlight ; 
 int /*<<< orphan*/  intel_dp_aux_get_backlight ; 
 int /*<<< orphan*/  intel_dp_aux_set_backlight ; 
 int /*<<< orphan*/  intel_dp_aux_setup_backlight ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

int intel_dp_aux_init_backlight_funcs(struct intel_connector *intel_connector)
{
	struct intel_panel *panel = &intel_connector->panel;
	struct drm_i915_private *dev_priv = to_i915(intel_connector->base.dev);

	if (i915_modparams.enable_dpcd_backlight == 0 ||
	    (i915_modparams.enable_dpcd_backlight == -1 &&
	    dev_priv->vbt.backlight.type != INTEL_BACKLIGHT_VESA_EDP_AUX_INTERFACE))
		return -ENODEV;

	if (!intel_dp_aux_display_control_capable(intel_connector))
		return -ENODEV;

	panel->backlight.setup = intel_dp_aux_setup_backlight;
	panel->backlight.enable = intel_dp_aux_enable_backlight;
	panel->backlight.disable = intel_dp_aux_disable_backlight;
	panel->backlight.set = intel_dp_aux_set_backlight;
	panel->backlight.get = intel_dp_aux_get_backlight;

	return 0;
}