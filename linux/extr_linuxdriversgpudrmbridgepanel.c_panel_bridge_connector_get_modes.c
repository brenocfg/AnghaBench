#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct panel_bridge {int /*<<< orphan*/  panel; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 struct panel_bridge* drm_connector_to_panel_bridge (struct drm_connector*) ; 
 int drm_panel_get_modes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int panel_bridge_connector_get_modes(struct drm_connector *connector)
{
	struct panel_bridge *panel_bridge =
		drm_connector_to_panel_bridge(connector);

	return drm_panel_get_modes(panel_bridge->panel);
}