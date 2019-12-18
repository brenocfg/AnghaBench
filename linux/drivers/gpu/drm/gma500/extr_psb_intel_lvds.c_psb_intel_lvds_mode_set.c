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
typedef  int u32 ;
struct drm_psb_private {scalar_t__ lvds_dither; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_display_mode {scalar_t__ hdisplay; scalar_t__ vdisplay; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int HORIZ_AUTO_SCALE ; 
 int HORIZ_INTERP_BILINEAR ; 
 int PANEL_8TO6_DITHER_ENABLE ; 
 int /*<<< orphan*/  PFIT_CONTROL ; 
 int PFIT_ENABLE ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int VERT_AUTO_SCALE ; 
 int VERT_INTERP_BILINEAR ; 

__attribute__((used)) static void psb_intel_lvds_mode_set(struct drm_encoder *encoder,
				struct drm_display_mode *mode,
				struct drm_display_mode *adjusted_mode)
{
	struct drm_device *dev = encoder->dev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	u32 pfit_control;

	/*
	 * The LVDS pin pair will already have been turned on in the
	 * psb_intel_crtc_mode_set since it has a large impact on the DPLL
	 * settings.
	 */

	/*
	 * Enable automatic panel scaling so that non-native modes fill the
	 * screen.  Should be enabled before the pipe is enabled, according to
	 * register description and PRM.
	 */
	if (mode->hdisplay != adjusted_mode->hdisplay ||
	    mode->vdisplay != adjusted_mode->vdisplay)
		pfit_control = (PFIT_ENABLE | VERT_AUTO_SCALE |
				HORIZ_AUTO_SCALE | VERT_INTERP_BILINEAR |
				HORIZ_INTERP_BILINEAR);
	else
		pfit_control = 0;

	if (dev_priv->lvds_dither)
		pfit_control |= PANEL_8TO6_DITHER_ENABLE;

	REG_WRITE(PFIT_CONTROL, pfit_control);
}