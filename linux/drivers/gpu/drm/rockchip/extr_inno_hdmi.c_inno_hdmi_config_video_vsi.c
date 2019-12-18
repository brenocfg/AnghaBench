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
struct inno_hdmi {int /*<<< orphan*/  connector; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFOFRAME_VSI ; 
 int drm_hdmi_vendor_infoframe_from_display_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct drm_display_mode*) ; 
 int inno_hdmi_upload_frame (struct inno_hdmi*,int,union hdmi_infoframe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_PACKET_VSI_EN ; 
 int /*<<< orphan*/  v_PACKET_VSI_EN (int) ; 

__attribute__((used)) static int inno_hdmi_config_video_vsi(struct inno_hdmi *hdmi,
				      struct drm_display_mode *mode)
{
	union hdmi_infoframe frame;
	int rc;

	rc = drm_hdmi_vendor_infoframe_from_display_mode(&frame.vendor.hdmi,
							 &hdmi->connector,
							 mode);

	return inno_hdmi_upload_frame(hdmi, rc, &frame, INFOFRAME_VSI,
		m_PACKET_VSI_EN, v_PACKET_VSI_EN(0), v_PACKET_VSI_EN(1));
}