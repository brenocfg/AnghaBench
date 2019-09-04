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
struct hdmi_codec_params {int sample_width; int /*<<< orphan*/  sample_rate; } ;
struct hdmi_codec_daifmt {scalar_t__ fmt; int bit_clk_master; int frame_clk_master; } ;
struct dw_hdmi_i2s_audio_data {struct dw_hdmi* hdmi; } ;
struct dw_hdmi {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HDMI_AUD_CONF0 ; 
 int /*<<< orphan*/  HDMI_AUD_CONF0_I2S_ALL_ENABLE ; 
 int /*<<< orphan*/  HDMI_AUD_CONF1 ; 
 int /*<<< orphan*/  HDMI_AUD_CONF1_WIDTH_16 ; 
 int /*<<< orphan*/  HDMI_AUD_CONF1_WIDTH_24 ; 
 int /*<<< orphan*/  HDMI_AUD_INPUTCLKFS ; 
 int /*<<< orphan*/  HDMI_AUD_INPUTCLKFS_64FS ; 
 scalar_t__ HDMI_I2S ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dw_hdmi_audio_enable (struct dw_hdmi*) ; 
 int /*<<< orphan*/  dw_hdmi_set_sample_rate (struct dw_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_write (struct dw_hdmi_i2s_audio_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_hdmi_i2s_hw_params(struct device *dev, void *data,
				 struct hdmi_codec_daifmt *fmt,
				 struct hdmi_codec_params *hparms)
{
	struct dw_hdmi_i2s_audio_data *audio = data;
	struct dw_hdmi *hdmi = audio->hdmi;
	u8 conf0 = 0;
	u8 conf1 = 0;
	u8 inputclkfs = 0;

	/* it cares I2S only */
	if ((fmt->fmt != HDMI_I2S) ||
	    (fmt->bit_clk_master | fmt->frame_clk_master)) {
		dev_err(dev, "unsupported format/settings\n");
		return -EINVAL;
	}

	inputclkfs	= HDMI_AUD_INPUTCLKFS_64FS;
	conf0		= HDMI_AUD_CONF0_I2S_ALL_ENABLE;

	switch (hparms->sample_width) {
	case 16:
		conf1 = HDMI_AUD_CONF1_WIDTH_16;
		break;
	case 24:
	case 32:
		conf1 = HDMI_AUD_CONF1_WIDTH_24;
		break;
	}

	dw_hdmi_set_sample_rate(hdmi, hparms->sample_rate);

	hdmi_write(audio, inputclkfs, HDMI_AUD_INPUTCLKFS);
	hdmi_write(audio, conf0, HDMI_AUD_CONF0);
	hdmi_write(audio, conf1, HDMI_AUD_CONF1);

	dw_hdmi_audio_enable(hdmi);

	return 0;
}