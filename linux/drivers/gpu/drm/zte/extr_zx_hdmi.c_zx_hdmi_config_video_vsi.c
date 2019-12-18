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
struct TYPE_2__ {int /*<<< orphan*/  hdmi; } ;
union hdmi_infoframe {TYPE_1__ vendor; } ;
struct zx_hdmi {int /*<<< orphan*/  dev; int /*<<< orphan*/  connector; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  FSEL_VSIF ; 
 int drm_hdmi_vendor_infoframe_from_display_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct drm_display_mode*) ; 
 int zx_hdmi_infoframe_trans (struct zx_hdmi*,union hdmi_infoframe*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zx_hdmi_config_video_vsi(struct zx_hdmi *hdmi,
				    struct drm_display_mode *mode)
{
	union hdmi_infoframe frame;
	int ret;

	ret = drm_hdmi_vendor_infoframe_from_display_mode(&frame.vendor.hdmi,
							  &hdmi->connector,
							  mode);
	if (ret) {
		DRM_DEV_ERROR(hdmi->dev, "failed to get vendor infoframe: %d\n",
			      ret);
		return ret;
	}

	return zx_hdmi_infoframe_trans(hdmi, &frame, FSEL_VSIF);
}