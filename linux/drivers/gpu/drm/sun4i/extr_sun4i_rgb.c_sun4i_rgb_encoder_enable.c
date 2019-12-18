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
struct sun4i_rgb {scalar_t__ panel; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 struct sun4i_rgb* drm_encoder_to_sun4i_rgb (struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_panel_enable (scalar_t__) ; 
 int /*<<< orphan*/  drm_panel_prepare (scalar_t__) ; 

__attribute__((used)) static void sun4i_rgb_encoder_enable(struct drm_encoder *encoder)
{
	struct sun4i_rgb *rgb = drm_encoder_to_sun4i_rgb(encoder);

	DRM_DEBUG_DRIVER("Enabling RGB output\n");

	if (rgb->panel) {
		drm_panel_prepare(rgb->panel);
		drm_panel_enable(rgb->panel);
	}
}