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
struct audio_clock_info {int pixel_clock_in_10khz; int cts_32khz; int cts_44khz; int cts_48khz; int n_32khz; int n_44khz; int n_48khz; } ;
typedef  enum dc_color_depth { ____Placeholder_dc_color_depth } dc_color_depth ;

/* Variables and functions */
 int ARRAY_SIZE (struct audio_clock_info*) ; 
#define  COLOR_DEPTH_121212 129 
#define  COLOR_DEPTH_161616 128 
 struct audio_clock_info* audio_clock_info_table ; 
 struct audio_clock_info* audio_clock_info_table_36bpc ; 
 struct audio_clock_info* audio_clock_info_table_48bpc ; 

void get_audio_clock_info(
	enum dc_color_depth color_depth,
	uint32_t crtc_pixel_clock_100Hz,
	uint32_t actual_pixel_clock_100Hz,
	struct audio_clock_info *audio_clock_info)
{
	const struct audio_clock_info *clock_info;
	uint32_t index;
	uint32_t crtc_pixel_clock_in_10khz = crtc_pixel_clock_100Hz / 100;
	uint32_t audio_array_size;

	switch (color_depth) {
	case COLOR_DEPTH_161616:
		clock_info = audio_clock_info_table_48bpc;
		audio_array_size = ARRAY_SIZE(
				audio_clock_info_table_48bpc);
		break;
	case COLOR_DEPTH_121212:
		clock_info = audio_clock_info_table_36bpc;
		audio_array_size = ARRAY_SIZE(
				audio_clock_info_table_36bpc);
		break;
	default:
		clock_info = audio_clock_info_table;
		audio_array_size = ARRAY_SIZE(
				audio_clock_info_table);
		break;
	}

	if (clock_info != NULL) {
		/* search for exact pixel clock in table */
		for (index = 0; index < audio_array_size; index++) {
			if (clock_info[index].pixel_clock_in_10khz >
				crtc_pixel_clock_in_10khz)
				break;  /* not match */
			else if (clock_info[index].pixel_clock_in_10khz ==
					crtc_pixel_clock_in_10khz) {
				/* match found */
				*audio_clock_info = clock_info[index];
				return;
			}
		}
	}

	/* not found */
	if (actual_pixel_clock_100Hz == 0)
		actual_pixel_clock_100Hz = crtc_pixel_clock_100Hz;

	/* See HDMI spec  the table entry under
	 *  pixel clock of "Other". */
	audio_clock_info->pixel_clock_in_10khz =
			actual_pixel_clock_100Hz / 100;
	audio_clock_info->cts_32khz = actual_pixel_clock_100Hz / 10;
	audio_clock_info->cts_44khz = actual_pixel_clock_100Hz / 10;
	audio_clock_info->cts_48khz = actual_pixel_clock_100Hz / 10;

	audio_clock_info->n_32khz = 4096;
	audio_clock_info->n_44khz = 6272;
	audio_clock_info->n_48khz = 6144;
}