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
typedef  int u32 ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; int width; int height; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; } ;
struct v4l2_subdev_format {scalar_t__ which; scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;
struct cx25840_state {int std; int /*<<< orphan*/  generic_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MEDIA_BUS_FMT_FIXED ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int V4L2_STD_525_60 ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 void* clamp (int,int,int) ; 
 int /*<<< orphan*/  cx25840_debug ; 
 int cx25840_read (struct i2c_client*,int) ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  cx25840_write4 (struct i2c_client*,int,int) ; 
 scalar_t__ is_cx23888 (struct cx25840_state*) ; 
 struct cx25840_state* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  v4l_err (struct i2c_client*,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int cx25840_set_fmt(struct v4l2_subdev *sd,
			   struct v4l2_subdev_pad_config *cfg,
			   struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *fmt = &format->format;
	struct cx25840_state *state = to_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	u32 hsc, vsc, v_src, h_src, v_add;
	int filter;
	int is_50hz = !(state->std & V4L2_STD_525_60);

	if (format->pad || fmt->code != MEDIA_BUS_FMT_FIXED)
		return -EINVAL;

	fmt->field = V4L2_FIELD_INTERLACED;
	fmt->colorspace = V4L2_COLORSPACE_SMPTE170M;

	if (is_cx23888(state)) {
		v_src = (cx25840_read(client, 0x42a) & 0x3f) << 4;
		v_src |= (cx25840_read(client, 0x429) & 0xf0) >> 4;
	} else {
		v_src = (cx25840_read(client, 0x476) & 0x3f) << 4;
		v_src |= (cx25840_read(client, 0x475) & 0xf0) >> 4;
	}

	if (is_cx23888(state)) {
		h_src = (cx25840_read(client, 0x426) & 0x3f) << 4;
		h_src |= (cx25840_read(client, 0x425) & 0xf0) >> 4;
	} else {
		h_src = (cx25840_read(client, 0x472) & 0x3f) << 4;
		h_src |= (cx25840_read(client, 0x471) & 0xf0) >> 4;
	}

	if (!state->generic_mode) {
		v_add = is_50hz ? 4 : 7;

		/*
		 * cx23888 in 525-line mode is programmed for 486 active lines
		 * while other chips use 487 active lines.
		 *
		 * See reg 0x428 bits [21:12] in cx23888_std_setup() vs
		 * vactive in cx25840_std_setup().
		 */
		if (is_cx23888(state) && !is_50hz)
			v_add--;
	} else {
		v_add = 0;
	}

	if (h_src == 0 ||
	    v_src <= v_add) {
		v4l_err(client,
			"chip reported picture size (%u x %u) is far too small\n",
			(unsigned int)h_src, (unsigned int)v_src);
		/*
		 * that's the best we can do since the output picture
		 * size is completely unknown in this case
		 */
		return -EINVAL;
	}

	fmt->width = clamp(fmt->width, (h_src + 15) / 16, h_src);

	if (v_add * 8 >= v_src)
		fmt->height = clamp(fmt->height, (u32)1, v_src - v_add);
	else
		fmt->height = clamp(fmt->height, (v_src - v_add * 8 + 7) / 8,
				    v_src - v_add);

	if (format->which == V4L2_SUBDEV_FORMAT_TRY)
		return 0;

	hsc = (h_src * (1 << 20)) / fmt->width - (1 << 20);
	vsc = (1 << 16) - (v_src * (1 << 9) / (fmt->height + v_add) - (1 << 9));
	vsc &= 0x1fff;

	if (fmt->width >= 385)
		filter = 0;
	else if (fmt->width > 192)
		filter = 1;
	else if (fmt->width > 96)
		filter = 2;
	else
		filter = 3;

	v4l_dbg(1, cx25840_debug, client,
		"decoder set size %u x %u with scale %x x %x\n",
		(unsigned int)fmt->width, (unsigned int)fmt->height,
		(unsigned int)hsc, (unsigned int)vsc);

	/* HSCALE=hsc */
	if (is_cx23888(state)) {
		cx25840_write4(client, 0x434, hsc | (1 << 24));
		/* VSCALE=vsc VS_INTRLACE=1 VFILT=filter */
		cx25840_write4(client, 0x438, vsc | (1 << 19) | (filter << 16));
	} else {
		cx25840_write(client, 0x418, hsc & 0xff);
		cx25840_write(client, 0x419, (hsc >> 8) & 0xff);
		cx25840_write(client, 0x41a, hsc >> 16);
		/* VSCALE=vsc */
		cx25840_write(client, 0x41c, vsc & 0xff);
		cx25840_write(client, 0x41d, vsc >> 8);
		/* VS_INTRLACE=1 VFILT=filter */
		cx25840_write(client, 0x41e, 0x8 | filter);
	}
	return 0;
}