#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gma_encoder {scalar_t__ type; } ;
struct TYPE_4__ {struct drm_display_mode* panel_fixed_mode2; struct drm_display_mode* panel_fixed_mode; } ;
struct drm_psb_private {TYPE_2__ mode_dev; } ;
struct drm_display_mode {int flags; scalar_t__ hdisplay; scalar_t__ vdisplay; } ;
struct drm_connector {TYPE_1__* dev; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;
struct TYPE_3__ {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_DBLSCAN ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 scalar_t__ INTEL_OUTPUT_MIPI2 ; 
 int MODE_NO_DBLESCAN ; 
 int MODE_NO_INTERLACE ; 
 int MODE_OK ; 
 int MODE_PANEL ; 
 struct gma_encoder* gma_attached_encoder (struct drm_connector*) ; 

enum drm_mode_status psb_intel_lvds_mode_valid(struct drm_connector *connector,
				 struct drm_display_mode *mode)
{
	struct drm_psb_private *dev_priv = connector->dev->dev_private;
	struct gma_encoder *gma_encoder = gma_attached_encoder(connector);
	struct drm_display_mode *fixed_mode =
					dev_priv->mode_dev.panel_fixed_mode;

	if (gma_encoder->type == INTEL_OUTPUT_MIPI2)
		fixed_mode = dev_priv->mode_dev.panel_fixed_mode2;

	/* just in case */
	if (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		return MODE_NO_DBLESCAN;

	/* just in case */
	if (mode->flags & DRM_MODE_FLAG_INTERLACE)
		return MODE_NO_INTERLACE;

	if (fixed_mode) {
		if (mode->hdisplay > fixed_mode->hdisplay)
			return MODE_PANEL;
		if (mode->vdisplay > fixed_mode->vdisplay)
			return MODE_PANEL;
	}
	return MODE_OK;
}