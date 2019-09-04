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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int field; } ;
struct v4l2_subdev_format {struct v4l2_mbus_framefmt format; int /*<<< orphan*/  which; } ;
struct v4l2_pix_format {scalar_t__ pixelformat; int field; int bytesperline; int sizeimage; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct pxa_camera_format_xlate {int /*<<< orphan*/  host_fmt; int /*<<< orphan*/  code; } ;
struct pxa_camera_dev {int /*<<< orphan*/  user_formats; } ;
struct file {int dummy; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_FIELD_ANY 129 
#define  V4L2_FIELD_NONE 128 
 scalar_t__ V4L2_PIX_FMT_YUV422P ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  pcdev_to_dev (struct pxa_camera_dev*) ; 
 int pxa_mbus_bytes_per_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pxa_mbus_image_size (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct pxa_camera_format_xlate* pxa_mbus_xlate_by_fourcc (int /*<<< orphan*/ ,scalar_t__) ; 
 int sensor_call (struct pxa_camera_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*) ; 
 int /*<<< orphan*/  set_fmt ; 
 int /*<<< orphan*/  v4l2_fill_mbus_format (struct v4l2_mbus_framefmt*,struct v4l2_pix_format*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fill_pix_format (struct v4l2_pix_format*,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int) ; 
 struct pxa_camera_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int pxac_vidioc_try_fmt_vid_cap(struct file *filp, void *priv,
				      struct v4l2_format *f)
{
	struct pxa_camera_dev *pcdev = video_drvdata(filp);
	const struct pxa_camera_format_xlate *xlate;
	struct v4l2_pix_format *pix = &f->fmt.pix;
	struct v4l2_subdev_pad_config pad_cfg;
	struct v4l2_subdev_format format = {
		.which = V4L2_SUBDEV_FORMAT_TRY,
	};
	struct v4l2_mbus_framefmt *mf = &format.format;
	__u32 pixfmt = pix->pixelformat;
	int ret;

	xlate = pxa_mbus_xlate_by_fourcc(pcdev->user_formats, pixfmt);
	if (!xlate) {
		dev_warn(pcdev_to_dev(pcdev), "Format %x not found\n", pixfmt);
		return -EINVAL;
	}

	/*
	 * Limit to pxa hardware capabilities.  YUV422P planar format requires
	 * images size to be a multiple of 16 bytes.  If not, zeros will be
	 * inserted between Y and U planes, and U and V planes, which violates
	 * the YUV422P standard.
	 */
	v4l_bound_align_image(&pix->width, 48, 2048, 1,
			      &pix->height, 32, 2048, 0,
			      pixfmt == V4L2_PIX_FMT_YUV422P ? 4 : 0);

	v4l2_fill_mbus_format(mf, pix, xlate->code);
	ret = sensor_call(pcdev, pad, set_fmt, &pad_cfg, &format);
	if (ret < 0)
		return ret;

	v4l2_fill_pix_format(pix, mf);

	/* Only progressive video supported so far */
	switch (mf->field) {
	case V4L2_FIELD_ANY:
	case V4L2_FIELD_NONE:
		pix->field = V4L2_FIELD_NONE;
		break;
	default:
		/* TODO: support interlaced at least in pass-through mode */
		dev_err(pcdev_to_dev(pcdev), "Field type %d unsupported.\n",
			mf->field);
		return -EINVAL;
	}

	ret = pxa_mbus_bytes_per_line(pix->width, xlate->host_fmt);
	if (ret < 0)
		return ret;

	pix->bytesperline = ret;
	ret = pxa_mbus_image_size(xlate->host_fmt, pix->bytesperline,
				  pix->height);
	if (ret < 0)
		return ret;

	pix->sizeimage = ret;
	return 0;
}