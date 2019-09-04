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
struct audio_support {int /*<<< orphan*/  hdmi_audio_native; int /*<<< orphan*/  hdmi_audio_on_dongle; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;
typedef  enum display_dongle_type { ____Placeholder_display_dongle_type } display_dongle_type ;

/* Variables and functions */
#define  DISPLAY_DONGLE_DP_DVI_DONGLE 130 
#define  DISPLAY_DONGLE_DP_HDMI_DONGLE 129 
#define  DISPLAY_DONGLE_DP_HDMI_MISMATCHED_DONGLE 128 
 int SIGNAL_TYPE_DVI_SINGLE_LINK ; 
 int SIGNAL_TYPE_HDMI_TYPE_A ; 
 int SIGNAL_TYPE_NONE ; 

__attribute__((used)) static enum signal_type decide_signal_from_strap_and_dongle_type(
		enum display_dongle_type dongle_type,
		struct audio_support *audio_support)
{
	enum signal_type signal = SIGNAL_TYPE_NONE;

	switch (dongle_type) {
	case DISPLAY_DONGLE_DP_HDMI_DONGLE:
		if (audio_support->hdmi_audio_on_dongle)
			signal =  SIGNAL_TYPE_HDMI_TYPE_A;
		else
			signal = SIGNAL_TYPE_DVI_SINGLE_LINK;
		break;
	case DISPLAY_DONGLE_DP_DVI_DONGLE:
		signal = SIGNAL_TYPE_DVI_SINGLE_LINK;
		break;
	case DISPLAY_DONGLE_DP_HDMI_MISMATCHED_DONGLE:
		if (audio_support->hdmi_audio_native)
			signal =  SIGNAL_TYPE_HDMI_TYPE_A;
		else
			signal = SIGNAL_TYPE_DVI_SINGLE_LINK;
		break;
	default:
		signal = SIGNAL_TYPE_NONE;
		break;
	}

	return signal;
}