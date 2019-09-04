#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qxl_device {scalar_t__ monitors_config_width; scalar_t__ monitors_config_height; } ;
struct drm_display_mode {scalar_t__ hdisplay; scalar_t__ vdisplay; } ;
struct drm_device {struct qxl_device* dev_private; } ;
struct drm_connector {struct drm_device* dev; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;
struct TYPE_3__ {scalar_t__ w; scalar_t__ h; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int MODE_BAD ; 
 int MODE_OK ; 
 TYPE_1__* common_modes ; 

__attribute__((used)) static enum drm_mode_status qxl_conn_mode_valid(struct drm_connector *connector,
			       struct drm_display_mode *mode)
{
	struct drm_device *ddev = connector->dev;
	struct qxl_device *qdev = ddev->dev_private;
	int i;

	/* TODO: is this called for user defined modes? (xrandr --add-mode)
	 * TODO: check that the mode fits in the framebuffer */

	if(qdev->monitors_config_width == mode->hdisplay &&
	   qdev->monitors_config_height == mode->vdisplay)
		return MODE_OK;

	for (i = 0; i < ARRAY_SIZE(common_modes); i++) {
		if (common_modes[i].w == mode->hdisplay && common_modes[i].h == mode->vdisplay)
			return MODE_OK;
	}
	return MODE_BAD;
}