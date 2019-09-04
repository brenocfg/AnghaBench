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
struct hdmi_audio_param {int /*<<< orphan*/  aud_input_chan_type; int /*<<< orphan*/  aud_mclk; int /*<<< orphan*/  aud_i2s_fmt; int /*<<< orphan*/  aud_input_type; int /*<<< orphan*/  aud_sampe_size; int /*<<< orphan*/  aud_codec; } ;
struct mtk_hdmi {int /*<<< orphan*/  csp; struct hdmi_audio_param aud_param; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_AUDIO_CODING_TYPE_PCM ; 
 int /*<<< orphan*/  HDMI_AUDIO_SAMPLE_SIZE_16 ; 
 int /*<<< orphan*/  HDMI_AUD_CHAN_TYPE_2_0 ; 
 int /*<<< orphan*/  HDMI_AUD_INPUT_I2S ; 
 int /*<<< orphan*/  HDMI_AUD_MCLK_128FS ; 
 int /*<<< orphan*/  HDMI_COLORSPACE_RGB ; 
 int /*<<< orphan*/  HDMI_I2S_MODE_I2S_24BIT ; 

__attribute__((used)) static int mtk_hdmi_output_init(struct mtk_hdmi *hdmi)
{
	struct hdmi_audio_param *aud_param = &hdmi->aud_param;

	hdmi->csp = HDMI_COLORSPACE_RGB;
	aud_param->aud_codec = HDMI_AUDIO_CODING_TYPE_PCM;
	aud_param->aud_sampe_size = HDMI_AUDIO_SAMPLE_SIZE_16;
	aud_param->aud_input_type = HDMI_AUD_INPUT_I2S;
	aud_param->aud_i2s_fmt = HDMI_I2S_MODE_I2S_24BIT;
	aud_param->aud_mclk = HDMI_AUD_MCLK_128FS;
	aud_param->aud_input_chan_type = HDMI_AUD_CHAN_TYPE_2_0;

	return 0;
}