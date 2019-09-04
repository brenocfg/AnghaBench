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
typedef  int /*<<< orphan*/  videomode ;
struct xen_drm_front_drm_pipeline {int width; int height; } ;
struct videomode {int hactive; int vactive; int hfront_porch; int hback_porch; int hsync_len; int vfront_porch; int vback_porch; int vsync_len; int pixelclock; } ;
struct drm_display_mode {int type; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DRM_MODE_TYPE_DRIVER ; 
 int DRM_MODE_TYPE_PREFERRED ; 
 int XEN_DRM_CRTC_VREFRESH_HZ ; 
 int /*<<< orphan*/  drm_display_mode_from_videomode (struct videomode*,struct drm_display_mode*) ; 
 struct drm_display_mode* drm_mode_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  memset (struct videomode*,int /*<<< orphan*/ ,int) ; 
 struct xen_drm_front_drm_pipeline* to_xen_drm_pipeline (struct drm_connector*) ; 

__attribute__((used)) static int connector_get_modes(struct drm_connector *connector)
{
	struct xen_drm_front_drm_pipeline *pipeline =
			to_xen_drm_pipeline(connector);
	struct drm_display_mode *mode;
	struct videomode videomode;
	int width, height;

	mode = drm_mode_create(connector->dev);
	if (!mode)
		return 0;

	memset(&videomode, 0, sizeof(videomode));
	videomode.hactive = pipeline->width;
	videomode.vactive = pipeline->height;
	width = videomode.hactive + videomode.hfront_porch +
			videomode.hback_porch + videomode.hsync_len;
	height = videomode.vactive + videomode.vfront_porch +
			videomode.vback_porch + videomode.vsync_len;
	videomode.pixelclock = width * height * XEN_DRM_CRTC_VREFRESH_HZ;
	mode->type = DRM_MODE_TYPE_PREFERRED | DRM_MODE_TYPE_DRIVER;

	drm_display_mode_from_videomode(&videomode, mode);
	drm_mode_probed_add(connector, mode);
	return 1;
}