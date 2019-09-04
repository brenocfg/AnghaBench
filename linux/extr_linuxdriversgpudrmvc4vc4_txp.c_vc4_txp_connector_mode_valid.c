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
struct drm_mode_config {int min_width; int max_width; int min_height; int max_height; } ;
struct drm_display_mode {int hdisplay; int vdisplay; } ;
struct drm_device {struct drm_mode_config mode_config; } ;
struct drm_connector {struct drm_device* dev; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int MODE_BAD_HVALUE ; 
 int MODE_BAD_VVALUE ; 
 int MODE_OK ; 

__attribute__((used)) static enum drm_mode_status
vc4_txp_connector_mode_valid(struct drm_connector *connector,
			     struct drm_display_mode *mode)
{
	struct drm_device *dev = connector->dev;
	struct drm_mode_config *mode_config = &dev->mode_config;
	int w = mode->hdisplay, h = mode->vdisplay;

	if (w < mode_config->min_width || w > mode_config->max_width)
		return MODE_BAD_HVALUE;

	if (h < mode_config->min_height || h > mode_config->max_height)
		return MODE_BAD_VVALUE;

	return MODE_OK;
}