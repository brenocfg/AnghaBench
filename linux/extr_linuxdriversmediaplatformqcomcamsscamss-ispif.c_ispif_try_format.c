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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {void* colorspace; int /*<<< orphan*/  field; void* height; void* width; int /*<<< orphan*/  code; } ;
struct ispif_line {unsigned int nformats; int /*<<< orphan*/ * formats; } ;
typedef  enum v4l2_subdev_format_whence { ____Placeholder_v4l2_subdev_format_whence } v4l2_subdev_format_whence ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_BUS_FMT_UYVY8_2X8 ; 
#define  MSM_ISPIF_PAD_SINK 129 
#define  MSM_ISPIF_PAD_SRC 128 
 void* V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct v4l2_mbus_framefmt* __ispif_get_format (struct ispif_line*,struct v4l2_subdev_pad_config*,int const,int) ; 
 void* clamp_t (int /*<<< orphan*/ ,void*,int,int) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static void ispif_try_format(struct ispif_line *line,
			     struct v4l2_subdev_pad_config *cfg,
			     unsigned int pad,
			     struct v4l2_mbus_framefmt *fmt,
			     enum v4l2_subdev_format_whence which)
{
	unsigned int i;

	switch (pad) {
	case MSM_ISPIF_PAD_SINK:
		/* Set format on sink pad */

		for (i = 0; i < line->nformats; i++)
			if (fmt->code == line->formats[i])
				break;

		/* If not found, use UYVY as default */
		if (i >= line->nformats)
			fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;

		fmt->width = clamp_t(u32, fmt->width, 1, 8191);
		fmt->height = clamp_t(u32, fmt->height, 1, 8191);

		fmt->field = V4L2_FIELD_NONE;
		fmt->colorspace = V4L2_COLORSPACE_SRGB;

		break;

	case MSM_ISPIF_PAD_SRC:
		/* Set and return a format same as sink pad */

		*fmt = *__ispif_get_format(line, cfg, MSM_ISPIF_PAD_SINK,
					   which);

		break;
	}

	fmt->colorspace = V4L2_COLORSPACE_SRGB;
}