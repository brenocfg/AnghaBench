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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct hdmi_vendor_infoframe {int /*<<< orphan*/  s3d_struct; scalar_t__ vic; } ;
struct drm_display_mode {int flags; } ;
struct TYPE_2__ {int has_hdmi_infoframe; } ;
struct drm_connector {TYPE_1__ display_info; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_3D_MASK ; 
 int EINVAL ; 
 scalar_t__ drm_match_hdmi_mode (struct drm_display_mode const*) ; 
 int hdmi_vendor_infoframe_init (struct hdmi_vendor_infoframe*) ; 
 int /*<<< orphan*/  s3d_structure_from_display_mode (struct drm_display_mode const*) ; 

int
drm_hdmi_vendor_infoframe_from_display_mode(struct hdmi_vendor_infoframe *frame,
					    struct drm_connector *connector,
					    const struct drm_display_mode *mode)
{
	/*
	 * FIXME: sil-sii8620 doesn't have a connector around when
	 * we need one, so we have to be prepared for a NULL connector.
	 */
	bool has_hdmi_infoframe = connector ?
		connector->display_info.has_hdmi_infoframe : false;
	int err;
	u32 s3d_flags;
	u8 vic;

	if (!frame || !mode)
		return -EINVAL;

	if (!has_hdmi_infoframe)
		return -EINVAL;

	vic = drm_match_hdmi_mode(mode);
	s3d_flags = mode->flags & DRM_MODE_FLAG_3D_MASK;

	/*
	 * Even if it's not absolutely necessary to send the infoframe
	 * (ie.vic==0 and s3d_struct==0) we will still send it if we
	 * know that the sink can handle it. This is based on a
	 * suggestion in HDMI 2.0 Appendix F. Apparently some sinks
	 * have trouble realizing that they shuld switch from 3D to 2D
	 * mode if the source simply stops sending the infoframe when
	 * it wants to switch from 3D to 2D.
	 */

	if (vic && s3d_flags)
		return -EINVAL;

	err = hdmi_vendor_infoframe_init(frame);
	if (err < 0)
		return err;

	frame->vic = vic;
	frame->s3d_struct = s3d_structure_from_display_mode(mode);

	return 0;
}