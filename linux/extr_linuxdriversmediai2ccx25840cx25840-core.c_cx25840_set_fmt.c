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
struct v4l2_mbus_framefmt {scalar_t__ code; int height; int width; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; } ;
struct v4l2_subdev_format {scalar_t__ which; scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;
struct cx25840_state {int std; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 scalar_t__ MEDIA_BUS_FMT_FIXED ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int V4L2_STD_525_60 ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  cx25840_debug ; 
 int cx25840_read (struct i2c_client*,int) ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  cx25840_write4 (struct i2c_client*,int,int) ; 
 scalar_t__ is_cx23888 (struct cx25840_state*) ; 
 struct cx25840_state* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  v4l_err (struct i2c_client*,char*,int,int) ; 

__attribute__((used)) static int cx25840_set_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *fmt = &format->format;
	struct cx25840_state *state = to_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int HSC, VSC, Vsrc, Hsrc, filter, Vlines;
	int is_50Hz = !(state->std & V4L2_STD_525_60);

	if (format->pad || fmt->code != MEDIA_BUS_FMT_FIXED)
		return -EINVAL;

	fmt->field = V4L2_FIELD_INTERLACED;
	fmt->colorspace = V4L2_COLORSPACE_SMPTE170M;

	if (is_cx23888(state)) {
		Vsrc = (cx25840_read(client, 0x42a) & 0x3f) << 4;
		Vsrc |= (cx25840_read(client, 0x429) & 0xf0) >> 4;
	} else {
		Vsrc = (cx25840_read(client, 0x476) & 0x3f) << 4;
		Vsrc |= (cx25840_read(client, 0x475) & 0xf0) >> 4;
	}

	if (is_cx23888(state)) {
		Hsrc = (cx25840_read(client, 0x426) & 0x3f) << 4;
		Hsrc |= (cx25840_read(client, 0x425) & 0xf0) >> 4;
	} else {
		Hsrc = (cx25840_read(client, 0x472) & 0x3f) << 4;
		Hsrc |= (cx25840_read(client, 0x471) & 0xf0) >> 4;
	}

	Vlines = fmt->height + (is_50Hz ? 4 : 7);

	/*
	 * We keep 1 margin for the Vsrc < Vlines check since the
	 * cx23888 reports a Vsrc of 486 instead of 487 for the NTSC
	 * height. Without that margin the cx23885 fails in this
	 * check.
	 */
	if ((fmt->width == 0) || (Vlines == 0) ||
	    (fmt->width * 16 < Hsrc) || (Hsrc < fmt->width) ||
	    (Vlines * 8 < Vsrc) || (Vsrc + 1 < Vlines)) {
		v4l_err(client, "%dx%d is not a valid size!\n",
				fmt->width, fmt->height);
		return -ERANGE;
	}
	if (format->which == V4L2_SUBDEV_FORMAT_TRY)
		return 0;

	HSC = (Hsrc * (1 << 20)) / fmt->width - (1 << 20);
	VSC = (1 << 16) - (Vsrc * (1 << 9) / Vlines - (1 << 9));
	VSC &= 0x1fff;

	if (fmt->width >= 385)
		filter = 0;
	else if (fmt->width > 192)
		filter = 1;
	else if (fmt->width > 96)
		filter = 2;
	else
		filter = 3;

	v4l_dbg(1, cx25840_debug, client, "decoder set size %dx%d -> scale  %ux%u\n",
			fmt->width, fmt->height, HSC, VSC);

	/* HSCALE=HSC */
	if (is_cx23888(state)) {
		cx25840_write4(client, 0x434, HSC | (1 << 24));
		/* VSCALE=VSC VS_INTRLACE=1 VFILT=filter */
		cx25840_write4(client, 0x438, VSC | (1 << 19) | (filter << 16));
	} else {
		cx25840_write(client, 0x418, HSC & 0xff);
		cx25840_write(client, 0x419, (HSC >> 8) & 0xff);
		cx25840_write(client, 0x41a, HSC >> 16);
		/* VSCALE=VSC */
		cx25840_write(client, 0x41c, VSC & 0xff);
		cx25840_write(client, 0x41d, VSC >> 8);
		/* VS_INTRLACE=1 VFILT=filter */
		cx25840_write(client, 0x41e, 0x8 | filter);
	}
	return 0;
}