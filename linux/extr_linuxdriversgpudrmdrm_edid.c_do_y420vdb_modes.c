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
typedef  int u8 ;
struct drm_hdmi_info {int /*<<< orphan*/  y420_vdb_modes; } ;
struct drm_display_mode {int dummy; } ;
struct drm_display_info {int /*<<< orphan*/  color_formats; struct drm_hdmi_info hdmi; } ;
struct drm_device {int dummy; } ;
struct drm_connector {struct drm_display_info display_info; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_COLOR_FORMAT_YCRCB420 ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int,int) ; 
 struct drm_display_mode* drm_mode_duplicate (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_valid_cea_vic (int) ; 
 int /*<<< orphan*/ * edid_cea_modes ; 
 int svd_to_vic (int const) ; 

__attribute__((used)) static int do_y420vdb_modes(struct drm_connector *connector,
			    const u8 *svds, u8 svds_len)
{
	int modes = 0, i;
	struct drm_device *dev = connector->dev;
	struct drm_display_info *info = &connector->display_info;
	struct drm_hdmi_info *hdmi = &info->hdmi;

	for (i = 0; i < svds_len; i++) {
		u8 vic = svd_to_vic(svds[i]);
		struct drm_display_mode *newmode;

		if (!drm_valid_cea_vic(vic))
			continue;

		newmode = drm_mode_duplicate(dev, &edid_cea_modes[vic]);
		if (!newmode)
			break;
		bitmap_set(hdmi->y420_vdb_modes, vic, 1);
		drm_mode_probed_add(connector, newmode);
		modes++;
	}

	if (modes > 0)
		info->color_formats |= DRM_COLOR_FORMAT_YCRCB420;
	return modes;
}