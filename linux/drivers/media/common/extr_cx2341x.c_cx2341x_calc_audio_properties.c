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
struct cx2341x_mpeg_params {int audio_properties; int audio_sampling_freq; int audio_mode; int audio_mode_extension; int audio_emphasis; int audio_crc; int capabilities; int audio_encoding; int audio_ac3_bitrate; int audio_l2_bitrate; } ;

/* Variables and functions */
 int CX2341X_AUDIO_ENCODING_METHOD_AC3 ; 
 int CX2341X_CAP_HAS_AC3 ; 
 int V4L2_MPEG_AUDIO_EMPHASIS_CCITT_J17 ; 
 int V4L2_MPEG_AUDIO_ENCODING_AC3 ; 
 int V4L2_MPEG_AUDIO_ENCODING_LAYER_2 ; 

__attribute__((used)) static void cx2341x_calc_audio_properties(struct cx2341x_mpeg_params *params)
{
	params->audio_properties =
		(params->audio_sampling_freq << 0) |
		(params->audio_mode << 8) |
		(params->audio_mode_extension << 10) |
		(((params->audio_emphasis == V4L2_MPEG_AUDIO_EMPHASIS_CCITT_J17)
		  ? 3 : params->audio_emphasis) << 12) |
		(params->audio_crc << 14);

	if ((params->capabilities & CX2341X_CAP_HAS_AC3) &&
	    params->audio_encoding == V4L2_MPEG_AUDIO_ENCODING_AC3) {
		params->audio_properties |=
			/* Not sure if this MPEG Layer II setting is required */
			((3 - V4L2_MPEG_AUDIO_ENCODING_LAYER_2) << 2) |
			(params->audio_ac3_bitrate << 4) |
			(CX2341X_AUDIO_ENCODING_METHOD_AC3 << 28);
	} else {
		/* Assuming MPEG Layer II */
		params->audio_properties |=
			((3 - params->audio_encoding) << 2) |
			((1 + params->audio_l2_bitrate) << 4);
	}
}