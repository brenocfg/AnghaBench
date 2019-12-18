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
struct sun4i_lvds {int /*<<< orphan*/  panel; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 struct sun4i_lvds* drm_connector_to_sun4i_lvds (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_panel_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sun4i_lvds_connector_destroy(struct drm_connector *connector)
{
	struct sun4i_lvds *lvds = drm_connector_to_sun4i_lvds(connector);

	drm_panel_detach(lvds->panel);
	drm_connector_cleanup(connector);
}