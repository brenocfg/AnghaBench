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
struct mtk_hdmi {int dummy; } ;
struct drm_display_mode {int flags; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_3D_MASK ; 
 int /*<<< orphan*/  mtk_hdmi_setup_audio_infoframe (struct mtk_hdmi*) ; 
 int /*<<< orphan*/  mtk_hdmi_setup_avi_infoframe (struct mtk_hdmi*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  mtk_hdmi_setup_spd_infoframe (struct mtk_hdmi*,char*,char*) ; 
 int /*<<< orphan*/  mtk_hdmi_setup_vendor_specific_infoframe (struct mtk_hdmi*,struct drm_display_mode*) ; 

__attribute__((used)) static void mtk_hdmi_send_infoframe(struct mtk_hdmi *hdmi,
				    struct drm_display_mode *mode)
{
	mtk_hdmi_setup_audio_infoframe(hdmi);
	mtk_hdmi_setup_avi_infoframe(hdmi, mode);
	mtk_hdmi_setup_spd_infoframe(hdmi, "mediatek", "On-chip HDMI");
	if (mode->flags & DRM_MODE_FLAG_3D_MASK)
		mtk_hdmi_setup_vendor_specific_infoframe(hdmi, mode);
}