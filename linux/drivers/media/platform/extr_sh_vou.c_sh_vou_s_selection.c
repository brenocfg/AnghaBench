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
struct TYPE_4__ {scalar_t__ code; scalar_t__ width; unsigned int height; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; } ;
struct TYPE_3__ {scalar_t__ width; unsigned int height; } ;
struct v4l2_subdev_selection {scalar_t__ target; TYPE_2__ format; TYPE_1__ r; int /*<<< orphan*/  which; } ;
struct v4l2_subdev_format {scalar_t__ target; TYPE_2__ format; TYPE_1__ r; int /*<<< orphan*/  which; } ;
struct v4l2_rect {scalar_t__ width; unsigned int height; scalar_t__ left; unsigned int top; } ;
struct v4l2_selection {scalar_t__ type; scalar_t__ target; struct v4l2_rect r; } ;
struct v4l2_pix_format {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct sh_vou_geometry {int /*<<< orphan*/  scale_idx_v; int /*<<< orphan*/  scale_idx_h; int /*<<< orphan*/  in_height; int /*<<< orphan*/  in_width; struct v4l2_rect output; } ;
struct sh_vou_device {int std; int /*<<< orphan*/  pix_idx; struct v4l2_rect rect; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  queue; struct v4l2_pix_format pix; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ MEDIA_BUS_FMT_YUYV8_2X8 ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 scalar_t__ V4L2_SEL_TGT_COMPOSE ; 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 scalar_t__ VOU_MAX_IMAGE_WIDTH ; 
 int /*<<< orphan*/  VOU_MIN_IMAGE_HEIGHT ; 
 int /*<<< orphan*/  VOU_MIN_IMAGE_WIDTH ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  set_fmt ; 
 int /*<<< orphan*/  set_selection ; 
 int /*<<< orphan*/  sh_vou_configure_geometry (struct sh_vou_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int v4l2_device_call_until_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_selection*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int,unsigned int*,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct sh_vou_device* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vou_adjust_input (struct sh_vou_geometry*,int) ; 

__attribute__((used)) static int sh_vou_s_selection(struct file *file, void *fh,
			      struct v4l2_selection *sel)
{
	struct v4l2_rect *rect = &sel->r;
	struct sh_vou_device *vou_dev = video_drvdata(file);
	struct v4l2_subdev_selection sd_sel = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.target = V4L2_SEL_TGT_COMPOSE,
	};
	struct v4l2_pix_format *pix = &vou_dev->pix;
	struct sh_vou_geometry geo;
	struct v4l2_subdev_format format = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		/* Revisit: is this the correct code? */
		.format.code = MEDIA_BUS_FMT_YUYV8_2X8,
		.format.field = V4L2_FIELD_INTERLACED,
		.format.colorspace = V4L2_COLORSPACE_SMPTE170M,
	};
	unsigned int img_height_max;
	int ret;

	if (sel->type != V4L2_BUF_TYPE_VIDEO_OUTPUT ||
	    sel->target != V4L2_SEL_TGT_COMPOSE)
		return -EINVAL;

	if (vb2_is_busy(&vou_dev->queue))
		return -EBUSY;

	if (vou_dev->std & V4L2_STD_525_60)
		img_height_max = 480;
	else
		img_height_max = 576;

	v4l_bound_align_image(&rect->width,
			      VOU_MIN_IMAGE_WIDTH, VOU_MAX_IMAGE_WIDTH, 1,
			      &rect->height,
			      VOU_MIN_IMAGE_HEIGHT, img_height_max, 1, 0);

	if (rect->width + rect->left > VOU_MAX_IMAGE_WIDTH)
		rect->left = VOU_MAX_IMAGE_WIDTH - rect->width;

	if (rect->height + rect->top > img_height_max)
		rect->top = img_height_max - rect->height;

	geo.output = *rect;
	geo.in_width = pix->width;
	geo.in_height = pix->height;

	/* Configure the encoder one-to-one, position at 0, ignore errors */
	sd_sel.r.width = geo.output.width;
	sd_sel.r.height = geo.output.height;
	/*
	 * We first issue a S_SELECTION, so that the subsequent S_FMT delivers the
	 * final encoder configuration.
	 */
	v4l2_device_call_until_err(&vou_dev->v4l2_dev, 0, pad,
				   set_selection, NULL, &sd_sel);
	format.format.width = geo.output.width;
	format.format.height = geo.output.height;
	ret = v4l2_device_call_until_err(&vou_dev->v4l2_dev, 0, pad,
					 set_fmt, NULL, &format);
	/* Must be implemented, so, don't check for -ENOIOCTLCMD */
	if (ret < 0)
		return ret;

	/* Sanity checks */
	if ((unsigned)format.format.width > VOU_MAX_IMAGE_WIDTH ||
	    (unsigned)format.format.height > img_height_max ||
	    format.format.code != MEDIA_BUS_FMT_YUYV8_2X8)
		return -EIO;

	geo.output.width = format.format.width;
	geo.output.height = format.format.height;

	/*
	 * No down-scaling. According to the API, current call has precedence:
	 * https://linuxtv.org/downloads/v4l-dvb-apis/uapi/v4l/crop.html#cropping-structures
	 */
	vou_adjust_input(&geo, vou_dev->std);

	/* We tried to preserve output rectangle, but it could have changed */
	vou_dev->rect = geo.output;
	pix->width = geo.in_width;
	pix->height = geo.in_height;

	sh_vou_configure_geometry(vou_dev, vou_dev->pix_idx,
				  geo.scale_idx_h, geo.scale_idx_v);

	return 0;
}