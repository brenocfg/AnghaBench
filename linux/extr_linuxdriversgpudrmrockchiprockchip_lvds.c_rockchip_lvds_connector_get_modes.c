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
struct rockchip_lvds {struct drm_panel* panel; } ;
struct drm_panel {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 struct rockchip_lvds* connector_to_lvds (struct drm_connector*) ; 
 int drm_panel_get_modes (struct drm_panel*) ; 

__attribute__((used)) static int rockchip_lvds_connector_get_modes(struct drm_connector *connector)
{
	struct rockchip_lvds *lvds = connector_to_lvds(connector);
	struct drm_panel *panel = lvds->panel;

	return drm_panel_get_modes(panel);
}