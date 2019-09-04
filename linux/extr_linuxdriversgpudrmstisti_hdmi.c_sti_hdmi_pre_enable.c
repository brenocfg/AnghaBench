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
struct TYPE_4__ {scalar_t__ enabled; } ;
struct sti_hdmi {int enabled; TYPE_2__ audio; TYPE_1__* phy_ops; int /*<<< orphan*/  clk_phy; int /*<<< orphan*/  clk_tmds; int /*<<< orphan*/  clk_pix; } ;
struct drm_bridge {struct sti_hdmi* driver_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* start ) (struct sti_hdmi*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  HDMI_INT_EN ; 
 int /*<<< orphan*/  HDMI_WORKING_INT ; 
 scalar_t__ clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_active_area (struct sti_hdmi*) ; 
 scalar_t__ hdmi_audio_configure (struct sti_hdmi*) ; 
 int /*<<< orphan*/  hdmi_audio_infoframe_config (struct sti_hdmi*) ; 
 scalar_t__ hdmi_avi_infoframe_config (struct sti_hdmi*) ; 
 int /*<<< orphan*/  hdmi_config (struct sti_hdmi*) ; 
 int /*<<< orphan*/  hdmi_swreset (struct sti_hdmi*) ; 
 scalar_t__ hdmi_vendor_infoframe_config (struct sti_hdmi*) ; 
 int /*<<< orphan*/  hdmi_write (struct sti_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sti_hdmi*) ; 

__attribute__((used)) static void sti_hdmi_pre_enable(struct drm_bridge *bridge)
{
	struct sti_hdmi *hdmi = bridge->driver_private;

	DRM_DEBUG_DRIVER("\n");

	if (hdmi->enabled)
		return;

	/* Prepare/enable clocks */
	if (clk_prepare_enable(hdmi->clk_pix))
		DRM_ERROR("Failed to prepare/enable hdmi_pix clk\n");
	if (clk_prepare_enable(hdmi->clk_tmds))
		DRM_ERROR("Failed to prepare/enable hdmi_tmds clk\n");
	if (clk_prepare_enable(hdmi->clk_phy))
		DRM_ERROR("Failed to prepare/enable hdmi_rejec_pll clk\n");

	hdmi->enabled = true;

	/* Program hdmi serializer and start phy */
	if (!hdmi->phy_ops->start(hdmi)) {
		DRM_ERROR("Unable to start hdmi phy\n");
		return;
	}

	/* Program hdmi active area */
	hdmi_active_area(hdmi);

	/* Enable working interrupts */
	hdmi_write(hdmi, HDMI_WORKING_INT, HDMI_INT_EN);

	/* Program hdmi config */
	hdmi_config(hdmi);

	/* Program AVI infoframe */
	if (hdmi_avi_infoframe_config(hdmi))
		DRM_ERROR("Unable to configure AVI infoframe\n");

	if (hdmi->audio.enabled) {
		if (hdmi_audio_configure(hdmi))
			DRM_ERROR("Unable to configure audio\n");
	} else {
		hdmi_audio_infoframe_config(hdmi);
	}

	/* Program VS infoframe */
	if (hdmi_vendor_infoframe_config(hdmi))
		DRM_ERROR("Unable to configure VS infoframe\n");

	/* Sw reset */
	hdmi_swreset(hdmi);
}