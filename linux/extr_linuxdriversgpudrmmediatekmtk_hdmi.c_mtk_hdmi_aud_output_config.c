#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
struct TYPE_5__ {TYPE_1__ iec; } ;
struct TYPE_6__ {TYPE_2__ codec_params; } ;
struct mtk_hdmi {TYPE_3__ aud_param; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_hdmi_aud_enable_packet (struct mtk_hdmi*,int) ; 
 int /*<<< orphan*/  mtk_hdmi_aud_on_off_hw_ncts (struct mtk_hdmi*,int) ; 
 int /*<<< orphan*/  mtk_hdmi_aud_set_input (struct mtk_hdmi*) ; 
 int /*<<< orphan*/  mtk_hdmi_aud_set_src (struct mtk_hdmi*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_aud_mute (struct mtk_hdmi*) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_aud_set_channel_status (struct mtk_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_aud_unmute (struct mtk_hdmi*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mtk_hdmi_aud_output_config(struct mtk_hdmi *hdmi,
				      struct drm_display_mode *display_mode)
{
	mtk_hdmi_hw_aud_mute(hdmi);
	mtk_hdmi_aud_enable_packet(hdmi, false);

	mtk_hdmi_aud_set_input(hdmi);
	mtk_hdmi_aud_set_src(hdmi, display_mode);
	mtk_hdmi_hw_aud_set_channel_status(hdmi,
			hdmi->aud_param.codec_params.iec.status);

	usleep_range(50, 100);

	mtk_hdmi_aud_on_off_hw_ncts(hdmi, true);
	mtk_hdmi_aud_enable_packet(hdmi, true);
	mtk_hdmi_hw_aud_unmute(hdmi);
	return 0;
}