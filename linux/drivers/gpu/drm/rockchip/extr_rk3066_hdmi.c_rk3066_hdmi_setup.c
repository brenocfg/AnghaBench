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
struct TYPE_2__ {int vic; scalar_t__ sink_is_hdmi; int /*<<< orphan*/  colorimetry; int /*<<< orphan*/  enc_out_format; } ;
struct rk3066_hdmi {int tmdsclk; TYPE_1__ hdmi_data; } ;
struct drm_display_mode {int clock; } ;

/* Variables and functions */
 int HDMI_AUDIO_DISABLE ; 
 int /*<<< orphan*/  HDMI_AV_CTRL1 ; 
 int /*<<< orphan*/  HDMI_COLORIMETRY_ITU_601 ; 
 int /*<<< orphan*/  HDMI_COLORIMETRY_ITU_709 ; 
 int /*<<< orphan*/  HDMI_COLORSPACE_RGB ; 
 int /*<<< orphan*/  HDMI_DEEP_COLOR_MODE ; 
 int /*<<< orphan*/  HDMI_HDCP_CTRL ; 
 scalar_t__ HDMI_SYS_POWER_MODE_B ; 
 scalar_t__ HDMI_SYS_POWER_MODE_E ; 
 int /*<<< orphan*/  HDMI_VIDEO_AUDIO_DISABLE_MASK ; 
 int /*<<< orphan*/  HDMI_VIDEO_CTRL1 ; 
 int /*<<< orphan*/  HDMI_VIDEO_CTRL2 ; 
 int /*<<< orphan*/  HDMI_VIDEO_DE_MASK ; 
 int HDMI_VIDEO_DISABLE ; 
 int HDMI_VIDEO_EXTERNAL_DE ; 
 int HDMI_VIDEO_INPUT_COLOR_RGB ; 
 int HDMI_VIDEO_INPUT_DATA_DEPTH_8BIT ; 
 int HDMI_VIDEO_MODE_HDMI ; 
 int /*<<< orphan*/  HDMI_VIDEO_MODE_MASK ; 
 int HDMI_VIDEO_OUTPUT_RGB444 ; 
 int drm_match_cea_mode (struct drm_display_mode*) ; 
 int /*<<< orphan*/  hdmi_modb (struct rk3066_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hdmi_writeb (struct rk3066_hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rk3066_hdmi_config_avi (struct rk3066_hdmi*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  rk3066_hdmi_config_phy (struct rk3066_hdmi*) ; 
 int /*<<< orphan*/  rk3066_hdmi_config_video_timing (struct rk3066_hdmi*,struct drm_display_mode*) ; 
 scalar_t__ rk3066_hdmi_get_power_mode (struct rk3066_hdmi*) ; 
 int /*<<< orphan*/  rk3066_hdmi_i2c_init (struct rk3066_hdmi*) ; 
 int /*<<< orphan*/  rk3066_hdmi_set_power_mode (struct rk3066_hdmi*,scalar_t__) ; 

__attribute__((used)) static int rk3066_hdmi_setup(struct rk3066_hdmi *hdmi,
			     struct drm_display_mode *mode)
{
	hdmi->hdmi_data.vic = drm_match_cea_mode(mode);
	hdmi->hdmi_data.enc_out_format = HDMI_COLORSPACE_RGB;

	if (hdmi->hdmi_data.vic == 6 || hdmi->hdmi_data.vic == 7 ||
	    hdmi->hdmi_data.vic == 21 || hdmi->hdmi_data.vic == 22 ||
	    hdmi->hdmi_data.vic == 2 || hdmi->hdmi_data.vic == 3 ||
	    hdmi->hdmi_data.vic == 17 || hdmi->hdmi_data.vic == 18)
		hdmi->hdmi_data.colorimetry = HDMI_COLORIMETRY_ITU_601;
	else
		hdmi->hdmi_data.colorimetry = HDMI_COLORIMETRY_ITU_709;

	hdmi->tmdsclk = mode->clock * 1000;

	/* Mute video and audio output. */
	hdmi_modb(hdmi, HDMI_VIDEO_CTRL2, HDMI_VIDEO_AUDIO_DISABLE_MASK,
		  HDMI_AUDIO_DISABLE | HDMI_VIDEO_DISABLE);

	/* Set power state to mode B. */
	if (rk3066_hdmi_get_power_mode(hdmi) != HDMI_SYS_POWER_MODE_B)
		rk3066_hdmi_set_power_mode(hdmi, HDMI_SYS_POWER_MODE_B);

	/* Input video mode is RGB 24 bit. Use external data enable signal. */
	hdmi_modb(hdmi, HDMI_AV_CTRL1,
		  HDMI_VIDEO_DE_MASK, HDMI_VIDEO_EXTERNAL_DE);
	hdmi_writeb(hdmi, HDMI_VIDEO_CTRL1,
		    HDMI_VIDEO_OUTPUT_RGB444 |
		    HDMI_VIDEO_INPUT_DATA_DEPTH_8BIT |
		    HDMI_VIDEO_INPUT_COLOR_RGB);
	hdmi_writeb(hdmi, HDMI_DEEP_COLOR_MODE, 0x20);

	rk3066_hdmi_config_video_timing(hdmi, mode);

	if (hdmi->hdmi_data.sink_is_hdmi) {
		hdmi_modb(hdmi, HDMI_HDCP_CTRL, HDMI_VIDEO_MODE_MASK,
			  HDMI_VIDEO_MODE_HDMI);
		rk3066_hdmi_config_avi(hdmi, mode);
	} else {
		hdmi_modb(hdmi, HDMI_HDCP_CTRL, HDMI_VIDEO_MODE_MASK, 0);
	}

	rk3066_hdmi_config_phy(hdmi);

	rk3066_hdmi_set_power_mode(hdmi, HDMI_SYS_POWER_MODE_E);

	/*
	 * When the IP controller is configured with accurate video
	 * timing, the TMDS clock source should be switched to
	 * DCLK_LCDC, so we need to init the TMDS rate to the pixel mode
	 * clock rate and reconfigure the DDC clock.
	 */
	rk3066_hdmi_i2c_init(hdmi);

	/* Unmute video output. */
	hdmi_modb(hdmi, HDMI_VIDEO_CTRL2,
		  HDMI_VIDEO_AUDIO_DISABLE_MASK, HDMI_AUDIO_DISABLE);
	return 0;
}