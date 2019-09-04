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
struct TYPE_2__ {scalar_t__ RATE_88_2; scalar_t__ RATE_96; scalar_t__ RATE_176_4; scalar_t__ RATE_192; } ;
union audio_sample_rates {TYPE_1__ rate; } ;
typedef  int uint32_t ;
struct audio_crtc_info {int requested_pixel_clock; int v_active; int pixel_repetition; int h_total; int h_active; int refresh_rate; int color_depth; scalar_t__ interlaced; } ;

/* Variables and functions */
#define  COLOR_DEPTH_101010 130 
#define  COLOR_DEPTH_121212 129 
#define  COLOR_DEPTH_888 128 

__attribute__((used)) static void check_audio_bandwidth_hdmi(
	const struct audio_crtc_info *crtc_info,
	uint32_t channel_count,
	union audio_sample_rates *sample_rates)
{
	uint32_t samples;
	uint32_t  h_blank;
	bool limit_freq_to_48_khz = false;
	bool limit_freq_to_88_2_khz = false;
	bool limit_freq_to_96_khz = false;
	bool limit_freq_to_174_4_khz = false;

	/* For two channels supported return whatever sink support,unmodified*/
	if (channel_count > 2) {

		/* Based on HDMI spec 1.3 Table 7.5 */
		if ((crtc_info->requested_pixel_clock <= 27000) &&
		(crtc_info->v_active <= 576) &&
		!(crtc_info->interlaced) &&
		!(crtc_info->pixel_repetition == 2 ||
		crtc_info->pixel_repetition == 4)) {
			limit_freq_to_48_khz = true;

		} else if ((crtc_info->requested_pixel_clock <= 27000) &&
				(crtc_info->v_active <= 576) &&
				(crtc_info->interlaced) &&
				(crtc_info->pixel_repetition == 2)) {
			limit_freq_to_88_2_khz = true;

		} else if ((crtc_info->requested_pixel_clock <= 54000) &&
				(crtc_info->v_active <= 576) &&
				!(crtc_info->interlaced)) {
			limit_freq_to_174_4_khz = true;
		}
	}

	/* Also do some calculation for the available Audio Bandwidth for the
	 * 8 ch (i.e. for the Layout 1 => ch > 2)
	 */
	h_blank = crtc_info->h_total - crtc_info->h_active;

	if (crtc_info->pixel_repetition)
		h_blank *= crtc_info->pixel_repetition;

	/*based on HDMI spec 1.3 Table 7.5 */
	h_blank -= 58;
	/*for Control Period */
	h_blank -= 16;

	samples = h_blank * 10;
	/* Number of Audio Packets (multiplied by 10) per Line (for 8 ch number
	 * of Audio samples per line multiplied by 10 - Layout 1)
	 */
	samples /= 32;
	samples *= crtc_info->v_active;
	/*Number of samples multiplied by 10, per second */
	samples *= crtc_info->refresh_rate;
	/*Number of Audio samples per second */
	samples /= 10;

	/* @todo do it after deep color is implemented
	 * 8xx - deep color bandwidth scaling
	 * Extra bandwidth is avaliable in deep color b/c link runs faster than
	 * pixel rate. This has the effect of allowing more tmds characters to
	 * be transmitted during blank
	 */

	switch (crtc_info->color_depth) {
	case COLOR_DEPTH_888:
		samples *= 4;
		break;
	case COLOR_DEPTH_101010:
		samples *= 5;
		break;
	case COLOR_DEPTH_121212:
		samples *= 6;
		break;
	default:
		samples *= 4;
		break;
	}

	samples /= 4;

	/*check limitation*/
	if (samples < 88200)
		limit_freq_to_48_khz = true;
	else if (samples < 96000)
		limit_freq_to_88_2_khz = true;
	else if (samples < 176400)
		limit_freq_to_96_khz = true;
	else if (samples < 192000)
		limit_freq_to_174_4_khz = true;

	if (sample_rates != NULL) {
		/* limit frequencies */
		if (limit_freq_to_174_4_khz)
			sample_rates->rate.RATE_192 = 0;

		if (limit_freq_to_96_khz) {
			sample_rates->rate.RATE_192 = 0;
			sample_rates->rate.RATE_176_4 = 0;
		}
		if (limit_freq_to_88_2_khz) {
			sample_rates->rate.RATE_192 = 0;
			sample_rates->rate.RATE_176_4 = 0;
			sample_rates->rate.RATE_96 = 0;
		}
		if (limit_freq_to_48_khz) {
			sample_rates->rate.RATE_192 = 0;
			sample_rates->rate.RATE_176_4 = 0;
			sample_rates->rate.RATE_96 = 0;
			sample_rates->rate.RATE_88_2 = 0;
		}
	}
}