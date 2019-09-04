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
struct drm_display_mode {int /*<<< orphan*/  type; } ;
struct drm_device {int dummy; } ;
struct drm_connector {struct drm_device* dev; } ;
struct TYPE_3__ {unsigned int w; unsigned int h; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DRM_MODE_TYPE_PREFERRED ; 
 TYPE_1__* common_modes ; 
 struct drm_display_mode* drm_cvt_mode (struct drm_device*,unsigned int,unsigned int,int,int,int,int) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 

__attribute__((used)) static int qxl_add_common_modes(struct drm_connector *connector,
                                unsigned pwidth,
                                unsigned pheight)
{
	struct drm_device *dev = connector->dev;
	struct drm_display_mode *mode = NULL;
	int i;
	for (i = 0; i < ARRAY_SIZE(common_modes); i++) {
		mode = drm_cvt_mode(dev, common_modes[i].w, common_modes[i].h,
				    60, false, false, false);
		if (common_modes[i].w == pwidth && common_modes[i].h == pheight)
			mode->type |= DRM_MODE_TYPE_PREFERRED;
		drm_mode_probed_add(connector, mode);
	}
	return i - 1;
}