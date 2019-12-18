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
struct sun4i_lvds {scalar_t__ panel; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 struct sun4i_lvds* drm_encoder_to_sun4i_lvds (struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_panel_disable (scalar_t__) ; 
 int /*<<< orphan*/  drm_panel_unprepare (scalar_t__) ; 

__attribute__((used)) static void sun4i_lvds_encoder_disable(struct drm_encoder *encoder)
{
	struct sun4i_lvds *lvds = drm_encoder_to_sun4i_lvds(encoder);

	DRM_DEBUG_DRIVER("Disabling LVDS output\n");

	if (lvds->panel) {
		drm_panel_disable(lvds->panel);
		drm_panel_unprepare(lvds->panel);
	}
}