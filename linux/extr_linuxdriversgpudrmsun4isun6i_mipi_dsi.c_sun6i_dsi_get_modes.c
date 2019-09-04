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
struct sun6i_dsi {int /*<<< orphan*/  panel; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 struct sun6i_dsi* connector_to_sun6i_dsi (struct drm_connector*) ; 
 int drm_panel_get_modes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun6i_dsi_get_modes(struct drm_connector *connector)
{
	struct sun6i_dsi *dsi = connector_to_sun6i_dsi(connector);

	return drm_panel_get_modes(dsi->panel);
}