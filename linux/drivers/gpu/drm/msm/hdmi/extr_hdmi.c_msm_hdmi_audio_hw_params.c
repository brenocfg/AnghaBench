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
struct TYPE_2__ {int channels; } ;
struct hdmi_codec_params {int sample_rate; TYPE_1__ cea; int /*<<< orphan*/  sample_width; } ;
struct hdmi_codec_daifmt {int dummy; } ;
struct hdmi {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG (struct device*,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int) ; 
 int EINVAL ; 
 unsigned int HDMI_SAMPLE_RATE_176_4KHZ ; 
 unsigned int HDMI_SAMPLE_RATE_192KHZ ; 
 unsigned int HDMI_SAMPLE_RATE_32KHZ ; 
 unsigned int HDMI_SAMPLE_RATE_44_1KHZ ; 
 unsigned int HDMI_SAMPLE_RATE_48KHZ ; 
 unsigned int HDMI_SAMPLE_RATE_88_2KHZ ; 
 unsigned int HDMI_SAMPLE_RATE_96KHZ ; 
 unsigned int MSM_HDMI_AUDIO_CHANNEL_2 ; 
 unsigned int MSM_HDMI_AUDIO_CHANNEL_4 ; 
 unsigned int MSM_HDMI_AUDIO_CHANNEL_6 ; 
 unsigned int MSM_HDMI_AUDIO_CHANNEL_8 ; 
 struct hdmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  msm_hdmi_audio_info_setup (struct hdmi*,int,unsigned int,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  msm_hdmi_audio_set_sample_rate (struct hdmi*,unsigned int) ; 

__attribute__((used)) static int msm_hdmi_audio_hw_params(struct device *dev, void *data,
				    struct hdmi_codec_daifmt *daifmt,
				    struct hdmi_codec_params *params)
{
	struct hdmi *hdmi = dev_get_drvdata(dev);
	unsigned int chan;
	unsigned int channel_allocation = 0;
	unsigned int rate;
	unsigned int level_shift  = 0; /* 0dB */
	bool down_mix = false;

	DRM_DEV_DEBUG(dev, "%u Hz, %d bit, %d channels\n", params->sample_rate,
		 params->sample_width, params->cea.channels);

	switch (params->cea.channels) {
	case 2:
		/* FR and FL speakers */
		channel_allocation  = 0;
		chan = MSM_HDMI_AUDIO_CHANNEL_2;
		break;
	case 4:
		/* FC, LFE, FR and FL speakers */
		channel_allocation  = 0x3;
		chan = MSM_HDMI_AUDIO_CHANNEL_4;
		break;
	case 6:
		/* RR, RL, FC, LFE, FR and FL speakers */
		channel_allocation  = 0x0B;
		chan = MSM_HDMI_AUDIO_CHANNEL_6;
		break;
	case 8:
		/* FRC, FLC, RR, RL, FC, LFE, FR and FL speakers */
		channel_allocation  = 0x1F;
		chan = MSM_HDMI_AUDIO_CHANNEL_8;
		break;
	default:
		return -EINVAL;
	}

	switch (params->sample_rate) {
	case 32000:
		rate = HDMI_SAMPLE_RATE_32KHZ;
		break;
	case 44100:
		rate = HDMI_SAMPLE_RATE_44_1KHZ;
		break;
	case 48000:
		rate = HDMI_SAMPLE_RATE_48KHZ;
		break;
	case 88200:
		rate = HDMI_SAMPLE_RATE_88_2KHZ;
		break;
	case 96000:
		rate = HDMI_SAMPLE_RATE_96KHZ;
		break;
	case 176400:
		rate = HDMI_SAMPLE_RATE_176_4KHZ;
		break;
	case 192000:
		rate = HDMI_SAMPLE_RATE_192KHZ;
		break;
	default:
		DRM_DEV_ERROR(dev, "rate[%d] not supported!\n",
			params->sample_rate);
		return -EINVAL;
	}

	msm_hdmi_audio_set_sample_rate(hdmi, rate);
	msm_hdmi_audio_info_setup(hdmi, 1, chan, channel_allocation,
			      level_shift, down_mix);

	return 0;
}