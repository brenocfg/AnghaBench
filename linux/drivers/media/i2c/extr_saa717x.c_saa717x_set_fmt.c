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
typedef  int /*<<< orphan*/  u8 ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; int width; int height; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; } ;
struct v4l2_subdev_format {scalar_t__ which; scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MEDIA_BUS_FMT_FIXED ; 
 int SAA717X_NTSC_HEIGHT ; 
 int SAA717X_NTSC_WIDTH ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  saa717x_write (struct v4l2_subdev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_h_prescale (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  set_v_scale (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int saa717x_set_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *fmt = &format->format;
	int prescale, h_scale, v_scale;

	v4l2_dbg(1, debug, sd, "decoder set size\n");

	if (format->pad || fmt->code != MEDIA_BUS_FMT_FIXED)
		return -EINVAL;

	/* FIXME need better bounds checking here */
	if (fmt->width < 1 || fmt->width > 1440)
		return -EINVAL;
	if (fmt->height < 1 || fmt->height > 960)
		return -EINVAL;

	fmt->field = V4L2_FIELD_INTERLACED;
	fmt->colorspace = V4L2_COLORSPACE_SMPTE170M;

	if (format->which == V4L2_SUBDEV_FORMAT_TRY)
		return 0;

	/* scaling setting */
	/* NTSC and interlace only */
	prescale = SAA717X_NTSC_WIDTH / fmt->width;
	if (prescale == 0)
		prescale = 1;
	h_scale = 1024 * SAA717X_NTSC_WIDTH / prescale / fmt->width;
	/* interlace */
	v_scale = 512 * 2 * SAA717X_NTSC_HEIGHT / fmt->height;

	/* Horizontal prescaling etc */
	set_h_prescale(sd, 0, prescale);
	set_h_prescale(sd, 1, prescale);

	/* Horizontal scaling increment */
	/* TASK A */
	saa717x_write(sd, 0x6C, (u8)(h_scale & 0xFF));
	saa717x_write(sd, 0x6D, (u8)((h_scale >> 8) & 0xFF));
	/* TASK B */
	saa717x_write(sd, 0xAC, (u8)(h_scale & 0xFF));
	saa717x_write(sd, 0xAD, (u8)((h_scale >> 8) & 0xFF));

	/* Vertical prescaling etc */
	set_v_scale(sd, 0, v_scale);
	set_v_scale(sd, 1, v_scale);

	/* set video output size */
	/* video number of pixels at output */
	/* TASK A */
	saa717x_write(sd, 0x5C, (u8)(fmt->width & 0xFF));
	saa717x_write(sd, 0x5D, (u8)((fmt->width >> 8) & 0xFF));
	/* TASK B */
	saa717x_write(sd, 0x9C, (u8)(fmt->width & 0xFF));
	saa717x_write(sd, 0x9D, (u8)((fmt->width >> 8) & 0xFF));

	/* video number of lines at output */
	/* TASK A */
	saa717x_write(sd, 0x5E, (u8)(fmt->height & 0xFF));
	saa717x_write(sd, 0x5F, (u8)((fmt->height >> 8) & 0xFF));
	/* TASK B */
	saa717x_write(sd, 0x9E, (u8)(fmt->height & 0xFF));
	saa717x_write(sd, 0x9F, (u8)((fmt->height >> 8) & 0xFF));
	return 0;
}