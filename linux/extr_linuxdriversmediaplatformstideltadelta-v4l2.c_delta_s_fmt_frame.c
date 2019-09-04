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
struct vb2_queue {int dummy; } ;
struct v4l2_pix_format {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  sizeimage; scalar_t__ pixelformat; int /*<<< orphan*/  width; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  height; } ;
struct TYPE_3__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {int /*<<< orphan*/  type; TYPE_1__ fmt; } ;
struct file {int /*<<< orphan*/  private_data; } ;
struct delta_frameinfo {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  size; int /*<<< orphan*/  aligned_height; int /*<<< orphan*/  aligned_width; scalar_t__ pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct delta_dev {int /*<<< orphan*/  dev; } ;
struct delta_dec {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  m2m_ctx; } ;
struct delta_ctx {scalar_t__ state; int /*<<< orphan*/  name; struct delta_frameinfo frameinfo; int /*<<< orphan*/  flags; TYPE_2__ fh; struct delta_dec* dec; struct delta_dev* dev; } ;
typedef  int /*<<< orphan*/  str ;
typedef  int /*<<< orphan*/  frameinfo ;

/* Variables and functions */
 int /*<<< orphan*/  DELTA_FLAG_FRAMEINFO ; 
 scalar_t__ DELTA_STATE_READY ; 
 int EBUSY ; 
 int call_dec_op (struct delta_dec const*,int /*<<< orphan*/ ,struct delta_ctx*,struct delta_frameinfo*) ; 
 char* delta_frameinfo_str (struct delta_frameinfo*,unsigned char*,int) ; 
 int delta_try_fmt_frame (struct file*,void*,struct v4l2_format*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  frame_stride (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  get_frameinfo ; 
 int /*<<< orphan*/  memset (struct delta_frameinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_frameinfo ; 
 struct delta_ctx* to_ctx (int /*<<< orphan*/ ) ; 
 struct vb2_queue* v4l2_m2m_get_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_streaming (struct vb2_queue*) ; 

__attribute__((used)) static int delta_s_fmt_frame(struct file *file, void *fh, struct v4l2_format *f)
{
	struct delta_ctx *ctx = to_ctx(file->private_data);
	struct delta_dev *delta = ctx->dev;
	const struct delta_dec *dec = ctx->dec;
	struct v4l2_pix_format *pix = &f->fmt.pix;
	struct delta_frameinfo frameinfo;
	unsigned char str[100] = "";
	struct vb2_queue *vq;
	int ret;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (vb2_is_streaming(vq)) {
		dev_dbg(delta->dev, "%s V4L2 S_FMT (CAPTURE): queue busy\n",
			ctx->name);
		return -EBUSY;
	}

	if (ctx->state < DELTA_STATE_READY) {
		/*
		 * decoder not yet opened and valid stream header not found,
		 * could not negotiate format with decoder, check at least
		 * pixel format & negotiate resolution boundaries
		 * and alignment...
		 */
		ret = delta_try_fmt_frame(file, fh, f);
		if (ret) {
			dev_dbg(delta->dev,
				"%s V4L2 S_FMT (CAPTURE): unsupported format %4.4s\n",
				ctx->name, (char *)&pix->pixelformat);
			return ret;
		}

		return 0;
	}

	/* set frame information to decoder */
	memset(&frameinfo, 0, sizeof(frameinfo));
	frameinfo.pixelformat = pix->pixelformat;
	frameinfo.width = pix->width;
	frameinfo.height = pix->height;
	frameinfo.aligned_width = pix->width;
	frameinfo.aligned_height = pix->height;
	frameinfo.size = pix->sizeimage;
	frameinfo.field = pix->field;
	frameinfo.colorspace = pix->colorspace;
	frameinfo.xfer_func = pix->xfer_func;
	frameinfo.ycbcr_enc = pix->ycbcr_enc;
	frameinfo.quantization = pix->quantization;
	ret = call_dec_op(dec, set_frameinfo, ctx, &frameinfo);
	if (ret)
		return ret;

	/* then get what decoder can really do */
	ret = call_dec_op(dec, get_frameinfo, ctx, &frameinfo);
	if (ret)
		return ret;

	ctx->flags |= DELTA_FLAG_FRAMEINFO;
	ctx->frameinfo = frameinfo;
	dev_dbg(delta->dev,
		"%s V4L2 SET_FMT (CAPTURE): frameinfo updated to %s\n",
		ctx->name,
		delta_frameinfo_str(&frameinfo, str, sizeof(str)));

	pix->pixelformat = frameinfo.pixelformat;
	pix->width = frameinfo.aligned_width;
	pix->height = frameinfo.aligned_height;
	pix->bytesperline = frame_stride(pix->width, pix->pixelformat);
	pix->sizeimage = frameinfo.size;
	pix->field = frameinfo.field;
	pix->colorspace = frameinfo.colorspace;
	pix->xfer_func = frameinfo.xfer_func;
	pix->ycbcr_enc = frameinfo.ycbcr_enc;
	pix->quantization = frameinfo.quantization;

	return 0;
}