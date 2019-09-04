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
struct TYPE_2__ {int /*<<< orphan*/  level; int /*<<< orphan*/  pwm; } ;
struct intel_panel {TYPE_1__ backlight; } ;
struct intel_crtc_state {int dummy; } ;
struct intel_connector {struct intel_panel panel; } ;
struct drm_connector_state {int /*<<< orphan*/  connector; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_panel_actually_set_backlight (struct drm_connector_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_enable (int /*<<< orphan*/ ) ; 
 struct intel_connector* to_intel_connector (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pwm_enable_backlight(const struct intel_crtc_state *crtc_state,
				 const struct drm_connector_state *conn_state)
{
	struct intel_connector *connector = to_intel_connector(conn_state->connector);
	struct intel_panel *panel = &connector->panel;

	pwm_enable(panel->backlight.pwm);
	intel_panel_actually_set_backlight(conn_state, panel->backlight.level);
}