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
typedef  scalar_t__ u32 ;
struct v4l2_pix_format {scalar_t__ pixelformat; scalar_t__ width; scalar_t__ height; scalar_t__ sizeimage; int /*<<< orphan*/  field; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; scalar_t__ bytesperline; } ;
struct TYPE_3__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct hva_enc {int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; } ;
struct TYPE_4__ {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  pixelformat; } ;
struct hva_ctx {int flags; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  name; TYPE_2__ frameinfo; } ;
struct file {int /*<<< orphan*/  private_data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int HVA_FLAG_FRAMEINFO ; 
 int /*<<< orphan*/  HVA_MIN_HEIGHT ; 
 int /*<<< orphan*/  HVA_MIN_WIDTH ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct device* ctx_to_dev (struct hva_ctx*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 scalar_t__ estimated_stream_size (scalar_t__,scalar_t__) ; 
 struct hva_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 struct hva_enc* hva_find_encoder (struct hva_ctx*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  v4l_bound_align_image (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hva_try_fmt_stream(struct file *file, void *priv,
			      struct v4l2_format *f)
{
	struct hva_ctx *ctx = fh_to_ctx(file->private_data);
	struct device *dev = ctx_to_dev(ctx);
	struct v4l2_pix_format *pix = &f->fmt.pix;
	u32 streamformat = pix->pixelformat;
	const struct hva_enc *enc;
	u32 width, height;
	u32 stream_size;

	enc = hva_find_encoder(ctx, ctx->frameinfo.pixelformat, streamformat);
	if (!enc) {
		dev_dbg(dev,
			"%s V4L2 TRY_FMT (CAPTURE): unsupported format %.4s\n",
			ctx->name, (char *)&pix->pixelformat);
		return -EINVAL;
	}

	width = pix->width;
	height = pix->height;
	if (ctx->flags & HVA_FLAG_FRAMEINFO) {
		/*
		 * if the frame resolution is already fixed, only allow the
		 * same stream resolution
		 */
		pix->width = ctx->frameinfo.width;
		pix->height = ctx->frameinfo.height;
		if ((pix->width != width) || (pix->height != height))
			dev_dbg(dev,
				"%s V4L2 TRY_FMT (CAPTURE): resolution updated %dx%d -> %dx%d to fit frame resolution\n",
				ctx->name, width, height,
				pix->width, pix->height);
	} else {
		/* adjust width & height */
		v4l_bound_align_image(&pix->width,
				      HVA_MIN_WIDTH, enc->max_width,
				      0,
				      &pix->height,
				      HVA_MIN_HEIGHT, enc->max_height,
				      0,
				      0);

		if ((pix->width != width) || (pix->height != height))
			dev_dbg(dev,
				"%s V4L2 TRY_FMT (CAPTURE): resolution updated %dx%d -> %dx%d to fit min/max/alignment\n",
				ctx->name, width, height,
				pix->width, pix->height);
	}

	stream_size = estimated_stream_size(pix->width, pix->height);
	if (pix->sizeimage < stream_size)
		pix->sizeimage = stream_size;

	pix->bytesperline = 0;
	pix->colorspace = ctx->colorspace;
	pix->xfer_func = ctx->xfer_func;
	pix->ycbcr_enc = ctx->ycbcr_enc;
	pix->quantization = ctx->quantization;
	pix->field = V4L2_FIELD_NONE;

	return 0;
}