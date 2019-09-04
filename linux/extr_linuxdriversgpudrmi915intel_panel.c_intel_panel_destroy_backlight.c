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
struct TYPE_2__ {int present; scalar_t__ pwm; } ;
struct intel_panel {TYPE_1__ backlight; } ;
struct intel_connector {struct intel_panel panel; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pwm_put (scalar_t__) ; 
 struct intel_connector* to_intel_connector (struct drm_connector*) ; 

void intel_panel_destroy_backlight(struct drm_connector *connector)
{
	struct intel_connector *intel_connector = to_intel_connector(connector);
	struct intel_panel *panel = &intel_connector->panel;

	/* dispose of the pwm */
	if (panel->backlight.pwm)
		pwm_put(panel->backlight.pwm);

	panel->backlight.present = false;
}