#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int width; int height; int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {TYPE_4__ format; int /*<<< orphan*/  which; } ;
struct TYPE_6__ {int width; int height; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  sizeimage; scalar_t__ bytesperline; int /*<<< orphan*/  field; } ;
struct TYPE_7__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; int /*<<< orphan*/  type; } ;
struct go7007 {int width; int height; int encoder_h_halve; int encoder_v_halve; int encoder_subsample; int /*<<< orphan*/  v4l2_dev; TYPE_1__* board_info; int /*<<< orphan*/  encoder_v_offset; int /*<<< orphan*/  encoder_h_offset; int /*<<< orphan*/  format; } ;
struct TYPE_5__ {int sensor_flags; int /*<<< orphan*/  sensor_v_offset; int /*<<< orphan*/  sensor_h_offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GO7007_BUF_SIZE ; 
 int GO7007_SENSOR_SCALING ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_FIXED ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 
 int /*<<< orphan*/  get_resolution (struct go7007*,int*,int*) ; 
 int /*<<< orphan*/  memset (struct v4l2_format*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  set_fmt ; 
 int /*<<< orphan*/  valid_pixelformat (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_capture_size(struct go7007 *go, struct v4l2_format *fmt, int try)
{
	int sensor_height = 0, sensor_width = 0;
	int width, height;

	if (fmt != NULL && !valid_pixelformat(fmt->fmt.pix.pixelformat))
		return -EINVAL;

	get_resolution(go, &sensor_width, &sensor_height);

	if (fmt == NULL) {
		width = sensor_width;
		height = sensor_height;
	} else if (go->board_info->sensor_flags & GO7007_SENSOR_SCALING) {
		if (fmt->fmt.pix.width > sensor_width)
			width = sensor_width;
		else if (fmt->fmt.pix.width < 144)
			width = 144;
		else
			width = fmt->fmt.pix.width & ~0x0f;

		if (fmt->fmt.pix.height > sensor_height)
			height = sensor_height;
		else if (fmt->fmt.pix.height < 96)
			height = 96;
		else
			height = fmt->fmt.pix.height & ~0x0f;
	} else {
		width = fmt->fmt.pix.width;

		if (width <= sensor_width / 4) {
			width = sensor_width / 4;
			height = sensor_height / 4;
		} else if (width <= sensor_width / 2) {
			width = sensor_width / 2;
			height = sensor_height / 2;
		} else {
			width = sensor_width;
			height = sensor_height;
		}
		width &= ~0xf;
		height &= ~0xf;
	}

	if (fmt != NULL) {
		u32 pixelformat = fmt->fmt.pix.pixelformat;

		memset(fmt, 0, sizeof(*fmt));
		fmt->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		fmt->fmt.pix.width = width;
		fmt->fmt.pix.height = height;
		fmt->fmt.pix.pixelformat = pixelformat;
		fmt->fmt.pix.field = V4L2_FIELD_NONE;
		fmt->fmt.pix.bytesperline = 0;
		fmt->fmt.pix.sizeimage = GO7007_BUF_SIZE;
		fmt->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	}

	if (try)
		return 0;

	if (fmt)
		go->format = fmt->fmt.pix.pixelformat;
	go->width = width;
	go->height = height;
	go->encoder_h_offset = go->board_info->sensor_h_offset;
	go->encoder_v_offset = go->board_info->sensor_v_offset;

	if (go->board_info->sensor_flags & GO7007_SENSOR_SCALING) {
		struct v4l2_subdev_format format = {
			.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		};

		format.format.code = MEDIA_BUS_FMT_FIXED;
		format.format.width = fmt ? fmt->fmt.pix.width : width;
		format.format.height = height;
		go->encoder_h_halve = 0;
		go->encoder_v_halve = 0;
		go->encoder_subsample = 0;
		call_all(&go->v4l2_dev, pad, set_fmt, NULL, &format);
	} else {
		if (width <= sensor_width / 4) {
			go->encoder_h_halve = 1;
			go->encoder_v_halve = 1;
			go->encoder_subsample = 1;
		} else if (width <= sensor_width / 2) {
			go->encoder_h_halve = 1;
			go->encoder_v_halve = 1;
			go->encoder_subsample = 0;
		} else {
			go->encoder_h_halve = 0;
			go->encoder_v_halve = 0;
			go->encoder_subsample = 0;
		}
	}
	return 0;
}