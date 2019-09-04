#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pixel_encoding; int display_color_depth; } ;
struct dc_stream_state {int dither_option; TYPE_1__ timing; } ;
struct TYPE_4__ {int TRUNCATE_ENABLED; int TRUNCATE_DEPTH; int TRUNCATE_MODE; int SPATIAL_DITHER_ENABLED; int SPATIAL_DITHER_DEPTH; int HIGHPASS_RANDOM; int RGB_RANDOM; int FRAME_RANDOM; int FRAME_MODULATION_ENABLED; int FRAME_MODULATION_DEPTH; } ;
struct bit_depth_reduction_params {int pixel_encoding; TYPE_2__ flags; } ;
typedef  enum dc_pixel_encoding { ____Placeholder_dc_pixel_encoding } dc_pixel_encoding ;
typedef  enum dc_dither_option { ____Placeholder_dc_dither_option } dc_dither_option ;

/* Variables and functions */
#define  COLOR_DEPTH_101010 130 
#define  COLOR_DEPTH_666 129 
#define  COLOR_DEPTH_888 128 
 int DITHER_OPTION_DEFAULT ; 
 int DITHER_OPTION_DISABLE ; 
 int DITHER_OPTION_FM10 ; 
 int DITHER_OPTION_FM6 ; 
 int DITHER_OPTION_FM8 ; 
 int DITHER_OPTION_SPATIAL10 ; 
 int DITHER_OPTION_SPATIAL10_FM6 ; 
 int DITHER_OPTION_SPATIAL10_FM8 ; 
 int DITHER_OPTION_SPATIAL10_FRAME_RANDOM ; 
 int DITHER_OPTION_SPATIAL6 ; 
 int DITHER_OPTION_SPATIAL6_FRAME_RANDOM ; 
 int DITHER_OPTION_SPATIAL8 ; 
 int DITHER_OPTION_SPATIAL8_FM6 ; 
 int DITHER_OPTION_SPATIAL8_FRAME_RANDOM ; 
 int DITHER_OPTION_TRUN10 ; 
 int DITHER_OPTION_TRUN10_FM6 ; 
 int DITHER_OPTION_TRUN10_FM8 ; 
 int DITHER_OPTION_TRUN10_SPATIAL6 ; 
 int DITHER_OPTION_TRUN10_SPATIAL8 ; 
 int DITHER_OPTION_TRUN10_SPATIAL8_FM6 ; 
 int DITHER_OPTION_TRUN6 ; 
 int DITHER_OPTION_TRUN8 ; 
 int DITHER_OPTION_TRUN8_FM6 ; 
 int DITHER_OPTION_TRUN8_SPATIAL6 ; 
 int PIXEL_ENCODING_RGB ; 
 int /*<<< orphan*/  memset (struct bit_depth_reduction_params*,int /*<<< orphan*/ ,int) ; 

void resource_build_bit_depth_reduction_params(struct dc_stream_state *stream,
		struct bit_depth_reduction_params *fmt_bit_depth)
{
	enum dc_dither_option option = stream->dither_option;
	enum dc_pixel_encoding pixel_encoding =
			stream->timing.pixel_encoding;

	memset(fmt_bit_depth, 0, sizeof(*fmt_bit_depth));

	if (option == DITHER_OPTION_DEFAULT) {
		switch (stream->timing.display_color_depth) {
		case COLOR_DEPTH_666:
			option = DITHER_OPTION_SPATIAL6;
			break;
		case COLOR_DEPTH_888:
			option = DITHER_OPTION_SPATIAL8;
			break;
		case COLOR_DEPTH_101010:
			option = DITHER_OPTION_SPATIAL10;
			break;
		default:
			option = DITHER_OPTION_DISABLE;
		}
	}

	if (option == DITHER_OPTION_DISABLE)
		return;

	if (option == DITHER_OPTION_TRUN6) {
		fmt_bit_depth->flags.TRUNCATE_ENABLED = 1;
		fmt_bit_depth->flags.TRUNCATE_DEPTH = 0;
	} else if (option == DITHER_OPTION_TRUN8 ||
			option == DITHER_OPTION_TRUN8_SPATIAL6 ||
			option == DITHER_OPTION_TRUN8_FM6) {
		fmt_bit_depth->flags.TRUNCATE_ENABLED = 1;
		fmt_bit_depth->flags.TRUNCATE_DEPTH = 1;
	} else if (option == DITHER_OPTION_TRUN10        ||
			option == DITHER_OPTION_TRUN10_SPATIAL6   ||
			option == DITHER_OPTION_TRUN10_SPATIAL8   ||
			option == DITHER_OPTION_TRUN10_FM8     ||
			option == DITHER_OPTION_TRUN10_FM6     ||
			option == DITHER_OPTION_TRUN10_SPATIAL8_FM6) {
		fmt_bit_depth->flags.TRUNCATE_ENABLED = 1;
		fmt_bit_depth->flags.TRUNCATE_DEPTH = 2;
	}

	/* special case - Formatter can only reduce by 4 bits at most.
	 * When reducing from 12 to 6 bits,
	 * HW recommends we use trunc with round mode
	 * (if we did nothing, trunc to 10 bits would be used)
	 * note that any 12->10 bit reduction is ignored prior to DCE8,
	 * as the input was 10 bits.
	 */
	if (option == DITHER_OPTION_SPATIAL6_FRAME_RANDOM ||
			option == DITHER_OPTION_SPATIAL6 ||
			option == DITHER_OPTION_FM6) {
		fmt_bit_depth->flags.TRUNCATE_ENABLED = 1;
		fmt_bit_depth->flags.TRUNCATE_DEPTH = 2;
		fmt_bit_depth->flags.TRUNCATE_MODE = 1;
	}

	/* spatial dither
	 * note that spatial modes 1-3 are never used
	 */
	if (option == DITHER_OPTION_SPATIAL6_FRAME_RANDOM            ||
			option == DITHER_OPTION_SPATIAL6 ||
			option == DITHER_OPTION_TRUN10_SPATIAL6      ||
			option == DITHER_OPTION_TRUN8_SPATIAL6) {
		fmt_bit_depth->flags.SPATIAL_DITHER_ENABLED = 1;
		fmt_bit_depth->flags.SPATIAL_DITHER_DEPTH = 0;
		fmt_bit_depth->flags.HIGHPASS_RANDOM = 1;
		fmt_bit_depth->flags.RGB_RANDOM =
				(pixel_encoding == PIXEL_ENCODING_RGB) ? 1 : 0;
	} else if (option == DITHER_OPTION_SPATIAL8_FRAME_RANDOM            ||
			option == DITHER_OPTION_SPATIAL8 ||
			option == DITHER_OPTION_SPATIAL8_FM6        ||
			option == DITHER_OPTION_TRUN10_SPATIAL8      ||
			option == DITHER_OPTION_TRUN10_SPATIAL8_FM6) {
		fmt_bit_depth->flags.SPATIAL_DITHER_ENABLED = 1;
		fmt_bit_depth->flags.SPATIAL_DITHER_DEPTH = 1;
		fmt_bit_depth->flags.HIGHPASS_RANDOM = 1;
		fmt_bit_depth->flags.RGB_RANDOM =
				(pixel_encoding == PIXEL_ENCODING_RGB) ? 1 : 0;
	} else if (option == DITHER_OPTION_SPATIAL10_FRAME_RANDOM ||
			option == DITHER_OPTION_SPATIAL10 ||
			option == DITHER_OPTION_SPATIAL10_FM8 ||
			option == DITHER_OPTION_SPATIAL10_FM6) {
		fmt_bit_depth->flags.SPATIAL_DITHER_ENABLED = 1;
		fmt_bit_depth->flags.SPATIAL_DITHER_DEPTH = 2;
		fmt_bit_depth->flags.HIGHPASS_RANDOM = 1;
		fmt_bit_depth->flags.RGB_RANDOM =
				(pixel_encoding == PIXEL_ENCODING_RGB) ? 1 : 0;
	}

	if (option == DITHER_OPTION_SPATIAL6 ||
			option == DITHER_OPTION_SPATIAL8 ||
			option == DITHER_OPTION_SPATIAL10) {
		fmt_bit_depth->flags.FRAME_RANDOM = 0;
	} else {
		fmt_bit_depth->flags.FRAME_RANDOM = 1;
	}

	//////////////////////
	//// temporal dither
	//////////////////////
	if (option == DITHER_OPTION_FM6           ||
			option == DITHER_OPTION_SPATIAL8_FM6     ||
			option == DITHER_OPTION_SPATIAL10_FM6     ||
			option == DITHER_OPTION_TRUN10_FM6     ||
			option == DITHER_OPTION_TRUN8_FM6      ||
			option == DITHER_OPTION_TRUN10_SPATIAL8_FM6) {
		fmt_bit_depth->flags.FRAME_MODULATION_ENABLED = 1;
		fmt_bit_depth->flags.FRAME_MODULATION_DEPTH = 0;
	} else if (option == DITHER_OPTION_FM8        ||
			option == DITHER_OPTION_SPATIAL10_FM8  ||
			option == DITHER_OPTION_TRUN10_FM8) {
		fmt_bit_depth->flags.FRAME_MODULATION_ENABLED = 1;
		fmt_bit_depth->flags.FRAME_MODULATION_DEPTH = 1;
	} else if (option == DITHER_OPTION_FM10) {
		fmt_bit_depth->flags.FRAME_MODULATION_ENABLED = 1;
		fmt_bit_depth->flags.FRAME_MODULATION_DEPTH = 2;
	}

	fmt_bit_depth->pixel_encoding = pixel_encoding;
}