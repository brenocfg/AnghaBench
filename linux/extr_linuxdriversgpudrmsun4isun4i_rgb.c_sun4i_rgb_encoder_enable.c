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
struct sun4i_tcon {int /*<<< orphan*/  panel; } ;
struct sun4i_rgb {struct sun4i_tcon* tcon; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 struct sun4i_rgb* drm_encoder_to_sun4i_rgb (struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_panel_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_prepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun4i_rgb_encoder_enable(struct drm_encoder *encoder)
{
	struct sun4i_rgb *rgb = drm_encoder_to_sun4i_rgb(encoder);
	struct sun4i_tcon *tcon = rgb->tcon;

	DRM_DEBUG_DRIVER("Enabling RGB output\n");

	if (!IS_ERR(tcon->panel)) {
		drm_panel_prepare(tcon->panel);
		drm_panel_enable(tcon->panel);
	}
}