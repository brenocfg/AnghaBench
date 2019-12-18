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
struct TYPE_2__ {void* level; void* max; } ;
struct intel_panel {TYPE_1__ backlight; } ;
struct intel_connector {struct intel_panel panel; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 void* PANEL_PWM_MAX_VALUE ; 

__attribute__((used)) static int dcs_setup_backlight(struct intel_connector *connector,
			       enum pipe unused)
{
	struct intel_panel *panel = &connector->panel;

	panel->backlight.max = PANEL_PWM_MAX_VALUE;
	panel->backlight.level = PANEL_PWM_MAX_VALUE;

	return 0;
}