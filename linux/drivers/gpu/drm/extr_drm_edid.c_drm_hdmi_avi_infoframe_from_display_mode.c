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
typedef  int /*<<< orphan*/  u8 ;
struct hdmi_avi_infoframe {int pixel_repeat; int video_code; int picture_aspect; int /*<<< orphan*/  scan_mode; int /*<<< orphan*/  active_aspect; scalar_t__ itc; int /*<<< orphan*/  content_type; } ;
struct drm_display_mode {int flags; int picture_aspect_ratio; } ;
struct drm_connector {int dummy; } ;
typedef  enum hdmi_picture_aspect { ____Placeholder_hdmi_picture_aspect } hdmi_picture_aspect ;

/* Variables and functions */
 int DRM_MODE_FLAG_3D_MASK ; 
 int DRM_MODE_FLAG_DBLCLK ; 
 int EINVAL ; 
 int /*<<< orphan*/  HDMI_ACTIVE_ASPECT_PICTURE ; 
 int /*<<< orphan*/  HDMI_CONTENT_TYPE_GRAPHICS ; 
 int HDMI_PICTURE_ASPECT_16_9 ; 
 int HDMI_PICTURE_ASPECT_NONE ; 
 int /*<<< orphan*/  HDMI_SCAN_MODE_UNDERSCAN ; 
 int drm_get_cea_aspect_ratio (int) ; 
 int drm_match_cea_mode (struct drm_display_mode const*) ; 
 int /*<<< orphan*/  drm_match_hdmi_mode (struct drm_display_mode const*) ; 
 scalar_t__ drm_valid_hdmi_vic (int /*<<< orphan*/ ) ; 
 int hdmi_avi_infoframe_init (struct hdmi_avi_infoframe*) ; 
 int /*<<< orphan*/  is_hdmi2_sink (struct drm_connector*) ; 

int
drm_hdmi_avi_infoframe_from_display_mode(struct hdmi_avi_infoframe *frame,
					 struct drm_connector *connector,
					 const struct drm_display_mode *mode)
{
	enum hdmi_picture_aspect picture_aspect;
	int err;

	if (!frame || !mode)
		return -EINVAL;

	err = hdmi_avi_infoframe_init(frame);
	if (err < 0)
		return err;

	if (mode->flags & DRM_MODE_FLAG_DBLCLK)
		frame->pixel_repeat = 1;

	frame->video_code = drm_match_cea_mode(mode);

	/*
	 * HDMI 1.4 VIC range: 1 <= VIC <= 64 (CEA-861-D) but
	 * HDMI 2.0 VIC range: 1 <= VIC <= 107 (CEA-861-F). So we
	 * have to make sure we dont break HDMI 1.4 sinks.
	 */
	if (!is_hdmi2_sink(connector) && frame->video_code > 64)
		frame->video_code = 0;

	/*
	 * HDMI spec says if a mode is found in HDMI 1.4b 4K modes
	 * we should send its VIC in vendor infoframes, else send the
	 * VIC in AVI infoframes. Lets check if this mode is present in
	 * HDMI 1.4b 4K modes
	 */
	if (frame->video_code) {
		u8 vendor_if_vic = drm_match_hdmi_mode(mode);
		bool is_s3d = mode->flags & DRM_MODE_FLAG_3D_MASK;

		if (drm_valid_hdmi_vic(vendor_if_vic) && !is_s3d)
			frame->video_code = 0;
	}

	frame->picture_aspect = HDMI_PICTURE_ASPECT_NONE;

	/*
	 * As some drivers don't support atomic, we can't use connector state.
	 * So just initialize the frame with default values, just the same way
	 * as it's done with other properties here.
	 */
	frame->content_type = HDMI_CONTENT_TYPE_GRAPHICS;
	frame->itc = 0;

	/*
	 * Populate picture aspect ratio from either
	 * user input (if specified) or from the CEA mode list.
	 */
	picture_aspect = mode->picture_aspect_ratio;
	if (picture_aspect == HDMI_PICTURE_ASPECT_NONE)
		picture_aspect = drm_get_cea_aspect_ratio(frame->video_code);

	/*
	 * The infoframe can't convey anything but none, 4:3
	 * and 16:9, so if the user has asked for anything else
	 * we can only satisfy it by specifying the right VIC.
	 */
	if (picture_aspect > HDMI_PICTURE_ASPECT_16_9) {
		if (picture_aspect !=
		    drm_get_cea_aspect_ratio(frame->video_code))
			return -EINVAL;
		picture_aspect = HDMI_PICTURE_ASPECT_NONE;
	}

	frame->picture_aspect = picture_aspect;
	frame->active_aspect = HDMI_ACTIVE_ASPECT_PICTURE;
	frame->scan_mode = HDMI_SCAN_MODE_UNDERSCAN;

	return 0;
}