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
struct TYPE_4__ {int /*<<< orphan*/  scan_mode; int /*<<< orphan*/  colorimetry; scalar_t__ colorspace; } ;
union hdmi_infoframe {TYPE_2__ avi; } ;
struct TYPE_3__ {scalar_t__ enc_out_format; int /*<<< orphan*/  colorimetry; } ;
struct rk3066_hdmi {TYPE_1__ hdmi_data; int /*<<< orphan*/  connector; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 scalar_t__ HDMI_COLORSPACE_RGB ; 
 scalar_t__ HDMI_COLORSPACE_YUV422 ; 
 scalar_t__ HDMI_COLORSPACE_YUV444 ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_AVI ; 
 int /*<<< orphan*/  HDMI_SCAN_MODE_NONE ; 
 int drm_hdmi_avi_infoframe_from_display_mode (TYPE_2__*,int /*<<< orphan*/ *,struct drm_display_mode*) ; 
 int rk3066_hdmi_upload_frame (struct rk3066_hdmi*,int,union hdmi_infoframe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rk3066_hdmi_config_avi(struct rk3066_hdmi *hdmi,
				  struct drm_display_mode *mode)
{
	union hdmi_infoframe frame;
	int rc;

	rc = drm_hdmi_avi_infoframe_from_display_mode(&frame.avi,
						      &hdmi->connector, mode);

	if (hdmi->hdmi_data.enc_out_format == HDMI_COLORSPACE_YUV444)
		frame.avi.colorspace = HDMI_COLORSPACE_YUV444;
	else if (hdmi->hdmi_data.enc_out_format == HDMI_COLORSPACE_YUV422)
		frame.avi.colorspace = HDMI_COLORSPACE_YUV422;
	else
		frame.avi.colorspace = HDMI_COLORSPACE_RGB;

	frame.avi.colorimetry = hdmi->hdmi_data.colorimetry;
	frame.avi.scan_mode = HDMI_SCAN_MODE_NONE;

	return rk3066_hdmi_upload_frame(hdmi, rc, &frame,
					HDMI_INFOFRAME_AVI, 0, 0, 0);
}