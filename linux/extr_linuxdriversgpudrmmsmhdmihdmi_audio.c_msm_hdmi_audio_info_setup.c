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
typedef  size_t uint32_t ;
struct TYPE_2__ {size_t channel_allocation; size_t level_shift_value; int downmix_inhibit; int /*<<< orphan*/  channels; } ;
struct hdmi_audio {int enabled; TYPE_1__ infoframe; } ;
struct hdmi {struct hdmi_audio audio; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENXIO ; 
 int msm_hdmi_audio_update (struct hdmi*) ; 
 int /*<<< orphan*/ * nchannels ; 

int msm_hdmi_audio_info_setup(struct hdmi *hdmi, bool enabled,
	uint32_t num_of_channels, uint32_t channel_allocation,
	uint32_t level_shift, bool down_mix)
{
	struct hdmi_audio *audio;

	if (!hdmi)
		return -ENXIO;

	audio = &hdmi->audio;

	if (num_of_channels >= ARRAY_SIZE(nchannels))
		return -EINVAL;

	audio->enabled = enabled;
	audio->infoframe.channels = nchannels[num_of_channels];
	audio->infoframe.channel_allocation = channel_allocation;
	audio->infoframe.level_shift_value = level_shift;
	audio->infoframe.downmix_inhibit = down_mix;

	return msm_hdmi_audio_update(hdmi);
}