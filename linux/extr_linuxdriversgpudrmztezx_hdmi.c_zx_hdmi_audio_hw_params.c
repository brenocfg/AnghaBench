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
union hdmi_infoframe {int /*<<< orphan*/  audio; } ;
struct zx_hdmi {int /*<<< orphan*/  dev; } ;
struct hdmi_audio_infoframe {int dummy; } ;
struct hdmi_codec_params {int sample_width; int /*<<< orphan*/  sample_rate; struct hdmi_audio_infoframe cea; } ;
struct hdmi_codec_daifmt {int fmt; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_EN ; 
 int /*<<< orphan*/  AUD_IN_EN ; 
 int /*<<< orphan*/  AUD_MODE ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FSEL_AUDIO ; 
 int HDMI_SPDIF ; 
 int /*<<< orphan*/  N_SVAL1 ; 
 int /*<<< orphan*/  N_SVAL2 ; 
 int /*<<< orphan*/  N_SVAL3 ; 
 int /*<<< orphan*/  SPDIF_EN ; 
 int /*<<< orphan*/  SPDIF_SAMPLE_SIZE_16BIT ; 
 int /*<<< orphan*/  SPDIF_SAMPLE_SIZE_20BIT ; 
 int /*<<< orphan*/  SPDIF_SAMPLE_SIZE_24BIT ; 
 int /*<<< orphan*/  SPDIF_SAMPLE_SIZE_MASK ; 
 int /*<<< orphan*/  TPI_AUD_CONFIG ; 
 struct zx_hdmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  hdmi_writeb (struct zx_hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hdmi_writeb_mask (struct zx_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct hdmi_audio_infoframe*,int) ; 
 int zx_hdmi_audio_get_n (int /*<<< orphan*/ ) ; 
 int zx_hdmi_infoframe_trans (struct zx_hdmi*,union hdmi_infoframe*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zx_hdmi_audio_hw_params(struct device *dev,
				   void *data,
				   struct hdmi_codec_daifmt *daifmt,
				   struct hdmi_codec_params *params)
{
	struct zx_hdmi *hdmi = dev_get_drvdata(dev);
	struct hdmi_audio_infoframe *cea = &params->cea;
	union hdmi_infoframe frame;
	int n;

	/* We only support spdif for now */
	if (daifmt->fmt != HDMI_SPDIF) {
		DRM_DEV_ERROR(hdmi->dev, "invalid daifmt %d\n", daifmt->fmt);
		return -EINVAL;
	}

	switch (params->sample_width) {
	case 16:
		hdmi_writeb_mask(hdmi, TPI_AUD_CONFIG, SPDIF_SAMPLE_SIZE_MASK,
				 SPDIF_SAMPLE_SIZE_16BIT);
		break;
	case 20:
		hdmi_writeb_mask(hdmi, TPI_AUD_CONFIG, SPDIF_SAMPLE_SIZE_MASK,
				 SPDIF_SAMPLE_SIZE_20BIT);
		break;
	case 24:
		hdmi_writeb_mask(hdmi, TPI_AUD_CONFIG, SPDIF_SAMPLE_SIZE_MASK,
				 SPDIF_SAMPLE_SIZE_24BIT);
		break;
	default:
		DRM_DEV_ERROR(hdmi->dev, "invalid sample width %d\n",
			      params->sample_width);
		return -EINVAL;
	}

	/* CTS is calculated by hardware, and we only need to take care of N */
	n = zx_hdmi_audio_get_n(params->sample_rate);
	hdmi_writeb(hdmi, N_SVAL1, n & 0xff);
	hdmi_writeb(hdmi, N_SVAL2, (n >> 8) & 0xff);
	hdmi_writeb(hdmi, N_SVAL3, (n >> 16) & 0xf);

	/* Enable spdif mode */
	hdmi_writeb_mask(hdmi, AUD_MODE, SPDIF_EN, SPDIF_EN);

	/* Enable audio input */
	hdmi_writeb_mask(hdmi, AUD_EN, AUD_IN_EN, AUD_IN_EN);

	memcpy(&frame.audio, cea, sizeof(*cea));

	return zx_hdmi_infoframe_trans(hdmi, &frame, FSEL_AUDIO);
}