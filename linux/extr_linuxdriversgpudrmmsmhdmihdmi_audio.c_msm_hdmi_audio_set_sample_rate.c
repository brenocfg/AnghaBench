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
struct hdmi_audio {int rate; } ;
struct hdmi {struct hdmi_audio audio; } ;

/* Variables and functions */
 int MSM_HDMI_SAMPLE_RATE_MAX ; 
 int /*<<< orphan*/  msm_hdmi_audio_update (struct hdmi*) ; 

void msm_hdmi_audio_set_sample_rate(struct hdmi *hdmi, int rate)
{
	struct hdmi_audio *audio;

	if (!hdmi)
		return;

	audio = &hdmi->audio;

	if ((rate < 0) || (rate >= MSM_HDMI_SAMPLE_RATE_MAX))
		return;

	audio->rate = rate;
	msm_hdmi_audio_update(hdmi);
}