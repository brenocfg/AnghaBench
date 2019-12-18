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
struct v4l2_pix_format {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ pixelformat; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; } ;
struct TYPE_4__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {int /*<<< orphan*/  type; TYPE_1__ fmt; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ pixelformat; int /*<<< orphan*/  size; void* aligned_height; void* aligned_width; } ;
struct TYPE_5__ {int /*<<< orphan*/  m2m_ctx; } ;
struct hva_ctx {int /*<<< orphan*/  flags; TYPE_3__ frameinfo; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  name; TYPE_2__ fh; } ;
struct file {int /*<<< orphan*/  private_data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 void* ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  HVA_FLAG_FRAMEINFO ; 
 int /*<<< orphan*/  HVA_HEIGHT_ALIGNMENT ; 
 int /*<<< orphan*/  HVA_WIDTH_ALIGNMENT ; 
 struct device* ctx_to_dev (struct hva_ctx*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 struct hva_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 int hva_try_fmt_frame (struct file*,void*,struct v4l2_format*) ; 
 struct vb2_queue* v4l2_m2m_get_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_streaming (struct vb2_queue*) ; 

__attribute__((used)) static int hva_s_fmt_frame(struct file *file, void *fh, struct v4l2_format *f)
{
	struct hva_ctx *ctx = fh_to_ctx(file->private_data);
	struct device *dev = ctx_to_dev(ctx);
	struct v4l2_pix_format *pix = &f->fmt.pix;
	struct vb2_queue *vq;
	int ret;

	ret = hva_try_fmt_frame(file, fh, f);
	if (ret) {
		dev_dbg(dev, "%s V4L2 S_FMT (OUTPUT): unsupported format %.4s\n",
			ctx->name, (char *)&pix->pixelformat);
		return ret;
	}

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (vb2_is_streaming(vq)) {
		dev_dbg(dev, "%s V4L2 S_FMT (OUTPUT): queue busy\n", ctx->name);
		return -EBUSY;
	}

	ctx->colorspace = pix->colorspace;
	ctx->xfer_func = pix->xfer_func;
	ctx->ycbcr_enc = pix->ycbcr_enc;
	ctx->quantization = pix->quantization;

	ctx->frameinfo.aligned_width = ALIGN(pix->width, HVA_WIDTH_ALIGNMENT);
	ctx->frameinfo.aligned_height = ALIGN(pix->height,
					      HVA_HEIGHT_ALIGNMENT);
	ctx->frameinfo.size = pix->sizeimage;
	ctx->frameinfo.pixelformat = pix->pixelformat;
	ctx->frameinfo.width = pix->width;
	ctx->frameinfo.height = pix->height;
	ctx->flags |= HVA_FLAG_FRAMEINFO;

	return 0;
}