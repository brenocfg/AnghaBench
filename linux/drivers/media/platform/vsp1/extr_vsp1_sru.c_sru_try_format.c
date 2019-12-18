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
struct vsp1_sru {int /*<<< orphan*/  entity; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {unsigned int width; unsigned int height; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_BUS_FMT_ARGB8888_1X32 ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_AYUV8_1X32 ; 
 int SRU_MAX_SIZE ; 
 int /*<<< orphan*/  SRU_MIN_SIZE ; 
#define  SRU_PAD_SINK 129 
#define  SRU_PAD_SOURCE 128 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 void* clamp (unsigned int,int /*<<< orphan*/ ,int) ; 
 unsigned int min (unsigned int,int) ; 
 struct v4l2_mbus_framefmt* vsp1_entity_get_pad_format (int /*<<< orphan*/ *,struct v4l2_subdev_pad_config*,int const) ; 

__attribute__((used)) static void sru_try_format(struct vsp1_sru *sru,
			   struct v4l2_subdev_pad_config *config,
			   unsigned int pad, struct v4l2_mbus_framefmt *fmt)
{
	struct v4l2_mbus_framefmt *format;
	unsigned int input_area;
	unsigned int output_area;

	switch (pad) {
	case SRU_PAD_SINK:
		/* Default to YUV if the requested format is not supported. */
		if (fmt->code != MEDIA_BUS_FMT_ARGB8888_1X32 &&
		    fmt->code != MEDIA_BUS_FMT_AYUV8_1X32)
			fmt->code = MEDIA_BUS_FMT_AYUV8_1X32;

		fmt->width = clamp(fmt->width, SRU_MIN_SIZE, SRU_MAX_SIZE);
		fmt->height = clamp(fmt->height, SRU_MIN_SIZE, SRU_MAX_SIZE);
		break;

	case SRU_PAD_SOURCE:
		/* The SRU can't perform format conversion. */
		format = vsp1_entity_get_pad_format(&sru->entity, config,
						    SRU_PAD_SINK);
		fmt->code = format->code;

		/*
		 * We can upscale by 2 in both direction, but not independently.
		 * Compare the input and output rectangles areas (avoiding
		 * integer overflows on the output): if the requested output
		 * area is larger than 1.5^2 the input area upscale by two,
		 * otherwise don't scale.
		 */
		input_area = format->width * format->height;
		output_area = min(fmt->width, SRU_MAX_SIZE)
			    * min(fmt->height, SRU_MAX_SIZE);

		if (fmt->width <= SRU_MAX_SIZE / 2 &&
		    fmt->height <= SRU_MAX_SIZE / 2 &&
		    output_area > input_area * 9 / 4) {
			fmt->width = format->width * 2;
			fmt->height = format->height * 2;
		} else {
			fmt->width = format->width;
			fmt->height = format->height;
		}
		break;
	}

	fmt->field = V4L2_FIELD_NONE;
	fmt->colorspace = V4L2_COLORSPACE_SRGB;
}