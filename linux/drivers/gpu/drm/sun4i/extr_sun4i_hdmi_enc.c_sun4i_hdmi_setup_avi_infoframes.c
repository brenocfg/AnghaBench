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
struct sun4i_hdmi {scalar_t__ base; int /*<<< orphan*/  connector; } ;
struct hdmi_avi_infoframe {int dummy; } ;
struct drm_display_mode {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ SUN4I_HDMI_AVI_INFOFRAME_REG (int) ; 
 int drm_hdmi_avi_infoframe_from_display_mode (struct hdmi_avi_infoframe*,int /*<<< orphan*/ *,struct drm_display_mode*) ; 
 int hdmi_avi_infoframe_pack (struct hdmi_avi_infoframe*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sun4i_hdmi_setup_avi_infoframes(struct sun4i_hdmi *hdmi,
					   struct drm_display_mode *mode)
{
	struct hdmi_avi_infoframe frame;
	u8 buffer[17];
	int i, ret;

	ret = drm_hdmi_avi_infoframe_from_display_mode(&frame,
						       &hdmi->connector, mode);
	if (ret < 0) {
		DRM_ERROR("Failed to get infoframes from mode\n");
		return ret;
	}

	ret = hdmi_avi_infoframe_pack(&frame, buffer, sizeof(buffer));
	if (ret < 0) {
		DRM_ERROR("Failed to pack infoframes\n");
		return ret;
	}

	for (i = 0; i < sizeof(buffer); i++)
		writeb(buffer[i], hdmi->base + SUN4I_HDMI_AVI_INFOFRAME_REG(i));

	return 0;
}