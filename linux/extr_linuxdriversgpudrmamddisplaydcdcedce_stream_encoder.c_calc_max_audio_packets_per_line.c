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
typedef  int uint32_t ;
struct audio_crtc_info {int h_total; int h_active; int pixel_repetition; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t calc_max_audio_packets_per_line(
	const struct audio_crtc_info *crtc_info)
{
	uint32_t max_packets_per_line;

	max_packets_per_line =
		crtc_info->h_total - crtc_info->h_active;

	if (crtc_info->pixel_repetition)
		max_packets_per_line *= crtc_info->pixel_repetition;

	/* for other hdmi features */
	max_packets_per_line -= 58;
	/* for Control Period */
	max_packets_per_line -= 16;
	/* Number of Audio Packets per Line */
	max_packets_per_line /= 32;

	return max_packets_per_line;
}