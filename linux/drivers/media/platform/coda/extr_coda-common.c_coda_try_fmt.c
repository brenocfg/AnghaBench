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
struct TYPE_3__ {int field; int height; int pixelformat; int bytesperline; int sizeimage; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct coda_dev {int dummy; } ;
struct coda_ctx {struct coda_dev* dev; } ;
struct coda_codec {int dummy; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int /*<<< orphan*/  H_ALIGN ; 
 int /*<<< orphan*/  MIN_H ; 
 int /*<<< orphan*/  MIN_W ; 
 int /*<<< orphan*/  S_ALIGN ; 
 int V4L2_FIELD_ANY ; 
 int V4L2_FIELD_NONE ; 
#define  V4L2_PIX_FMT_H264 136 
#define  V4L2_PIX_FMT_JPEG 135 
#define  V4L2_PIX_FMT_MPEG2 134 
#define  V4L2_PIX_FMT_MPEG4 133 
#define  V4L2_PIX_FMT_NV12 132 
#define  V4L2_PIX_FMT_YUV420 131 
#define  V4L2_PIX_FMT_YUV422P 130 
#define  V4L2_PIX_FMT_YUYV 129 
#define  V4L2_PIX_FMT_YVU420 128 
 int /*<<< orphan*/  W_ALIGN ; 
 int coda_estimate_sizeimage (struct coda_ctx*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  coda_get_max_dimensions (struct coda_dev*,struct coda_codec const*,unsigned int*,unsigned int*) ; 
 int round_up (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int coda_try_fmt(struct coda_ctx *ctx, const struct coda_codec *codec,
			struct v4l2_format *f)
{
	struct coda_dev *dev = ctx->dev;
	unsigned int max_w, max_h;
	enum v4l2_field field;

	field = f->fmt.pix.field;
	if (field == V4L2_FIELD_ANY)
		field = V4L2_FIELD_NONE;
	else if (V4L2_FIELD_NONE != field)
		return -EINVAL;

	/* V4L2 specification suggests the driver corrects the format struct
	 * if any of the dimensions is unsupported */
	f->fmt.pix.field = field;

	coda_get_max_dimensions(dev, codec, &max_w, &max_h);
	v4l_bound_align_image(&f->fmt.pix.width, MIN_W, max_w, W_ALIGN,
			      &f->fmt.pix.height, MIN_H, max_h, H_ALIGN,
			      S_ALIGN);

	switch (f->fmt.pix.pixelformat) {
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_YUV420:
	case V4L2_PIX_FMT_YVU420:
		/*
		 * Frame stride must be at least multiple of 8,
		 * but multiple of 16 for h.264 or JPEG 4:2:x
		 */
		f->fmt.pix.bytesperline = round_up(f->fmt.pix.width, 16);
		f->fmt.pix.sizeimage = f->fmt.pix.bytesperline *
					f->fmt.pix.height * 3 / 2;
		break;
	case V4L2_PIX_FMT_YUYV:
		f->fmt.pix.bytesperline = round_up(f->fmt.pix.width, 16) * 2;
		f->fmt.pix.sizeimage = f->fmt.pix.bytesperline *
					f->fmt.pix.height;
		break;
	case V4L2_PIX_FMT_YUV422P:
		f->fmt.pix.bytesperline = round_up(f->fmt.pix.width, 16);
		f->fmt.pix.sizeimage = f->fmt.pix.bytesperline *
					f->fmt.pix.height * 2;
		break;
	case V4L2_PIX_FMT_JPEG:
	case V4L2_PIX_FMT_H264:
	case V4L2_PIX_FMT_MPEG4:
	case V4L2_PIX_FMT_MPEG2:
		f->fmt.pix.bytesperline = 0;
		f->fmt.pix.sizeimage = coda_estimate_sizeimage(ctx,
							f->fmt.pix.sizeimage,
							f->fmt.pix.width,
							f->fmt.pix.height);
		break;
	default:
		BUG();
	}

	return 0;
}