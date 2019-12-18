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
struct TYPE_2__ {int vic; scalar_t__ sink_is_hdmi; int /*<<< orphan*/  colorimetry; void* enc_out_format; void* enc_in_format; } ;
struct inno_hdmi {int tmds_rate; TYPE_1__ hdmi_data; } ;
struct drm_display_mode {int clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_AV_MUTE ; 
 int /*<<< orphan*/  HDMI_COLORIMETRY_ITU_601 ; 
 int /*<<< orphan*/  HDMI_COLORIMETRY_ITU_709 ; 
 void* HDMI_COLORSPACE_RGB ; 
 int /*<<< orphan*/  HDMI_HDCP_CTRL ; 
 int drm_match_cea_mode (struct drm_display_mode*) ; 
 int /*<<< orphan*/  hdmi_modb (struct inno_hdmi*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  hdmi_writeb (struct inno_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inno_hdmi_config_video_avi (struct inno_hdmi*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  inno_hdmi_config_video_csc (struct inno_hdmi*) ; 
 int /*<<< orphan*/  inno_hdmi_config_video_timing (struct inno_hdmi*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  inno_hdmi_config_video_vsi (struct inno_hdmi*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  inno_hdmi_i2c_init (struct inno_hdmi*) ; 
 int m_AUDIO_MUTE ; 
 int m_VIDEO_BLACK ; 
 int v_AUDIO_MUTE (int) ; 
 int /*<<< orphan*/  v_HDMI_DVI (scalar_t__) ; 
 int v_VIDEO_MUTE (int) ; 

__attribute__((used)) static int inno_hdmi_setup(struct inno_hdmi *hdmi,
			   struct drm_display_mode *mode)
{
	hdmi->hdmi_data.vic = drm_match_cea_mode(mode);

	hdmi->hdmi_data.enc_in_format = HDMI_COLORSPACE_RGB;
	hdmi->hdmi_data.enc_out_format = HDMI_COLORSPACE_RGB;

	if ((hdmi->hdmi_data.vic == 6) || (hdmi->hdmi_data.vic == 7) ||
	    (hdmi->hdmi_data.vic == 21) || (hdmi->hdmi_data.vic == 22) ||
	    (hdmi->hdmi_data.vic == 2) || (hdmi->hdmi_data.vic == 3) ||
	    (hdmi->hdmi_data.vic == 17) || (hdmi->hdmi_data.vic == 18))
		hdmi->hdmi_data.colorimetry = HDMI_COLORIMETRY_ITU_601;
	else
		hdmi->hdmi_data.colorimetry = HDMI_COLORIMETRY_ITU_709;

	/* Mute video and audio output */
	hdmi_modb(hdmi, HDMI_AV_MUTE, m_AUDIO_MUTE | m_VIDEO_BLACK,
		  v_AUDIO_MUTE(1) | v_VIDEO_MUTE(1));

	/* Set HDMI Mode */
	hdmi_writeb(hdmi, HDMI_HDCP_CTRL,
		    v_HDMI_DVI(hdmi->hdmi_data.sink_is_hdmi));

	inno_hdmi_config_video_timing(hdmi, mode);

	inno_hdmi_config_video_csc(hdmi);

	if (hdmi->hdmi_data.sink_is_hdmi) {
		inno_hdmi_config_video_avi(hdmi, mode);
		inno_hdmi_config_video_vsi(hdmi, mode);
	}

	/*
	 * When IP controller have configured to an accurate video
	 * timing, then the TMDS clock source would be switched to
	 * DCLK_LCDC, so we need to init the TMDS rate to mode pixel
	 * clock rate, and reconfigure the DDC clock.
	 */
	hdmi->tmds_rate = mode->clock * 1000;
	inno_hdmi_i2c_init(hdmi);

	/* Unmute video and audio output */
	hdmi_modb(hdmi, HDMI_AV_MUTE, m_AUDIO_MUTE | m_VIDEO_BLACK,
		  v_AUDIO_MUTE(0) | v_VIDEO_MUTE(0));

	return 0;
}