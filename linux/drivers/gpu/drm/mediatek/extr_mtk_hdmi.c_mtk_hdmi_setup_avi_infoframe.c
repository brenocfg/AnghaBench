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
struct mtk_hdmi {int /*<<< orphan*/  dev; int /*<<< orphan*/  conn; } ;
struct hdmi_avi_infoframe {int dummy; } ;
struct drm_display_mode {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ drm_hdmi_avi_infoframe_from_display_mode (struct hdmi_avi_infoframe*,int /*<<< orphan*/ *,struct drm_display_mode*) ; 
 scalar_t__ hdmi_avi_infoframe_pack (struct hdmi_avi_infoframe*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_send_info_frame (struct mtk_hdmi*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mtk_hdmi_setup_avi_infoframe(struct mtk_hdmi *hdmi,
					struct drm_display_mode *mode)
{
	struct hdmi_avi_infoframe frame;
	u8 buffer[17];
	ssize_t err;

	err = drm_hdmi_avi_infoframe_from_display_mode(&frame,
						       &hdmi->conn, mode);
	if (err < 0) {
		dev_err(hdmi->dev,
			"Failed to get AVI infoframe from mode: %zd\n", err);
		return err;
	}

	err = hdmi_avi_infoframe_pack(&frame, buffer, sizeof(buffer));
	if (err < 0) {
		dev_err(hdmi->dev, "Failed to pack AVI infoframe: %zd\n", err);
		return err;
	}

	mtk_hdmi_hw_send_info_frame(hdmi, buffer, sizeof(buffer));
	return 0;
}