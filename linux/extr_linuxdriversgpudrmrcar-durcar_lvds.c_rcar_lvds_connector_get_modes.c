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
struct rcar_lvds {int /*<<< orphan*/  panel; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 struct rcar_lvds* connector_to_rcar_lvds (struct drm_connector*) ; 
 int drm_panel_get_modes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcar_lvds_connector_get_modes(struct drm_connector *connector)
{
	struct rcar_lvds *lvds = connector_to_rcar_lvds(connector);

	return drm_panel_get_modes(lvds->panel);
}