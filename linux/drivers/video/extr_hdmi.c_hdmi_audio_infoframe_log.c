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
struct hdmi_audio_infoframe {char* channels; char* channel_allocation; char* level_shift_value; scalar_t__ downmix_inhibit; int /*<<< orphan*/  coding_type_ext; int /*<<< orphan*/  sample_frequency; int /*<<< orphan*/  sample_size; int /*<<< orphan*/  coding_type; } ;
struct hdmi_any_infoframe {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 char* hdmi_audio_coding_type_ext_get_name (int /*<<< orphan*/ ) ; 
 char* hdmi_audio_coding_type_get_name (int /*<<< orphan*/ ) ; 
 char* hdmi_audio_sample_frequency_get_name (int /*<<< orphan*/ ) ; 
 char* hdmi_audio_sample_size_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_infoframe_log_header (char const*,struct device*,struct hdmi_any_infoframe const*) ; 
 int /*<<< orphan*/  hdmi_log (char*,...) ; 

__attribute__((used)) static void hdmi_audio_infoframe_log(const char *level,
				     struct device *dev,
				     const struct hdmi_audio_infoframe *frame)
{
	hdmi_infoframe_log_header(level, dev,
				  (const struct hdmi_any_infoframe *)frame);

	if (frame->channels)
		hdmi_log("    channels: %u\n", frame->channels - 1);
	else
		hdmi_log("    channels: Refer to stream header\n");
	hdmi_log("    coding type: %s\n",
			hdmi_audio_coding_type_get_name(frame->coding_type));
	hdmi_log("    sample size: %s\n",
			hdmi_audio_sample_size_get_name(frame->sample_size));
	hdmi_log("    sample frequency: %s\n",
			hdmi_audio_sample_frequency_get_name(frame->sample_frequency));
	hdmi_log("    coding type ext: %s\n",
			hdmi_audio_coding_type_ext_get_name(frame->coding_type_ext));
	hdmi_log("    channel allocation: 0x%x\n",
			frame->channel_allocation);
	hdmi_log("    level shift value: %u dB\n",
			frame->level_shift_value);
	hdmi_log("    downmix inhibit: %s\n",
			frame->downmix_inhibit ? "Yes" : "No");
}