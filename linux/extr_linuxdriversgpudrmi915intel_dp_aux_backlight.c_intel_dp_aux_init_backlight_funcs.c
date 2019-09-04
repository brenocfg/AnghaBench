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
struct TYPE_3__ {int /*<<< orphan*/  get; int /*<<< orphan*/  set; int /*<<< orphan*/  disable; int /*<<< orphan*/  enable; int /*<<< orphan*/  setup; } ;
struct intel_panel {TYPE_1__ backlight; } ;
struct intel_connector {struct intel_panel panel; } ;
struct TYPE_4__ {int /*<<< orphan*/  enable_dpcd_backlight; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_2__ i915_modparams ; 
 int /*<<< orphan*/  intel_dp_aux_disable_backlight ; 
 int /*<<< orphan*/  intel_dp_aux_display_control_capable (struct intel_connector*) ; 
 int /*<<< orphan*/  intel_dp_aux_enable_backlight ; 
 int /*<<< orphan*/  intel_dp_aux_get_backlight ; 
 int /*<<< orphan*/  intel_dp_aux_set_backlight ; 
 int /*<<< orphan*/  intel_dp_aux_setup_backlight ; 

int intel_dp_aux_init_backlight_funcs(struct intel_connector *intel_connector)
{
	struct intel_panel *panel = &intel_connector->panel;

	if (!i915_modparams.enable_dpcd_backlight)
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