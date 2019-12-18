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
struct TYPE_2__ {int /*<<< orphan*/  colorspace; } ;
union hdmi_infoframe {TYPE_1__ avi; } ;
struct zx_hdmi {int /*<<< orphan*/  dev; int /*<<< orphan*/  connector; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  FSEL_AVI ; 
 int /*<<< orphan*/  HDMI_COLORSPACE_YUV444 ; 
 int drm_hdmi_avi_infoframe_from_display_mode (TYPE_1__*,int /*<<< orphan*/ *,struct drm_display_mode*) ; 
 int zx_hdmi_infoframe_trans (struct zx_hdmi*,union hdmi_infoframe*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zx_hdmi_config_video_avi(struct zx_hdmi *hdmi,
				    struct drm_display_mode *mode)
{
	union hdmi_infoframe frame;
	int ret;

	ret = drm_hdmi_avi_infoframe_from_display_mode(&frame.avi,
						       &hdmi->connector,
						       mode);
	if (ret) {
		DRM_DEV_ERROR(hdmi->dev, "failed to get avi infoframe: %d\n",
			      ret);
		return ret;
	}

	/* We always use YUV444 for HDMI output. */
	frame.avi.colorspace = HDMI_COLORSPACE_YUV444;

	return zx_hdmi_infoframe_trans(hdmi, &frame, FSEL_AVI);
}