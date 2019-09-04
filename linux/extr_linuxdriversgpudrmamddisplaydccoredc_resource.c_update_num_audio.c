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
struct resource_straps {scalar_t__ hdmi_disable; int dc_pinstraps_audio; int audio_stream_number; } ;
struct audio_support {int dp_audio; int hdmi_audio_native; int hdmi_audio_on_dongle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_ERR (char*) ; 

__attribute__((used)) static void update_num_audio(
	const struct resource_straps *straps,
	unsigned int *num_audio,
	struct audio_support *aud_support)
{
	aud_support->dp_audio = true;
	aud_support->hdmi_audio_native = false;
	aud_support->hdmi_audio_on_dongle = false;

	if (straps->hdmi_disable == 0) {
		if (straps->dc_pinstraps_audio & 0x2) {
			aud_support->hdmi_audio_on_dongle = true;
			aud_support->hdmi_audio_native = true;
		}
	}

	switch (straps->audio_stream_number) {
	case 0: /* multi streams supported */
		break;
	case 1: /* multi streams not supported */
		*num_audio = 1;
		break;
	default:
		DC_ERR("DC: unexpected audio fuse!\n");
	}
}