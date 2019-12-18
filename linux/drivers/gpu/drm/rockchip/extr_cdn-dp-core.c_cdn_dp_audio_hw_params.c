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
struct hdmi_codec_params {int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  sample_width; } ;
struct hdmi_codec_daifmt {int fmt; } ;
struct device {int dummy; } ;
struct audio_info {int /*<<< orphan*/  format; int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  sample_width; } ;
struct cdn_dp_device {int /*<<< orphan*/  lock; struct audio_info audio_info; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFMT_I2S ; 
 int /*<<< orphan*/  AFMT_SPDIF ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int) ; 
 int EINVAL ; 
 int ENODEV ; 
#define  HDMI_I2S 129 
#define  HDMI_SPDIF 128 
 int cdn_dp_audio_config (struct cdn_dp_device*,struct audio_info*) ; 
 struct cdn_dp_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cdn_dp_audio_hw_params(struct device *dev,  void *data,
				  struct hdmi_codec_daifmt *daifmt,
				  struct hdmi_codec_params *params)
{
	struct cdn_dp_device *dp = dev_get_drvdata(dev);
	struct audio_info audio = {
		.sample_width = params->sample_width,
		.sample_rate = params->sample_rate,
		.channels = params->channels,
	};
	int ret;

	mutex_lock(&dp->lock);
	if (!dp->active) {
		ret = -ENODEV;
		goto out;
	}

	switch (daifmt->fmt) {
	case HDMI_I2S:
		audio.format = AFMT_I2S;
		break;
	case HDMI_SPDIF:
		audio.format = AFMT_SPDIF;
		break;
	default:
		DRM_DEV_ERROR(dev, "Invalid format %d\n", daifmt->fmt);
		ret = -EINVAL;
		goto out;
	}

	ret = cdn_dp_audio_config(dp, &audio);
	if (!ret)
		dp->audio_info = audio;

out:
	mutex_unlock(&dp->lock);
	return ret;
}