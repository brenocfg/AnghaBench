#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct udl_device {int sku_pixel_limit; } ;
struct drm_display_mode {int vdisplay; int hdisplay; } ;
struct drm_connector {TYPE_1__* dev; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;
struct TYPE_2__ {struct udl_device* dev_private; } ;

/* Variables and functions */
 int MODE_VIRTUAL_Y ; 

__attribute__((used)) static enum drm_mode_status udl_mode_valid(struct drm_connector *connector,
			  struct drm_display_mode *mode)
{
	struct udl_device *udl = connector->dev->dev_private;
	if (!udl->sku_pixel_limit)
		return 0;

	if (mode->vdisplay * mode->hdisplay > udl->sku_pixel_limit)
		return MODE_VIRTUAL_Y;

	return 0;
}