#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vb2_queue {int dummy; } ;
struct v4l2_pix_format {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; scalar_t__ pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  sizeimage; } ;
struct TYPE_4__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {int /*<<< orphan*/  type; TYPE_1__ fmt; } ;
struct file {int /*<<< orphan*/  private_data; } ;
struct delta_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; scalar_t__ streamformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_5__ {int /*<<< orphan*/  m2m_ctx; } ;
struct delta_ctx {int /*<<< orphan*/  flags; TYPE_3__ streaminfo; int /*<<< orphan*/  max_au_size; int /*<<< orphan*/  name; TYPE_2__ fh; struct delta_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELTA_FLAG_STREAMINFO ; 
 int EBUSY ; 
 int delta_try_fmt_stream (struct file*,void*,struct v4l2_format*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 struct delta_ctx* to_ctx (int /*<<< orphan*/ ) ; 
 struct vb2_queue* v4l2_m2m_get_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_streaming (struct vb2_queue*) ; 

__attribute__((used)) static int delta_s_fmt_stream(struct file *file, void *fh,
			      struct v4l2_format *f)
{
	struct delta_ctx *ctx = to_ctx(file->private_data);
	struct delta_dev *delta = ctx->dev;
	struct vb2_queue *vq;
	struct v4l2_pix_format *pix = &f->fmt.pix;
	int ret;

	ret = delta_try_fmt_stream(file, fh, f);
	if (ret) {
		dev_dbg(delta->dev,
			"%s V4L2 S_FMT (OUTPUT): unsupported format %4.4s\n",
			ctx->name, (char *)&pix->pixelformat);
		return ret;
	}

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (vb2_is_streaming(vq)) {
		dev_dbg(delta->dev, "%s V4L2 S_FMT (OUTPUT): queue busy\n",
			ctx->name);
		return -EBUSY;
	}

	ctx->max_au_size = pix->sizeimage;
	ctx->streaminfo.width = pix->width;
	ctx->streaminfo.height = pix->height;
	ctx->streaminfo.streamformat = pix->pixelformat;
	ctx->streaminfo.colorspace = pix->colorspace;
	ctx->streaminfo.xfer_func = pix->xfer_func;
	ctx->streaminfo.ycbcr_enc = pix->ycbcr_enc;
	ctx->streaminfo.quantization = pix->quantization;
	ctx->flags |= DELTA_FLAG_STREAMINFO;

	return 0;
}